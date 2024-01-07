################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/UART/UART.c 

OBJS += \
./MCAL/UART/UART.o 

C_DEPS += \
./MCAL/UART/UART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/UART/UART.o: ../MCAL/UART/UART.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/MCAL/UART" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/MCAL/RCC" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/HAL/Keypad" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/HAL/LCD" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/MCAL/GPIO" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/STM32F103C6_Drivers/MCAL/EXTI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/UART/UART.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

