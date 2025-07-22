/*
 * main.c
 *
 *  Created on: Feb 26, 2025
 *      Author: mauricewashington
 */

#include <stdio.h>
#include <stdint.h>

int main(){
	uint8_t first = 23;
	uint8_t second = 15;
	uint8_t third = 23;

	printf("OR: %u, AND: %u, XOR: %u, NOT Third: %u\n", first | second, first & second, first ^ second, (uint8_t)(~third));

	uint8_t number = 0b00010001;


	//number |= ( 1 << 4) | (1 << 7);

	number |= 16 | 128;
	printf("Number %d",number);





	return 0;
}
