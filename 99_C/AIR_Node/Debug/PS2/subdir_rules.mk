################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
PS2/PS2_Controller.obj: ../PS2/PS2_Controller.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_ccs/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\Drystone_Vortex_GND\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\Drystone_Vortex_GND\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff --include_path="C:/ti_ccs/ccsv5/tools/compiler/msp430_4.2.1/include" --include_path="C:/ti_ccs/ccsv5/ccs_base/msp430/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/PS2" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/Oled" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/Drystone_Vortex_GND/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430F5529__ --define=LITTLE_ENDIANx --define=MRFI_CC1100 --define=SW1_PORT_IEx --define=SW2_PORT_IE --define=FREQUENCY_AGILITY --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=nofloat --preproc_with_compile --preproc_dependency="PS2/PS2_Controller.pp" --obj_directory="PS2" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


