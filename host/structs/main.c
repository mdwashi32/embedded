/*
 * main.c
 *
 *  Created on: Mar 2, 2025
 *      Author: mauricewashington
 */

#include <stdio.h>
#include <stdint.h>



// Structs should be defined outside of main function, preferably in header file
struct carModel
{
		int carNumber;
		uint32_t carPrice;
		uint16_t carMaxSpeed;
		float carWeight;
};



int main(){

	struct carModel carBMW = {2021,15000,220,1330};
	struct carModel carFord = {4031, 350000, 160, 1900.96};

	printf("Details of car BMW is as follow\n");
	printf("Car Number is %d", carBMW.carNumber);

	carFord.carNumber = 2200;
	printf("Details of car BMW is as follow\n");
	printf("Car Number is %d", carFord.carNumber);






	return 0;
}
