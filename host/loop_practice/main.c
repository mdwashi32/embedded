/*
 * main.c
 *
 *  Created on: Feb 27, 2025
 *      Author: mauricewashington
 */


#include <stdio.h>
#include <stdint.h>

int main(){

	int n1 = 0;
	int n2 = 0;

	printf("Please insert boundaries for even number count: ");
	scanf(" %d %d",&n1,&n2);
	if (n1 < 0 || n1 > 100 || n2 < 0 || n2 > 100){
		printf("\nOut of bounds. Must be between 0 and 100. Exiting.");
		return -1;
	}

//
//	while (n1 <= n2){
//		if (n1 % 2 == 0){
//			printf("%4u\t",n1);
//		}
//		n1++;
//	}
	for ( printf("Even numbers are: \n"); n1 <= n2; n1++){
		if (n1 % 2 == 0){
			printf("%4u\t",n1);
		}
	}


	return 0;
}
