/*
 * main.c
 *
 *  Created on: Mar 2, 2025
 *      Author: mauricewashington
 */

#include <stdio.h>
#include <stdint.h>

// Store 32 bits of packet with its respective sections.

union Packet{
	uint32_t packetValue;
	struct{
		uint32_t crc		:2; // 2 bits @ bit 0
		uint32_t status		:1; // 1 bit @ bit 2
		uint32_t payload	:12; // 12 bits @ bit 3
		uint32_t bat		:3; // 3 bits @ bit 15
		uint32_t sensor		:3; // 3 bits @ bit 18
		uint32_t longAddr	:8; // 8 bits @ bit 21
		uint32_t shortAddr	:2; // 2 bits @ bit 29
		uint32_t addrMode	:1; // 1 bit @ bit 31
	}packetFields;

};
// reduces size of struct from 10 bytes to 4 bytes.

void packetInformation(union Packet *ptr);

int main(){
	union Packet packetCapture;
	union Packet *pPacket = &packetCapture;

	packetInformation(pPacket);

	while(getchar() != '\n');
	getchar();

	return 0;
}

void packetInformation(union Packet *ptr){
	printf("Please enter a 32 bit packet value:\n");
	scanf(" %X",&ptr->packetValue);

//	ptr->crc = (uint8_t)(userInput >> 0) & (0x3);
//	ptr->status = (uint8_t)(userInput >> 2) & (0x1);
//	ptr->payload = (uint16_t)(userInput >> 3) & (0xFFF);
//	ptr->bat = (uint8_t)(userInput >> 15) & (0x7);
//	ptr->sensor = (uint8_t)(userInput >> 18) & (0x7);
//	ptr->longAddr = (uint8_t)(userInput >> 21) & (0xFF);
//	ptr->shortAddr = (uint8_t)(userInput >> 29) & (0x3);
//	ptr->addrMode = (uint8_t)(userInput >> 31) & (0x1);
// Doing struct in uion made it so that the struct packetFields value mask, receive and only return desired info
	printf("Packet information for %X\n",ptr->packetValue);
	printf("================================\n");
	printf("crc\t\t\t:%#X\n",ptr->packetFields.crc);
	printf("status\t\t\t:%#X\n",ptr->packetFields.status);
	printf("payload\t\t\t:%#X\n",ptr->packetFields.payload);
	printf("bat\t\t\t:%#X\n",ptr->packetFields.bat);
	printf("sensor\t\t\t:%#X\n",ptr->packetFields.sensor);
	printf("longAddr\t\t\t:%#X\n",ptr->packetFields.longAddr);
	printf("shortAddr\t\t\t:%#X\n",ptr->packetFields.shortAddr);
	printf("addrMode\t\t\t:%#X\n",ptr->packetFields.addrMode);
	printf("Size of union is %llu bytes.",(long long)sizeof(union Packet));

}

