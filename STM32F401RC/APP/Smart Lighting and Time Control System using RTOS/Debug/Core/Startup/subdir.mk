################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f401rctx.s 

OBJS += \
./Core/Startup/startup_stm32f401rctx.o 

S_DEPS += \
./Core/Startup/startup_stm32f401rctx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/FreeRTOS/include" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/Config" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/OS" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/Record" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/SEGGER" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f401rctx.d ./Core/Startup/startup_stm32f401rctx.o

.PHONY: clean-Core-2f-Startup

