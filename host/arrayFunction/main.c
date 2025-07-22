/*
 * main.c
 *
 *  Created on: Mar 5, 2025
 *      Author: mauricewashington
 */


#include <stdio.h>
#include <stdint.h>

void array_display(uint8_t* pArray,uint32_t nItems);

int main(){
	uint8_t someData[10];
	uint8_t length = sizeof(someData)/sizeof(uint8_t);

	for (int i = 0; i < length; i++){
		someData[i] = 0xFF;
	}

	for (int i = 0; i < length; i++){
		someData[i] = 0x33;
	}

	array_display(someData,length);

	for (int i = 0; i < length; i++){
		someData[i] = 0x22;
	}


	array_display((someData + 3),length-3);


	return 0;
}

void array_display(uint8_t* pArray, uint32_t nItems){
	for (uint32_t i = 0; i < nItems;i++){
		printf("%x\t",pArray[i]);
	}
	printf("\n");
}
