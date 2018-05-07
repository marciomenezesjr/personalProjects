################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/msp430_4.3.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./HAL/mrfi_board.obj" \
"./HAL/HAL_device.obj" \
"./HAL/HAL_F5_board.obj" \
"./SimpliciTI/Components/mrfi/mrfi.obj" \
"./SimpliciTI/Components/mrfi/radios/mrfi_spi.obj" \
"./SimpliciTI/Components/mrfi/radios/mrfi_radio.obj" \
"./SimpliciTI/Components/mrfi/radios/mrfi_f1f2.obj" \
"./SimpliciTI/Components/simpliciti/nwk/nwk_globals.obj" \
"./SimpliciTI/Components/simpliciti/nwk/nwk_frame.obj" \
"./SimpliciTI/Components/simpliciti/nwk/nwk_api.obj" \
"./SimpliciTI/Components/simpliciti/nwk/nwk_QMgmt.obj" \
"./SimpliciTI/Components/simpliciti/nwk/nwk.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_security.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_ping.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_mgmt.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_link.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_join.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_ioctl.obj" \
"./SimpliciTI/Components/simpliciti/nwk_applications/nwk_freq.obj" \
"./SimpliciTI/bsp_glue.obj" \
"./SimpliciTI/Radio_interface.obj" \
"./User/AIR_Node_main.obj" \
"./User/AIR_Node.obj" \
"../lnk_msp430f5529.cmd" \
-l"libmath.a" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include User/subdir_vars.mk
-include SimpliciTI/subdir_vars.mk
-include SimpliciTI/Components/simpliciti/nwk_applications/subdir_vars.mk
-include SimpliciTI/Components/simpliciti/nwk/subdir_vars.mk
-include SimpliciTI/Components/mrfi/radios/subdir_vars.mk
-include SimpliciTI/Components/mrfi/subdir_vars.mk
-include HAL/subdir_vars.mk
-include subdir_rules.mk
-include User/subdir_rules.mk
-include SimpliciTI/subdir_rules.mk
-include SimpliciTI/Components/simpliciti/nwk_applications/subdir_rules.mk
-include SimpliciTI/Components/simpliciti/nwk/subdir_rules.mk
-include SimpliciTI/Components/mrfi/radios/subdir_rules.mk
-include SimpliciTI/Components/mrfi/subdir_rules.mk
-include HAL/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
AIR_Node.out \

EXE_OUTPUTS__QUOTED += \
"AIR_Node.out" \


# All Target
all: AIR_Node.out

# Tool invocations
AIR_Node.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Node\SimpliciTI\Configuration\smpl_config.dat" --cmd_file="C:\Users\Marcio\Desktop\Angstrom\angstrom_ccs_workspace\AIR_Node\SimpliciTI\Configuration\smpl_nwk_config.dat"  -vmspx --abi=eabi -Ooff -g --define=__MSP430F5529__ --define=LITTLE_ENDIANx --define=MRFI_CC1100 --define=SW1_PORT_IEx --define=SW2_PORT_IE --define=FREQUENCY_AGILITY --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=nofloat -z -m"AIR_Node.map" --heap_size=160 --stack_size=160 --use_hw_mpy=F5 -i"c:/ti/ccsv6/ccs_base/msp430/include" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/lib" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/include" -i"c:/ti/ccsv6/ccs_base/msp430/lib" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="AIR_Node_linkInfo.xml" --rom_model -o "AIR_Node.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "User\AIR_Node.pp" "User\AIR_Node_main.pp" "SimpliciTI\Radio_interface.pp" "SimpliciTI\bsp_glue.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_freq.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_ioctl.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_join.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_link.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_mgmt.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_ping.pp" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_security.pp" "SimpliciTI\Components\simpliciti\nwk\nwk.pp" "SimpliciTI\Components\simpliciti\nwk\nwk_QMgmt.pp" "SimpliciTI\Components\simpliciti\nwk\nwk_api.pp" "SimpliciTI\Components\simpliciti\nwk\nwk_frame.pp" "SimpliciTI\Components\simpliciti\nwk\nwk_globals.pp" "SimpliciTI\Components\mrfi\radios\mrfi_f1f2.pp" "SimpliciTI\Components\mrfi\radios\mrfi_radio.pp" "SimpliciTI\Components\mrfi\radios\mrfi_spi.pp" "SimpliciTI\Components\mrfi\mrfi.pp" "HAL\HAL_F5_board.pp" 
	-$(RM) "HAL\HAL_device.pp" "HAL\mrfi_board.pp" 
	-$(RM) "User\AIR_Node.obj" "User\AIR_Node_main.obj" "SimpliciTI\Radio_interface.obj" "SimpliciTI\bsp_glue.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_freq.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_ioctl.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_join.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_link.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_mgmt.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_ping.obj" "SimpliciTI\Components\simpliciti\nwk_applications\nwk_security.obj" "SimpliciTI\Components\simpliciti\nwk\nwk.obj" "SimpliciTI\Components\simpliciti\nwk\nwk_QMgmt.obj" "SimpliciTI\Components\simpliciti\nwk\nwk_api.obj" "SimpliciTI\Components\simpliciti\nwk\nwk_frame.obj" "SimpliciTI\Components\simpliciti\nwk\nwk_globals.obj" "SimpliciTI\Components\mrfi\radios\mrfi_f1f2.obj" "SimpliciTI\Components\mrfi\radios\mrfi_radio.obj" "SimpliciTI\Components\mrfi\radios\mrfi_spi.obj" "SimpliciTI\Components\mrfi\mrfi.obj" 
	-$(RM) "HAL\HAL_F5_board.obj" "HAL\HAL_device.obj" "HAL\mrfi_board.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"c:/ti/ccsv6/tools/compiler/msp430_4.3.1/bin/hex430" --ti_txt "AIR_Node.out" -o "AIR_Node.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

