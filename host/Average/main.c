/*
 * main.c
 *
 *  Created on: Feb 25, 2025
 *      Author: mauricewashington
 */

#include <stdio.h>

int main(){
	float number1, number2, number3;
	float average;
	printf("Enter the first number: ");
	fflush(stdout);
	scanf("%f",&number1);
	printf("\nEnter the second number: ");
	fflush(stdout);
	scanf("%f",&number2);
	printf("\nEnter the third number: ");
	fflush(stdout);
	scanf("%f",&number3);

	average = (number1 + number2 + number3) / 3;
	printf("The average is %f\n",average);

	getchar();

	return 0;

}
