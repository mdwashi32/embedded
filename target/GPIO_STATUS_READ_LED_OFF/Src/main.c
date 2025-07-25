/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* STM32F4xx register boundary addresses - Reference Manual - Page 65
 * RCC: 0x4002 3800 - 0x4002 3BFF
 * 		- RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) Address offset: 0x30 - Page 244
 * 			- PORT A EN => |= 1
 * 			- PORT D EN => |= (1<<3)
 * GPIOA: 0x4002 0000 - 0x4002 03FF
 * 		- Read status?
 * 			- IF PA0 LOW - LED ON
 * 			- IF PA0 HIGH - LED OFF
 * 			- in this case is PA0 in output or input mode?
 * 				- Guess input, since it is dependent on connecting to VDD and GND
 * 		- PORT A, MODE Input
 * 			-  Address offset: 0x00 => 0x4002 0000 - Page 284
 * 				- CLEAR PA0 => &= ~(3) //no need to shift since it is first two bits
 * 		- Port A Read Input
 * 			- Address offset: 0x10 => 0x4002 0010 - Page 286
 * 			- We don't want to write here so simply Read (make data const)
 * 				- pin 0 is at 0
 * 				- If 1, then led on
 * 					- Bit extraction: Bit0 is already LSB so only need to mask by Bit0 & 1 to see if value is 1
 * GPIOD: 0x4002 0C00 - 0x4002 0FFF
 * 		- PORT D, MODE General Purpose Output
 * 			-  Address offset: 0x00 => 0x4002 0C00 - Page 284
 * 				- CLEAR PD12 => &= ~(3 << 24)
 * 				- SET PD 12 Output => |= (1 << 24)
 * 		- PORT D, Set (Write) Output (Turn on LED)
 * 			- Address offset: 0x14 => 0x4002 0C14 - Page 286
 * 				-SET PD12 |= (1 <<12)
 *
 *
 *
 */





int main(void)
{
	uint32_t volatile *const gpioAHB1Clock = (uint32_t*)0x40023830;
	uint32_t volatile *const pa0Input = (uint32_t*)0x40020000;
	uint32_t const volatile *const pa0Read = (uint32_t*)0x40020010; //need volatile here to prevent optimization issue with pin read
	// Use const volatile for read only memory addresses

	uint32_t volatile *const pd12Output = (uint32_t*)0x40020C00;
	uint32_t volatile *const pd12Write = (uint32_t*)0x40020C14;

	// Enable clocks
	*gpioAHB1Clock |= 1; // ENABLE Port A CLK
	*gpioAHB1Clock |= (1<<3); // ENABLE Port D CLK

	// Set Mode
	*pa0Input &= ~(3); // Clear Port A pin-1 to set as Input
	*pd12Output &= ~(3 << 24); // Clear Port D bits
	*pd12Output |= (1 << 24); // Set 24th but to set Port D as General Output

	// Read pA0
	uint8_t pinStatus = (uint8_t)(*pa0Read & 0x1); // mask all bits except for desired bit 0

	while(1){
		if (pinStatus){
			*pd12Write |= (1<< 12); // Turn on LED
		}
		else *pd12Write &= ~(1<< 12); // Turn off LED

	}


	/* Loop forever */
	for(;;);
}
