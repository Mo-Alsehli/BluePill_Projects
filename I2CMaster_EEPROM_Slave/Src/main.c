/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Magdi
 * @brief          : Main program body
 ****************************************************************************** */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
#include "LCD.h"
#include "Keypad.h"
#include "RCC.h"
#include "UART.h"
#include "TIM.h"
#include "SPI.h"
#include "I2C.h"
#include "EEPROM_I2C_Slave.h"



uint16_t ch;


void clockInit()
{
	RCC_GPIOA_CLk_EN();
	RCC_GPIOB_CLk_EN();
	RCC_AFIO_CLK_EN();
}

int main(void)
{
	GPIO_PinConfig_t pinCfg;

	clockInit();

	// Test Case 1:
	uint8_t ch1[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	uint8_t ch2[] = {0};

	EEPROM_Init();
	EEPROM_Write_NBytes(0xAF, ch1, 7);
	EEPROM_Read_Byte(0xAF, ch2, 7);

	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	EEPROM_Write_NBytes(0xFFF, ch1, 4);
	EEPROM_Read_Byte(0xFFF, ch2, 4);


	while (1){
	}
}
