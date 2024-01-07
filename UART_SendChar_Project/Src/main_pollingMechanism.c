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

void clockInit()
{
	RCC_GPIOA_CLk_EN();
	RCC_GPIOB_CLk_EN();
	AFIO_CLK_EN();
}

int main(void)
{
	uint16_t ch;
	UART_Config_t uartCfg;
	clockInit();
	uartCfg.BaudRate = UART_BaudRate_115200;
	uartCfg.IRQ_Enable = UART_IRQ_Eanble_NONE;
	uartCfg.HwFlowCtl = UART_HwFlowCtl_NONE;
	uartCfg.Parity = UART_Parity_NONE;
	uartCfg.Mode = UART_Mode_TX_RX;
	uartCfg.Payload = UART_PayloadLength_8B;
	uartCfg.StopBits = UART_StopBits_One;
	uartCfg.P_IRQ_Callback = NULL;

	MCAL_UART_Init(UART1, &uartCfg);
	MCAL_UART_GPIO_SetPins(UART1);
	while (1){
		MCAL_UART_SendData(UART1, &ch, enable);
		MCAL_UART_ReceiveData(UART1, &ch, enable);
	}
}
