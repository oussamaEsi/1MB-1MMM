##############################################################################
## Filename:          E:\Code_Doctorat_Virtex5\Base_System_MMM/drivers/ip_mmm256_opt_v1_00_a/data/ip_mmm256_opt_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Feb 06 14:32:45 2018 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "ip_mmm256_opt" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
