#!/usr/bin/env python3
# PYTHON_ARGCOMPLETE_OK

import json
import build_helper

kconfig_tmpl = """
#
# Automatically generated by gen_panel_config.py; DO NOT EDIT.
#

menu "Panel settings"
{0}

{1}

endmenu
"""

kconfig_choice_tmpl = """
choice
    prompt "{0}"
{1}
endchoice
"""

kconfig_config_bool_tmpl = """
config {0}
    bool "{1}"
    help
      "y" Config {1}.
"""

kconfig_config_str_tmpl = """
config {1}
    string{0}
"""

param_default_str_tmpl = """
    default "{0}" if {1}"""


def gen_panel_list(panel_intf_list):
    kconfig_panel_list = ""

    for panel_intf in panel_intf_list:
        panel_list = panel_intf_list[panel_intf]
        panel_intf = panel_intf.upper()

        kconfig_panel_config_list = ""
        for panel in panel_list:
            panel_name_u = panel.upper()
            panel_name_l = panel.lower()

            kconfig_panel_config_list = (
                kconfig_panel_config_list
                + kconfig_config_bool_tmpl.format(
                    panel_intf + "_PANEL_" + panel_name_u,
                    panel_intf + "_panel_" + panel_name_l))

        kconfig_panel_list = kconfig_panel_list + kconfig_panel_config_list
    kconfig_panel_list = kconfig_choice_tmpl.format("Panel selecting", kconfig_panel_list)

    return kconfig_panel_list


def gen_panel_tuning_list(panel_intf_list, tuning_param):
    kconfig_panel_tuning_list = ""
    param_default_str = ""

    for panel_intf in panel_intf_list:
        panel_list = panel_intf_list[panel_intf]
        panel_intf = panel_intf.upper()

        for panel in panel_list:
            panel_u = panel.upper()
            panel_l = panel.lower()
            param_default_str = (
                param_default_str
                + param_default_str_tmpl.format(panel_intf + "_panel_" + panel_l, panel_intf + "_PANEL_" + panel_u))

    kconfig_panel_tuning_list = kconfig_config_str_tmpl.format(param_default_str, tuning_param)

    return kconfig_panel_tuning_list


def gen_panel_tuning_param_list(panel_param_list, tuning_param):
    param_default_str = ""

    for panel_param in panel_param_list:
        panel_param_u = panel_param.upper()
        panel_param_l = panel_param.lower()
        param_default_str = (
            param_default_str
            + param_default_str_tmpl.format("MIPI_panel_" + panel_param_l, "MIPI_PANEL_" + panel_param_u))

    kconfig_panel_tuning_param_list = kconfig_config_str_tmpl.format(param_default_str, tuning_param)

    return kconfig_panel_tuning_param_list


def main():

    with open(build_helper.PANEL_LIST_PATH, "r", encoding="utf-8") as fp:
        panel_list_json = json.load(fp)
    panel_intf_list = panel_list_json['panel_list']
    panel_param_list = panel_list_json['panel_param']
    kconfig_panel_list = gen_panel_list(panel_intf_list)
    kconfig_panel_tuning_param_list = (
        gen_panel_tuning_list(panel_intf_list, "PANEL_TUNING_PARAM")
        + gen_panel_tuning_param_list(panel_param_list['lane_num'], "PANEL_LANE_NUM_TUNING_PARAM")
        + gen_panel_tuning_param_list(panel_param_list['lane_swap'], "PANEL_LANE_SWAP_TUNING_PARAM"))

    kconfig = kconfig_tmpl.format(
        kconfig_panel_list, kconfig_panel_tuning_param_list
    )

    with open(build_helper.PANEL_KCONFIG_PATH, "w") as fp:
        fp.write(kconfig)


if __name__ == "__main__":
    main()
