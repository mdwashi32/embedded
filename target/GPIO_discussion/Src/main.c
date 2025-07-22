/**
 ******************************************************************************
 ******************************************************************************
 * @attention
 * 1. Identify the GPIO port (of intended peripheral)  e.g. PORT D for GPIOD
 * 2. Identify the pin(s) needed for connection e.g PD12 for LED
 * 3. Activate GPIO (e.g. GPIOD) peripheral (Enabled the clock)
 * 		- Peripheral could be on by default so need to check reference manual for microcontroller
 * 		- ST microelectronics are normally dead by default
 * 		- ST peripheral clock (RCC) addresses: 0x4002 3800 - 0x4002 3BFF
 * 			- GPIOD is on AHB1 bus, RCC AHB1 peripheral clock register has offset of 0x30
 * 				- so address is *** 0x4002 3830 (RCC_AHB1ENR) ***
 * 				- GPIOD EN is on bit 3 so need to enable with |= (1 << 3)
 * 					- setting to 0 disables
 * 				- Can reset register with 0x0010 0000
 * 4. To turn on an LED for example, need to configure GPIO mode as output
 * 		- e.g. *** GPIOD mode register is at 0x4002 0C00 *** (has offset of 0x00 from GPIO base address)
 * 			- Setting bit 24 ( |= (1 << 24) ) will enable GPIOD pin-12 as general purpose output  (bit 25 belongs to pin 12 but remains at 0)
 * 5. Write to GPIO pin
 * 		- GPIO(D) port output data register offset 0x14
 * 			- *** GPIOx_ODR address is 0x4002 0C14 ***
 * 				- to write pin 12 as high (turn led on), set bit 12 to 1 ( | = (1 << 12 ))
 *
 * 		- 1 (HIGH) to make GPIO state HIGH (3.3v)
 * 		- 0 (LOW) to make GPIO state LOW (3.3v)
 *
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	uint32_t* rccAHB1 = (uint32_t*)0x40023830;
	uint32_t* gpioD12Mode = (uint32_t*)0x40020C00;
	uint32_t* gpioD12Out = (uint32_t*)0x40020C14;

	*rccAHB1 |= (1 << 3); //set bit 3 to enable GPIOD EN clock
	*gpioD12Mode &= ~(3 << 24); // clear bits 24 and 25 for output of GPIOD pin-12
	*gpioD12Mode |= (1 << 24); //set bit 24 to enable GPIOD pin-12 in output mode
	while(1){
		*gpioD12Out |= (1 << 12); //set bit 12 to turn on LED
		for(uint32_t i = 0; i < 200000; i++);
		*gpioD12Out &= ~(1 << 12);
		for(uint32_t i = 0; i < 200000; i++);
	}

    /* Loop forever */
	for(;;);
}
