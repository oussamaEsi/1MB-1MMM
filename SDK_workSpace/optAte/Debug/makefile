################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
optAte.elf.size \

ELFCHECK += \
optAte.elf.elfcheck \


# All Target
all: optAte.elf secondary-outputs

# Tool invocations
optAte.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../optAte_bsp/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.a -mno-xl-soft-mul -o"optAte.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

optAte.elf.size: optAte.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size optAte.elf  |tee "optAte.elf.size"
	@echo Finished building: $@
	@echo ' '

optAte.elf.elfcheck: optAte.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck optAte.elf -hw ../../Base_System_MMM_hw_platform/system.xml -pe microblaze_0  |tee "optAte.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) optAte.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
