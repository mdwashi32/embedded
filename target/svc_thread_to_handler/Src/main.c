/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int main(void)
{
	__asm volatile("SVC #25");
	printf("Out of SVC Handler\n");

	// register uint32_t data __asm("r0");
	uint32_t data;
	__asm("MOV %0,R0": "=r"(data) ::);
	printf("SVC incremented by 4 is %ld\n",data);
	/* Loop forever */
	for(;;);
}

__attribute__ ((naked)) void SVC_Handler(void)
{
	//1. get the value of the MSP
	__asm("MRS R0,MSP"); //Store MSP
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
	printf("In SVC handler\n");
	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6]; //MSP + 6 = PC = Instruction after SVC instruction

	//2. decrement the return address by 2 to point to opcode
	// of the SVC instruction in the program memory
	pReturn_addr -= 2; //PC - 2 = instruction before PC = SVC instruction

	//3. extract the SVC number (LSbyte of opcode)
	uint8_t svc_number = *pReturn_addr;
	printf("SVC number is %d\n",svc_number);

	//4. increment SVC number by 4 and return it to thread mode
	svc_number += 4; //increment
	pBaseOfStackFrame[0] = svc_number; //store back to stack frame, remember that [0] is R0
}
