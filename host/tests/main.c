//comment style one

/*Comment style two
 * on another line
 * and another
 */



#include <stdio.h>

int main(void){

	int AtoB = 160;
	int BtoC = 40;
	int C = AtoB + BtoC;


	printf("Total distance from A2C is %X 251\n",C);
	printf("Size of char data type = %d\n",sizeof(char));
	printf("Size of short data type = %d\n",sizeof(short));
	printf("Size of int data type = %d\n",sizeof(int));
	printf("Size of long data type = %d\n",sizeof(long));
	printf("Size of long long data type = %d\n",sizeof(long long));

	return 0;
}
