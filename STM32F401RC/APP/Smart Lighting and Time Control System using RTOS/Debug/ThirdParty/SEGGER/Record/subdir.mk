################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/Record/segger_uart.c 

OBJS += \
./ThirdParty/SEGGER/Record/segger_uart.o 

C_DEPS += \
./ThirdParty/SEGGER/Record/segger_uart.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/Record/%.o ThirdParty/SEGGER/Record/%.su ThirdParty/SEGGER/Record/%.cyclo: ../ThirdParty/SEGGER/Record/%.c ThirdParty/SEGGER/Record/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/FreeRTOS/include" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/Config" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/OS" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/Record" -I"D:/studying/Embedded_Advenced_Diploma_amged_samir/Projects/Smart Lighting and Time Control System using RTOS/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-SEGGER-2f-Record

clean-ThirdParty-2f-SEGGER-2f-Record:
	-$(RM) ./ThirdParty/SEGGER/Record/segger_uart.cyclo ./ThirdParty/SEGGER/Record/segger_uart.d ./ThirdParty/SEGGER/Record/segger_uart.o ./ThirdParty/SEGGER/Record/segger_uart.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-Record

