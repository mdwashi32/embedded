/*
 * main.c
 *
 *  Created on: Feb 27, 2025
 *      Author: mauricewashington
 */
#include <stdio.h>
#include <stdint.h>

int main(){
	int height = 0;

	printf("Please insert the height of your pyramid:\n");
	scanf(" %u",&height);

	for(int i = 1; i <= height; i++){
		for(int j = i; j > 0; j--){
			printf(" %2d\t",j);
		}
		printf("\n");
	}

}
