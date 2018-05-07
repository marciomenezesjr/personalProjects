################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SimpliciTI/Gateway_Radio_interface.obj: ../SimpliciTI/Gateway_Radio_interface.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Receiver\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Receiver\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430F5529__ --define=MRFI_CC1100 --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="SimpliciTI/Gateway_Radio_interface.pp" --obj_directory="SimpliciTI" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SimpliciTI/bsp_glue.obj: ../SimpliciTI/bsp_glue.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Receiver\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Receiver\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Receiver/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430F5529__ --define=MRFI_CC1100 --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="SimpliciTI/bsp_glue.pp" --obj_directory="SimpliciTI" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


