/*
 * main.c
 *
 *  Created on: Mar 5, 2025
 *      Author: mauricewashington
 */

#include <stdio.h>

int main(){



	char msg1[] = "Hello how are you?";
	printf("Message is : %s\n",msg1);
	printf("Message 1 Address : %p\n",&msg1);
	printf("Message 1 value : %p\n",msg1);

	char *msg2 = "Hello, I am good. You?";
	printf("Message is : %s\n",msg2);
	printf("Message 1 Address : %p\n",&msg2);
	printf("Message 1 value : %p\n",msg2);


	return 0;
}

