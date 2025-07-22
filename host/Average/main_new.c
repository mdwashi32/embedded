/*
 * main_new.c
 *
 *  Created on: Feb 25, 2025
 *      Author: mauricewashington
 */
#include <stdio.h>

int main(){
	float number1, number2, number3;
	float average;
	printf("Enter 3 numbers: ");
	fflush(stdout);
	scanf("%c %c %c % c % ",&number1,&number2,&number3);

	average = (number1 + number2 + number3) / 3;
	printf("The average is %f\n",average);

	getchar();

	return 0;

}

