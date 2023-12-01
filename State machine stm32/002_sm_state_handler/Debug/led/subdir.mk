################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../led/led.c 

OBJS += \
./led/led.o 

C_DEPS += \
./led/led.d 


# Each subdirectory must supply rules for building sources it contributes
led/%.o led/%.su: ../led/%.c led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/el_gl/Desktop/courses/uml_state_machine_git/State machine stm32/002_sm_state_handler/lcd" -I"C:/Users/el_gl/Desktop/courses/uml_state_machine_git/State machine stm32/002_sm_state_handler/led" -I"C:/Users/el_gl/Desktop/courses/uml_state_machine_git/State machine stm32/002_sm_state_handler/state_machine" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-led

clean-led:
	-$(RM) ./led/led.d ./led/led.o ./led/led.su

.PHONY: clean-led

