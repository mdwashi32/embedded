/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Jun 23, 2025
 *      Author: mauricewashington
 */

#include "stm32f407xx_gpio_driver.h"

/*
 * Peripheral Clock Setup
 */
/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_PeriClockControl
 *
 * 	@brief					-	This function enables or disables peripheral clock for given GPIO port
 *
 * 	@param[in]				-	Base address of GPIO peripheral
 * 	@param[in]				-	ENABLE OR DISABLE (macro)
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}

	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}

/*
 * Init and De-init (reset)
 */
/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_Init
 *
 * 	@brief					-	This function initializes the pin configuration for a given port
 *
 * 	@param[in]				-	Base address of GPIO peripheral
 * 	@param[in]				-
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

	uint32_t temp = 0; // temporary register

	//enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);


	// 1. Configure mode of GPIO pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//Non-interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clear
		pGPIOHandle->pGPIOx->MODER |= temp; //set
	}
	else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure the FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. Configure RTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. Configure both FTSR and RTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] |= portCode << (temp2 * 4);

		//3. Enable the EXTI delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	// 2. Configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3. Configure the pull-up/pull-down settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4. Configure the output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. Configure the alternate functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// configure the alternate function registers
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2);

	}

	temp = 0;
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_DeInit
 *
 * 	@brief					-	This function resets the pin configuration for a given port
 *
 * 	@param[in]				-	Base address of GPIO peripheral
 * 	@param[in]				-
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
	else if(pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*
 * Data Read and Write
 */
/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_ReadFromInputPin
 *
 * 	@brief					-	This function reads the data available on a pin configured as input
 *
 * 	@param[in]				-	Base address of GPIO peripheral
 * 	@param[in]				-	GPIO Pin Number
 * 	@param[in]				-
 *
 * 	@return					-	The value on input pin as an 8 bit unsigned integer
 *
 * 	@Note					-	none
 *************************************************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001); //shift value at pin to LSB and mask all other values with 0
	return value;
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_ReadFromInputPort
 *
 * 	@brief					-	This function reads the data available on all input pins for a given port
 *
 * 	@param[in]				-	Base address of GPIO peripheral/port
 * 	@param[in]				-
 * 	@param[in]				-
 *
 * 	@return					-	The value on all port input pins as a 16 bit unsigned integer
 *
 * 	@Note					-	none
 *************************************************************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR; //shift value at pin to LSB and mask all other values with 0
	return value;
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_WriteToOutputPin
 *
 * 	@brief					-	This function writes data to an output pin for a given port
 *
 * 	@param[in]				-	Base address of GPIO peripheral/port
 * 	@param[in]				-	Pin number
 * 	@param[in]				-	Value to be written
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// write 1 at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}

	else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_WriteToOutputPort
 *
 * 	@brief					-	This function writes data to all output pins for a given port
 *
 * 	@param[in]				-	Base address of GPIO peripheral/port
 * 	@param[in]				-	Value to be written
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_ToggleOutputPin
 *
 * 	@brief					-	This function enables or disables a GPIO pin as output
 *
 * 	@param[in]				-	Base address of GPIO peripheral/port
 * 	@param[in]				-	Pin number
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber); //bitwise XOR on the specific pin to toggle
}

/*
 * IRQ Configuration and ISR Handling
 */
/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_IRQInterruptConfig
 *
 * 	@brief					-	This function enables/disables interrupts for GPIO
 *
 * 	@param[in]				-	Interrupt Request Number
 * 	@param[in]				-	ENABLE or DISABLE (macro)
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 32 && IRQNumber < 64)
		{
			//program ISER1
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber > 64 && IRQNumber < 96)
		{
			//ISER2
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			//ICER0
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 32 && IRQNumber < 64)
		{
			//ICER1
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber > 64 && IRQNumber < 96)
		{
			//ICER2
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
		}
	}
}

/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_IRQPriorityConfig
 *
 * 	@brief					-	This function sets interrupt priority
 *
 * 	@param[in]				-	Interrupt Request Number
 * 	@param[in]				-	Interrupt Priority
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. first determine IPR register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4 ;

	//2. set priority
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount); // +iprx because pointer arithmetic leads to +4 address bytes
}


/*************************************************************************************************************
 * FUNCTION DETAILS
 * 	@function				-	GPIO_IRQHandling
 *
 * 	@brief					-	This is the handler for GPIO interrupt requests for a given pin
 *
 * 	@param[in]				-	PinNumber (port not necessary as input as it will be provided by EXTI during interrupt)
 * 	@param[in]				-
 * 	@param[in]				-
 *
 * 	@return					-	none
 *
 * 	@Note					-	none
 *************************************************************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI PR register corresponding to the pin number
	if(EXTI->PR &(1 <<PinNumber))
	{
		//clear
		EXTI->PR |= (1 << PinNumber); //CLR EXTI PR for pin by setting 1
	}
}
