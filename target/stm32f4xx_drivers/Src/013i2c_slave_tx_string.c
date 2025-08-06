/*
 * 013i2c_slave_tx_string.c
 *
 *  Created on: Aug 6, 2025
 *      Author: mauricewashington
 */


#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_i2c_driver.h"
#include <string.h>
#include <stdio.h>

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */

#define SLAVE_ADDR		0x68
#define MY_ADDR			SLAVE_ADDR

uint8_t txBuffer[32] = "STM32 Slave mode testing.";
I2C_Handle_t I2C1Handle;
uint8_t opcode = 0;

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

void I2C1_GPIOInits()
{
	GPIO_Handle_t I2CPins;
	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCL PB6
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);

	// SDA PB9
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&I2CPins);
}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GpioBtn;
	//button
	GpioBtn.pGPIOx = GPIOA;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioBtn);

}


int main(void)
{
	// Initialize GPIO button
	GPIO_ButtonInit();

	// Initialize GPIO pins as I2C1 peripheral pins
	I2C1_GPIOInits();

	// Initialize I2C1 peripheral configuration
	I2C1_Inits();

	// I2C IRQ configurations
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ERR, ENABLE);

	I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

	// Enable I2C1 peripheral
	I2C_PeripheralControl(I2C1, ENABLE); // ACK is enabled in peripheral control API

	while(1);

}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ERR_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEvent)
{
	static uint8_t count = 0;

	if(AppEvent == I2C_EV_DATA_REQ)
	{
		// Master is requesting data. Slave must send.
		if (opcode == 0x51)
		{
			// send length of data to master
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*)txBuffer));
		}
		else if(opcode == 0x52)
		{
			//send content of txBuffer
			I2C_SlaveSendData(pI2CHandle->pI2Cx, txBuffer[count++]);
		}

	}
	else if( AppEvent == I2C_EV_DATA_RCV)
	{
		// Data is waiting for slave to read
		opcode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);
	}
	else if(AppEvent == I2C_ERROR_AF)
	{
		// Master sent ACK, no more transmission from slave (during slave Tx)
		opcode = 0xFF;
		count = 0;
	}
	else if (AppEvent == I2C_EV_STOP)
	{
		//Master has ended I2C communication, no more reception by slave
	}
}
