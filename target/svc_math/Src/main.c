/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdint.h>
#include<stdio.h>

void SVC_Handle_c(uint32_t *pBaseStackFrame);

int32_t add_numbers(int32_t x , int32_t y )
{
    int32_t res;
    __asm volatile("SVC #36");
    __asm volatile ("MOV %0,R0": "=r"(res) ::);
    return res;

}


int32_t sub_numbers(int32_t x , int32_t y )
{
	 int32_t res;
	 __asm volatile("SVC #37");
	 __asm volatile ("MOV %0,R0": "=r"(res) ::);
	 return res;
   //TODO

}

int32_t mul_numbers(int32_t x , int32_t y )
{
	 int32_t res;
	 __asm volatile("SVC #38");
	 __asm volatile ("MOV %0,R0": "=r"(res) ::);
	 return res;

    //TODO
}

int32_t div_numbers(int32_t x , int32_t y )
{
	 int32_t res;
	 __asm volatile("SVC #39");
	 __asm volatile ("MOV %0,R0": "=r"(res) ::);
	 return res;
    //TODO

}


int main(void)
{
    int32_t res;

    res = add_numbers(40, -90);
    printf("Add result = %ld\n",res);

    res = sub_numbers(25,150);
    printf("Sub result = %ld\n",res);

    res = mul_numbers(374,890);
    printf("mul result = %ld\n", res);

    res = div_numbers(67,-3);
    printf("div result = %ld\n",res);

    for(;;);
}


__attribute__( ( naked ) ) void SVC_Handler( void )
{
    __asm ("MRS r0,MSP");
    __asm( "B SVC_Handler_c");
}


void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
    printf("in SVC handler\n");

    uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];

    //2. decrement the return address by 2 to point to
    //opcode of the SVC instruction in the program memory
    pReturn_addr-=2;


    //3. extract the SVC number (LSByte of the opcode)
    uint8_t svc_number = *pReturn_addr;

    printf("Svc number is : %d\n",svc_number);


    int32_t result = 0;
/*SVC number signifies the type of operation , decode it */
    switch(svc_number)
    {

    case 36:
        /*TODO:addition */
    	result = pBaseOfStackFrame[0] + pBaseOfStackFrame[1];

        break;
    case 37:
        /*TODO:Subtraction*/
    	result = pBaseOfStackFrame[0] - pBaseOfStackFrame[1];

        break;
    case 38:
        /*TODO:Multiplication*/
    	result = pBaseOfStackFrame[0] * pBaseOfStackFrame[1];

        break;
    case 39:
        /*TODO:division*/
    	result = pBaseOfStackFrame[0] / pBaseOfStackFrame[1];

        break;
    default:
        printf("invalid svc code\n");

    }

/*store the result back to stack frame at R0's position */
    pBaseOfStackFrame[0] = result; //TODO

}
