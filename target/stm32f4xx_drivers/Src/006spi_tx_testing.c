/*
 * 006spi_tx_testing.c
 *
 *  Created on: Jul 1, 2025
 *      Author: mauricewashington
 */

// 	PB15-> SPI2_MOSI
// 	PB14-> SPI2_MISO // Unused
//	PB13-> SPI2_SCLK
//	PB12-> SPI2_NSS // Unused
// Alt function Mode 5

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include <string.h>

void SPI2_GPIOInits()
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

//	//MISO
//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&SPIPins);

//	//NSS
//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
//	GPIO_Init(&SPIPins);


}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; //generates SCLK of 8MHZ
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_BITS8;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_HIGH;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //Software Slave MAnagement enabled for NSS

	SPI_Init(&SPI2Handle);
}

int main(void)
{
	char user_data[] = "Hello World";

	// Initialize GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	// Initialize SPI2 peripheral parameters
	SPI2_Inits();

	// Set NSS High to prevent Status Register MODF (Mode fault) = 1 which sets SPI to Slave Mode due to fault
	SPI_SSI_Config(SPI2,ENABLE);

	// Enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	// Send data
	SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

	// Confirm SPI not busy
	while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG)); // If busy, loop (while(1))

	// Disable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,DISABLE);

	while(1);

	return 0;

}
