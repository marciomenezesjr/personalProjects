################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
User/AIR_Gateway.obj: ../User/AIR_Gateway.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Gateway\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Gateway\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430F5529__ --define=MRFI_CC1100 --define=LITTLE_ENDIANx --define=SW1_PORT_IEx --define=SW2_PORT_IE --define=FREQUENCY_AGILITY --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="User/AIR_Gateway.pp" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User/AIR_Gateway_main.obj: ../User/AIR_Gateway_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Gateway\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Gateway\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/HAL" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/User" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/mrfi" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/simpliciti/nwk" --include_path="C:/Users/Marcio/Desktop/Angstrom/angstrom_ccs_workspace/AIR_Gateway/SimpliciTI/Components/simpliciti/nwk_applications" -g --define=__MSP430F5529__ --define=MRFI_CC1100 --define=LITTLE_ENDIANx --define=SW1_PORT_IEx --define=SW2_PORT_IE --define=FREQUENCY_AGILITY --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="User/AIR_Gateway_main.pp" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


