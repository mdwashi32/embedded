/*
 * main.c
 *
 *  Created on: Feb 26, 2025
 *      Author: mauricewashington
 */
#include <stdio.h>
#include <stdint.h>

void wait_for_input();

int main(){

	int age = 0;
	printf("Please enter your age: ");
	scanf("%d",&age);

	if (age >= 18){
		printf("\nYour age is %d and you can vote\n", age);
	}

	else printf("Your age is %d and you cannot vote\n", age);

	age < 18 ? printf("Heck no\n") : printf("Heck yes\n");

	printf("\nPlease provide two numbers to be evaluated: ");

	int32_t number1 = 0, number2 = 0;
	scanf("%d %d",&number1,&number2);

	if (number1 > number2){
		printf("%d is greater than %d\n",number1,number2);
	}

	else if(number1 == number2){
		printf("%d is equal to %d\n",number1,number2);
	}
	else printf("%d is less than %d\n", number1, number2);

	char shape;
	printf("Please enter the symbol for your desired shape.\n"
			"1. 't' for triangle\n"
			"2. 'z' for trapezoid\n"
			"3. 'c' for circle\n"
			"4. 's' for square\n"
			"5. 'r' for 'rectangle\n");
	if (!(scanf(" %c",&shape))){
		printf("Error, invalid input\n Exiting....\n");
	}
	float base1 = 0;
	float base2 = 0;
	float height = 0;
	float radius = 0;

	switch(shape){
		case 't':
			printf("Please provide the base, followed by the height of the triangle: ");
			scanf(" %f %f", &base1, &height);
			if (base1 < 0 || height < 0){
				printf("Error!!!! Exit.\n");
				return -1;
			}
			printf("The area of the triangle is %f.\n", (base1 * height)/2.0);
			break;
		case 'z':
			printf("Please provide the first base, followed by the second base, followed by the height of the trapezoid: ");
			scanf(" %f %f %f", &base1, &base2, &height);
			if (base1 < 0 || base2 < 0 || height < 0){
				printf("Error!!!! Exit.\n");
				return -1;
						}
			printf("The area of the trapezoid is %f\n", ((base1 + base2)/2.0)*height);
			break;
		case 'c':
			printf("Please provide the radius of the circle: ");
			scanf(" %f", &radius);
			if (radius < 0){
				printf("Error!!!! Exit.\n");
				return -1;
						}

			printf("The area of the circle is %f.\n", (3.14 * (radius * radius)));
			break;
		case 's':
			printf("Please provide the side of the square: ");
			scanf(" %f", &base1);
			if (base1 < 0){
				printf("Error!!!! Exit.\n");
				return -1;
						}
			printf("The area of the square is %f.\n", (base1 * base1));
			break;
		case 'r':
			printf("Please provide the base, followed by the height of the rectangle: ");
			scanf(" %f %f", &base1, &height);
			if (base1 < 0 || height <0){
				printf("Error!!!! Exit.\n");
				return -1;
						}
			printf("The area of the rectangle is %f.\n", base1 * height);
			break;
		default:
			printf("Invalid input. Exit.\n");
			return -1;
		}


	wait_for_input();
	return 0;

}

void wait_for_input(){
	printf("Please press enter to exit this application");
	while(getchar() != '\n'){
			//just read input buffer and do nothing
		}
	getchar();
}

