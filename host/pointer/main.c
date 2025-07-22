/*
 * main.c
 *
 *  Created on: Feb 25, 2025
 *      Author: mauricewashington
 */
#include <stdio.h>

int main(){
	char c = 100;
	printf("%p\n",&c);
	char *ptr = &c;

	char d = *ptr;
	printf("%d\n", d);

	*ptr = 65;
	printf("%d",c);

	return 0;
}

