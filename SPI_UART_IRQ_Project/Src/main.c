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

// SPI Device Mode configuration
//#define MCU_Act_Master
#define MCU_Act_Slave

uint16_t ch;

void UARTSendCharCallBack(){
#ifdef MCU_Act_Master
	MCAL_UART_ReceiveData(UART1, &ch, disable);
	MCAL_UART_SendData(UART1, &ch, enable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_LOW);
	MCAL_SPI_TX_RX(SPI1, &ch, pollingEn);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_HIGH);
#endif
}

void SPI1_IRQ_Callback(struct S_IRQ_SRC irqSrc){
#ifdef MCU_Act_Slave
	if(irqSrc.RXNE){
		ch = 0xf;
		MCAL_SPI_TX_RX(SPI1, &ch, pollingDis);
		MCAL_UART_SendData(UART1, &ch, pollingEn);
	}
#endif
}

void clockInit()
{
	RCC_GPIOA_CLk_EN();
	RCC_GPIOB_CLk_EN();
	RCC_AFIO_CLK_EN();
}

int main(void)
{
	UART_Config_t uartCfg;
	SPI_Config spi1Cfg;
	GPIO_PinConfig_t pinCfg;

	clockInit();
	uartCfg.BaudRate = UART_BaudRate_115200;
	uartCfg.IRQ_Enable = UART_IRQ_Eanble_RXNEIE;
	uartCfg.HwFlowCtl = UART_HwFlowCtl_NONE;
	uartCfg.Parity = UART_Parity_NONE;
	uartCfg.Mode = UART_Mode_TX_RX;
	uartCfg.Payload = UART_PayloadLength_8B;
	uartCfg.StopBits = UART_StopBits_One;
	uartCfg.P_IRQ_Callback = UARTSendCharCallBack;

	MCAL_UART_Init(UART1, &uartCfg);
	MCAL_UART_GPIO_SetPins(UART1);

	// SPI Initialization (SPI1)

	spi1Cfg.CLKPhase = SPI_CLK_Phase_2Edge;
	spi1Cfg.CLKPolarity = SPI_CLK_Polarity_High_When_Idle;
	spi1Cfg.dataSize = SPI_Data_Size_8Bit;
	spi1Cfg.frameFormat = SPI_Frame_Foramt_MSB;
	spi1Cfg.SPIBaudratePrescaller = SPI_BaudRate_Prescaller_8;
	spi1Cfg.communicationMode = SPI_Direction_2LINES;


#ifdef MCU_Act_Master
	spi1Cfg.deviceMode = SPI_Device_Mode_Master;
	spi1Cfg.IRQ_Enable = SPI_IRQ_Enable_NONE;
	spi1Cfg.NSS = SPI_NSS_SW_Internal_Set;
	spi1Cfg.P_IRQ_Callback = NULL;

	pinCfg.GPIO_PinNumber = GPIO_PIN_4;
	pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfg);

	// Force the slave select (high) idle mode.
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_HIGH);
#endif

#ifdef MCU_Act_Slave
	spi1Cfg.deviceMode = SPI_Device_Mode_Slave;
	spi1Cfg.IRQ_Enable = SPI_IRQ_Enable_RXNEIE;
	spi1Cfg.NSS = SPI_NSS_HW_Slave;
	spi1Cfg.P_IRQ_Callback = SPI1_IRQ_Callback;
#endif

	MCAL_SPI_Init(SPI1, &spi1Cfg);
	MCAL_SPI_GPIO_SetPins(SPI1);


	while (1){

	}
}
