/*
 * lcd.c
 *
 *  Created on: Aug 10, 2025
 *      Author: mauricewashington
 */

#include "lcd.h"

static void write_4_bits(uint8_t value);
static void lcd_enable(void);

void lcd_send_command(uint8_t cmd)
{
	// RS = 0 for LCD Instruction Register
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, RESET);

	// RnW = 0, for write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, RESET);

	// Send Upper Nibble
	write_4_bits(cmd >> 4);

	// Send Lower Nibble
	write_4_bits(cmd & 0XF);

}

void lcd_send_char(uint8_t data)
{
	// RS = 1 for LCD Data Register
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, SET);

	// RnW = 0, for write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, RESET);

	// Send Upper Nibble
	write_4_bits(data >> 4);

	// Send Lower Nibble
	write_4_bits(data & 0XF);

}

void lcd_print_string(char *message)
{
	do
	{
		lcd_send_char((uint8_t)*message++);
	}while(*message !=  '\0');
}

void lcd_init(void)
{
	//1. Configure GPIO pins for LCD connections
	GPIO_Handle_t lcd;

	// All pins have same output config
	lcd.pGPIOx = LCD_GPIO_PORT;
	lcd.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	lcd.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	lcd.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	lcd.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//RS
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&lcd);

	//RW
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd);

	//EN
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&lcd);

	//D4
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd);

	//D5
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd);

	//D6
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd);

	//D7
	lcd.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd);

	// initialize all pins to 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, RESET);


	//2. LCD Initialization Sequence

	// step 1: delay at least 40 ms
	mdelay(40);

	// step 2: RESET RS (Data register for write RS = 0) and RnW (Writing to LCD so RnW = 0).
	//		   DB7, DB6 = 0, DB5, DB4= 1.
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, RESET);

	// write to 4 data bits
	write_4_bits(0x3); // write 0011 across D7-D4

	// step 3: delay at least 4.1ms
	mdelay(5);

	// step 4: Repeat step 2 data write
	write_4_bits(0x3); // write 0011 across D7-D4

	// step 5: delay at least 100 microseconds
	udelay(150);

	// step 6: Repeat step 2 data write
	write_4_bits(0x3); // write 0011 across D7-D4

	// step 7: RS,RnW,DB7,DB6,DB4 = 0, DB5 = 1
	// write to 4 data bits
	write_4_bits(0x2); // write 0010 across D7-D4

	// step 8: Function set command
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);

	// step 9: Display function command
	// Display ON and Cursor ON
	lcd_send_command(LCD_CMD_DISON_CURSON);

	// step 10: Display clear command
	// Display clear (w/ delay following)
	lcd_display_clear();

	// Step 11: Entry mode set
	lcd_send_command(LCD_CMD_INCADD);

}

// write 4 bits of data across D7-D4
static void write_4_bits(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, (value >> 0) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, (value >> 1) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, (value >> 2) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, (value >> 3) & 0x1);

	lcd_enable(); // need to latch data onto lcd after write
}

void lcd_display_clear(void)
{

	lcd_send_command(LCD_CMD_DIS_CLR);

	// Delay of at least 2 ms required per datasheet (pg. 24)
	mdelay(2);
}

void lcd_display_return_home(void)
{
	lcd_send_command(LCD_CMD_DIS_RTN_HOME);

	// Delay of at least 2 ms required per datasheet (pg. 24)
	mdelay(2);
}

/*
 * Set 16 x 2 LCD to specified location given row and column information
 * Row ( 1 to 2)
 * Column (1 to 16)
 */
void lcd_set_cursor(uint8_t row, uint8_t column)
{
	column--;
	switch(row)
	{
		case 1: // Set cursor to 1st row address and add index
			lcd_send_command((column |= 0x80)); // D7 always needs to be kept 1 to change DDRAM address, so 10XX XXXX column offset
			break;
		case 2: // Set cursor to 2nd row address and add index, (11XX XXXX column offset)
			lcd_send_command((column |= 0xC0));
			break;
		default:
			break;
	}
}

static void lcd_enable(void)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, SET);
	udelay(10);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, RESET);
	udelay(100); // execution time > 37 micro seconds
}

void mdelay(uint32_t count)
{
	for(uint32_t i = 0; i < (count * 1000); i++); //milliseconds delay
}

void udelay(uint32_t count)
{
	for(uint32_t i = 0; i < (count * 1); i++); //microseconds delay
}
