/*
 * main.h
 *
 *  Created on: Mar 3, 2025
 *      Author: mauricewashington
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>

typedef struct{
	uint32_t gpioaen		:1;
	uint32_t gpioben		:1;
	uint32_t gpiocen		:1;
	uint32_t gpioden		:1;
	uint32_t gpioeen		:1;
	uint32_t gpiofen		:1;
	uint32_t gpiogen		:1;
	uint32_t gpiohen		:1;
	uint32_t gpioien		:1;
	uint32_t reserved_1		:3;
	uint32_t crcen			:1;
	uint32_t reserved_2		:5;
	uint32_t bkpsramen		:1;
	uint32_t reserved_3		:1;
	uint32_t ccmdataramen 	:1;
	uint32_t dma1en			:1;
	uint32_t dma2en			:1;
	uint32_t reserved_4		:2;
	uint32_t ethmacen		:1;
	uint32_t ethmactxen		:1;
	uint32_t ethmacrxen		:1;
	uint32_t ethmacptpen	:1;
	uint32_t otghsen		:1;
	uint32_t otghsuplien	:1;
	uint32_t reserved_5		:1;
}RCC_AHB1ENR_t; // RCC Base Address 0x4002 3800
				// offset 0x30

typedef struct{
	uint32_t moder0			:2;
	uint32_t moder1			:2;
	uint32_t moder2			:2;
	uint32_t moder3			:2;
	uint32_t moder4			:2;
	uint32_t moder5			:2;
	uint32_t moder6			:2;
	uint32_t moder7			:2;
	uint32_t moder8			:2;
	uint32_t moder9			:2;
	uint32_t moder10		:2;
	uint32_t moder11		:2;
	uint32_t moder12		:2;
	uint32_t moder13		:2;
	uint32_t moder14		:2;
	uint32_t moder15		:2;
}GPIOx_MODER_t; // GPIOA Base Address 0x4002 0000
				// GPIOD Base Address 0x4002 0C00
				// offset 0x00

typedef struct{
	uint32_t idr0			:1;
	uint32_t idr1			:1;
	uint32_t idr2			:1;
	uint32_t idr3			:1;
	uint32_t idr4			:1;
	uint32_t idr5			:1;
	uint32_t idr6			:1;
	uint32_t idr7			:1;
	uint32_t idr8			:1;
	uint32_t idr9			:1;
	uint32_t idr10			:1;
	uint32_t idr11			:1;
	uint32_t idr12			:1;
	uint32_t idr13			:1;
	uint32_t idr14			:1;
	uint32_t idr15			:1;
	uint32_t reserved 		:16;
}GPIOx_IDR_t;	// GPIOA Base Address 0x4002 0000
				// offset 0x10

typedef struct{
	uint32_t odr0			:1;
	uint32_t odr1			:1;
	uint32_t odr2			:1;
	uint32_t odr3			:1;
	uint32_t odr4			:1;
	uint32_t odr5			:1;
	uint32_t odr6			:1;
	uint32_t odr7			:1;
	uint32_t odr8			:1;
	uint32_t odr9			:1;
	uint32_t odr10			:1;
	uint32_t odr11			:1;
	uint32_t odr12			:1;
	uint32_t odr13			:1;
	uint32_t odr14			:1;
	uint32_t odr15			:1;
	uint32_t reserved 		:16;
}GPIOx_ODR_t;	// GPIOD Base Address 0x4002 0C00
				// offset 0x14

#endif /* MAIN_H_ */
