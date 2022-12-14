/*
 * Copyright (c) 2014-2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __CPU_MACROS_S__
#define __CPU_MACROS_S__

#include <cpu.h>

#define CPU_IMPL_PN_MASK	(MIDR_IMPL_MASK << MIDR_IMPL_SHIFT) | \
				(MIDR_PN_MASK << MIDR_PN_SHIFT)

/* The number of CPU operations allowed */
#define CPU_MAX_PWR_DWN_OPS		2

/* Special constant to specify that CPU has no reset function */
#define CPU_NO_RESET_FUNC		0

/* Word size for 64-bit CPUs */
#define CPU_WORD_SIZE			8

/*
 * Whether errata status needs reporting. Errata status is printed in debug
 * builds for both BL1 and BL31 images.
 */
#if (defined(IMAGE_BL1) || defined(IMAGE_BL31)) && DEBUG
# define REPORT_ERRATA	1
#else
# define REPORT_ERRATA	0
#endif

	/*
	 * Define the offsets to the fields in cpu_ops structure.
	 */
	.struct 0
CPU_MIDR: /* cpu_ops midr */
	.space  8
/* Reset fn is needed in BL at reset vector */
#if defined(IMAGE_BL1) || defined(IMAGE_BL31)
CPU_RESET_FUNC: /* cpu_ops reset_func */
	.space  8
#endif
#ifdef IMAGE_BL31 /* The power down core and cluster is needed only in BL31 */
CPU_PWR_DWN_OPS: /* cpu_ops power down functions */
	.space  (8 * CPU_MAX_PWR_DWN_OPS)
#endif

/*
 * Fields required to print errata status. Only in BL31 that the printing
 * require mutual exclusion and printed flag.
 */
#if REPORT_ERRATA
CPU_ERRATA_FUNC:
	.space	8
#ifdef IMAGE_BL31
CPU_ERRATA_LOCK:
	.space	8
CPU_ERRATA_PRINTED:
	.space	8
#endif
#endif

#if defined(IMAGE_BL31) && CRASH_REPORTING
CPU_REG_DUMP: /* cpu specific register dump for crash reporting */
	.space  8
#endif
CPU_OPS_SIZE = .

	/*
	 * Write given expressions as quad words
	 *
	 * _count:
	 *	Write at least _count quad words. If the given number of
	 *	expressions is less than _count, repeat the last expression to
	 *	fill _count quad words in total
	 * _rest:
	 *	Optional list of expressions. _this is for parameter extraction
	 *	only, and has no significance to the caller
	 *
	 * Invoked as:
	 *	fill_constants 2, foo, bar, blah, ...
	 */
	.macro fill_constants _count:req, _this, _rest:vararg
	  .ifgt \_count
	    /* Write the current expression */
	    .ifb \_this
	      .error "Nothing to fill"
	    .endif
	    .quad \_this

	    /* Invoke recursively for remaining expressions */
	    .ifnb \_rest
	      fill_constants \_count-1, \_rest
	    .else
	      fill_constants \_count-1, \_this
	    .endif
	  .endif
	.endm

	/*
	 * Declare CPU operations
	 *
	 * _name:
	 *	Name of the CPU for which operations are being specified
	 * _midr:
	 *	Numeric value expected to read from CPU's MIDR
	 * _resetfunc:
	 *	Reset function for the CPU. If there's no CPU reset function,
	 *	specify CPU_NO_RESET_FUNC
	 * _power_down_ops:
	 *	Comma-separated list of functions to perform power-down
	 *	operatios on the CPU. At least one, and up to
	 *	CPU_MAX_PWR_DWN_OPS number of functions may be specified.
	 *	Starting at power level 0, these functions shall handle power
	 *	down at subsequent power levels. If there aren't exactly
	 *	CPU_MAX_PWR_DWN_OPS functions, the last specified one will be
	 *	used to handle power down at subsequent levels
	 */
	.macro declare_cpu_ops _name:req, _midr:req, _resetfunc:req, \
		_power_down_ops:vararg
	.section cpu_ops, "a"
	.align 3
	.type cpu_ops_\_name, %object
	.quad \_midr
#if defined(IMAGE_BL1) || defined(IMAGE_BL31)
	.quad \_resetfunc
#endif
#ifdef IMAGE_BL31
1:
	/* Insert list of functions */
	fill_constants CPU_MAX_PWR_DWN_OPS, \_power_down_ops
2:
	/*
	 * Error if no or more than CPU_MAX_PWR_DWN_OPS were specified in the
	 * list
	 */
	.ifeq 2b - 1b
	  .error "At least one power down function must be specified"
	.else
	  .iflt 2b - 1b - (CPU_MAX_PWR_DWN_OPS * CPU_WORD_SIZE)
	    .error "More than CPU_MAX_PWR_DWN_OPS functions specified"
	  .endif
	.endif
#endif

#if REPORT_ERRATA
	.ifndef \_name\()_cpu_str
	  /*
	   * Place errata reported flag, and the spinlock to arbitrate access to
	   * it in the data section.
	   */
	  .pushsection .data
	  define_asm_spinlock \_name\()_errata_lock
	  \_name\()_errata_reported:
	  .word	0
	  .popsection

	  /* Place CPU string in rodata */
	  .pushsection .rodata
	  \_name\()_cpu_str:
	  .asciz "\_name"
	  .popsection
	.endif

	/*
	 * Weakly-bound, optional errata status printing function for CPUs of
	 * this class.
	 */
	.weak \_name\()_errata_report
	.quad \_name\()_errata_report

#ifdef IMAGE_BL31
	/* Pointers to errata lock and reported flag */
	.quad \_name\()_errata_lock
	.quad \_name\()_errata_reported
#endif
#endif

#if defined(IMAGE_BL31) && CRASH_REPORTING
	.quad \_name\()_cpu_reg_dump
#endif
	.endm

#if REPORT_ERRATA
	/*
	 * Print status of a CPU errata
	 *
	 * _chosen:
	 *	Identifier indicating whether or not a CPU errata has been
	 *	compiled in.
	 * _cpu:
	 *	Name of the CPU
	 * _id:
	 *	Errata identifier
	 * _rev_var:
	 *	Register containing the combined value CPU revision and variant
	 *	- typically the return value of cpu_get_rev_var
	 */
	.macro report_errata _chosen, _cpu, _id, _rev_var=x8
	/* Stash a string with errata ID */
	.pushsection .rodata
	\_cpu\()_errata_\_id\()_str:
	.asciz	"\_id"
	.popsection

	/* Check whether errata applies */
	mov	x0, \_rev_var
	bl	check_errata_\_id

	.ifeq \_chosen
	/*
	 * Errata workaround has not been compiled in. If the errata would have
	 * applied had it been compiled in, print its status as missing.
	 */
	cbz	x0, 900f
	mov	x0, #ERRATA_MISSING
	.endif
900:
	adr	x1, \_cpu\()_cpu_str
	adr	x2, \_cpu\()_errata_\_id\()_str
	bl	errata_print_msg
	.endm
#endif

#endif /* __CPU_MACROS_S__ */
