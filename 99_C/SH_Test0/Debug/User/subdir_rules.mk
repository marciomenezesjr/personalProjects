################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
User/compass.obj: ../User/compass.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Test0\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Test0\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/Sensors_API" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430FR5739__ --define=MRFI_CC1100 --define=ENABLE_SENSOR_DATA_STATUSx --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="User/compass.pp" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User/compass_main.obj: ../User/compass_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Test0\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\SH_Test0\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/Sensors_API" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/SH_Test0/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430FR5739__ --define=MRFI_CC1100 --define=ENABLE_SENSOR_DATA_STATUSx --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="User/compass_main.pp" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


