/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2021. All rights reserved.
 *
 * File Name: mars-clock.h
 * Description:
 */

#ifndef __DT_BINDINGS_CLK_MARS_H__
#define __DT_BINDINGS_CLK_MARS_H__

#define MARS_CLK_MPLL				0
#define MARS_CLK_TPLL				1
#define MARS_CLK_FPLL				2
#define MARS_CLK_MIPIMPLL			3
#define MARS_CLK_A0PLL				4
#define MARS_CLK_DISPPLL			5
#define MARS_CLK_CAM0PLL			6
#define MARS_CLK_CAM1PLL			7

#define MARS_CLK_MIPIMPLL_D3			8
#define MARS_CLK_CAM0PLL_D2			9
#define MARS_CLK_CAM0PLL_D3			10

#define MARS_CLK_A53				11
#define MARS_CLK_CPU_AXI0			12
#define MARS_CLK_CPU_GIC			13
#define MARS_CLK_XTAL_A53			14
#define MARS_CLK_TPU				15
#define MARS_CLK_TPU_FAB			16
#define MARS_CLK_AHB_ROM			17
#define MARS_CLK_DDR_AXI_REG			18
#define MARS_CLK_RTC_25M			19
#define MARS_CLK_TEMPSEN			20
#define MARS_CLK_SARADC				21
#define MARS_CLK_EFUSE				22
#define MARS_CLK_APB_EFUSE			23
#define MARS_CLK_DEBUG				24
#define MARS_CLK_XTAL_MISC			25
#define MARS_CLK_AXI4_EMMC			26
#define MARS_CLK_EMMC				27
#define MARS_CLK_100K_EMMC			28
#define MARS_CLK_AXI4_SD0			29
#define MARS_CLK_SD0				30
#define MARS_CLK_100K_SD0			31
#define MARS_CLK_AXI4_SD1			32
#define MARS_CLK_SD1				33
#define MARS_CLK_100K_SD1			34
#define MARS_CLK_SPI_NAND			35
#define MARS_CLK_500M_ETH0			36
#define MARS_CLK_AXI4_ETH0			37
#define MARS_CLK_500M_ETH1			38
#define MARS_CLK_AXI4_ETH1			39
#define MARS_CLK_APB_GPIO			40
#define MARS_CLK_APB_GPIO_INTR			41
#define MARS_CLK_GPIO_DB			42
#define MARS_CLK_AHB_SF				43
#define MARS_CLK_SDMA_AXI			44
#define MARS_CLK_SDMA_AUD0			45
#define MARS_CLK_SDMA_AUD1			46
#define MARS_CLK_SDMA_AUD2			47
#define MARS_CLK_SDMA_AUD3			48
#define MARS_CLK_APB_I2C			49
#define MARS_CLK_APB_WDT			50
#define MARS_CLK_PWM				51
#define MARS_CLK_APB_SPI0			52
#define MARS_CLK_APB_SPI1			53
#define MARS_CLK_APB_SPI2			54
#define MARS_CLK_APB_SPI3			55
#define MARS_CLK_CAM0_200			56
#define MARS_CLK_UART0				57
#define MARS_CLK_APB_UART0			58
#define MARS_CLK_UART1				59
#define MARS_CLK_APB_UART1			60
#define MARS_CLK_UART2				61
#define MARS_CLK_APB_UART2			62
#define MARS_CLK_UART3				63
#define MARS_CLK_APB_UART3			64
#define MARS_CLK_UART4				65
#define MARS_CLK_APB_UART4			66
#define MARS_CLK_APB_I2S0			67
#define MARS_CLK_APB_I2S1			68
#define MARS_CLK_APB_I2S2			69
#define MARS_CLK_APB_I2S3			70
#define MARS_CLK_AXI4_USB			71
#define MARS_CLK_APB_USB			72
#define MARS_CLK_125M_USB			73
#define MARS_CLK_33K_USB			74
#define MARS_CLK_12M_USB			75
#define MARS_CLK_AXI4				76
#define MARS_CLK_AXI6				77
#define MARS_CLK_DSI_ESC			78
#define MARS_CLK_AXI_VIP			79
#define MARS_CLK_SRC_VIP_SYS_0			80
#define MARS_CLK_SRC_VIP_SYS_1			81
#define MARS_CLK_DISP_SRC_VIP			82
#define MARS_CLK_AXI_VIDEO_CODEC		83
#define MARS_CLK_VC_SRC0			84
#define MARS_CLK_H264C				85
#define MARS_CLK_H265C				86
#define MARS_CLK_JPEG				87
#define MARS_CLK_APB_JPEG			88
#define MARS_CLK_APB_H264C			89
#define MARS_CLK_APB_H265C			90
#define MARS_CLK_CAM0				91
#define MARS_CLK_CAM1				92
#define MARS_CLK_CSI_MAC0_VIP			93
#define MARS_CLK_CSI_MAC1_VIP			94
#define MARS_CLK_ISP_TOP_VIP			95
#define MARS_CLK_IMG_D_VIP			96
#define MARS_CLK_IMG_V_VIP			97
#define MARS_CLK_SC_TOP_VIP			98
#define MARS_CLK_SC_D_VIP			99
#define MARS_CLK_SC_V1_VIP			100
#define MARS_CLK_SC_V2_VIP			101
#define MARS_CLK_SC_V3_VIP			102
#define MARS_CLK_DWA_VIP			103
#define MARS_CLK_BT_VIP				104
#define MARS_CLK_DISP_VIP			105
#define MARS_CLK_DSI_MAC_VIP			106
#define MARS_CLK_LVDS0_VIP			107
#define MARS_CLK_LVDS1_VIP			108
#define MARS_CLK_CSI0_RX_VIP			109
#define MARS_CLK_CSI1_RX_VIP			110
#define MARS_CLK_PAD_VI_VIP			111
#define MARS_CLK_1M				112
#define MARS_CLK_SPI				113
#define MARS_CLK_I2C				114
#define MARS_CLK_PM				115
#define MARS_CLK_TIMER0				116
#define MARS_CLK_TIMER1				117
#define MARS_CLK_TIMER2				118
#define MARS_CLK_TIMER3				119
#define MARS_CLK_TIMER4				120
#define MARS_CLK_TIMER5				121
#define MARS_CLK_TIMER6				122
#define MARS_CLK_TIMER7				123
#define MARS_CLK_APB_I2C0			124
#define MARS_CLK_APB_I2C1			125
#define MARS_CLK_APB_I2C2			126
#define MARS_CLK_APB_I2C3			127
#define MARS_CLK_APB_I2C4			128
#define MARS_CLK_WGN				129
#define MARS_CLK_WGN0				130
#define MARS_CLK_WGN1				131
#define MARS_CLK_WGN2				132
#define MARS_CLK_KEYSCAN			133
#define MARS_CLK_AHB_SF1			134
#define MARS_CLK_VC_SRC1			135
#define MARS_CLK_SRC_VIP_SYS_2			136
#define MARS_CLK_PAD_VI1_VIP			137
#define MARS_CLK_CFG_REG_VIP			138
#define MARS_CLK_CFG_REG_VC			139
#define MARS_CLK_AUDSRC				140
#define MARS_CLK_APB_AUDSRC			141
#define MARS_CLK_VC_SRC2			142
#define MARS_CLK_PWM_SRC			143
#define MARS_CLK_AP_DEBUG			144
#define MARS_CLK_SRC_RTC_SYS_0			145
#define MARS_CLK_PAD_VI2_VIP			146
#define MARS_CLK_CSI_BE_VIP			147
#define MARS_CLK_VIP_IP0			148
#define MARS_CLK_VIP_IP1			149
#define MARS_CLK_VIP_IP2			150
#define MARS_CLK_VIP_IP3			151
#define MARS_CLK_C906_0				152
#define MARS_CLK_C906_1				153
#define MARS_CLK_SRC_VIP_SYS_3			154
#define MARS_CLK_SRC_VIP_SYS_4			155
#define MARS_CLK_IVE_VIP			156
#define MARS_CLK_RAW_VIP			157
#define MARS_CLK_OSDC_VIP			158
#define MARS_CLK_CSI_MAC2_VIP			159
#define MARS_CLK_CAM0_VIP			160

#endif /* __DT_BINDINGS_CLK_MARS_H__ */
