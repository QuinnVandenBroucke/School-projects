/*
 * lcd_driver.c
 *
 *  Created on: 19 nov. 2020
 *      Author: quinn
 */


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "lcd_driver.h"

//	----------------------------------------------------------------------------
//	ADDITIONAL INFORMATION
//	----------------------------------------------------------------------------

//	MOSI  	: DIP 5  = p0.9		(Master out, slave in)
//	RESET 	: DIP 6  = p0.8		(Reset)
//	SCK	  	: DIP 7  = p0.7		(Serial clock)
//	LCD_A0	: DIP 8  = p0.6		(Register select (0 = instruction) (1 = data))
//	LCD_CS_N: DIP 11 = p0.18	(Slave select)



//	----------------------------------------------------------------------------
//	CONSTANTS
//	----------------------------------------------------------------------------

//	Fan bitmap
const unsigned char fan[4][4][8] = {
		{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		 {0x00, 0x00, 0x0C, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF},
		 {0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0, 0x00, 0x00},
		 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		 {0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x8F},
		 {0x8F, 0x1F, 0x1F, 0x1F, 0x07, 0x01, 0x00, 0x00},
		 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
		{{0x80, 0xE0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE},
		 {0xFE, 0xFC, 0xE0, 0x00, 0x00, 0x06, 0x0F, 0x1F},
		 {0x1F, 0x8F, 0xC6, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0},
		 {0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0}},
		{{0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F},
		 {0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		 {0x00, 0x00, 0x01, 0x07, 0x1F, 0x1F, 0x1F, 0x1F},
		 {0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x00}}
};


//	Font table
const unsigned char font[96][8] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // space
	{0x00,0x5f,0x00,0x00,0x00,0x00,0x00,0x00}, // !
	{0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00}, // "
	{0x0a,0x1f,0x0a,0x1f,0x0a,0x00,0x00,0x00}, // #
	{0x24,0x2a,0x2a,0x7f,0x2a,0x2a,0x12,0x00}, // $
	{0x00,0x47,0x25,0x17,0x08,0x74,0x52,0x71}, // %
	{0x00,0x36,0x49,0x49,0x49,0x41,0x41,0x38}, // &
	{0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00}, // '
	{0x00,0x3e,0x41,0x00,0x00,0x00,0x00,0x00}, // (
	{0x41,0x3e,0x00,0x00,0x00,0x00,0x00,0x00}, // )
	{0x04,0x15,0x0e,0x15,0x04,0x00,0x00,0x00}, // *
	{0x08,0x08,0x3e,0x08,0x08,0x00,0x00,0x00}, // +
	{0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00}, // ,
	{0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // -
	{0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00}, // .
	{0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00}, // /
	{0x00,0x3e,0x61,0x51,0x49,0x45,0x43,0x3e}, // 0
	{0x01,0x01,0x7e,0x00,0x00,0x00,0x00,0x00}, // 1
	{0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x46}, // 2
	{0x41,0x49,0x49,0x49,0x49,0x49,0x36,0x00}, // 3
	{0x00,0x0f,0x10,0x10,0x10,0x10,0x10,0x7f}, // 4
	{0x00,0x4f,0x49,0x49,0x49,0x49,0x49,0x31}, // 5
	{0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x30}, // 6
	{0x01,0x01,0x01,0x01,0x01,0x01,0x7e,0x00}, // 7
	{0x00,0x36,0x49,0x49,0x49,0x49,0x49,0x36}, // 8
	{0x00,0x06,0x49,0x49,0x49,0x49,0x49,0x3e}, // 9
	{0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // :
	{0x40,0x34,0x00,0x00,0x00,0x00,0x00,0x00}, // ;
	{0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x00}, // <
	{0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00}, // =
	{0x22,0x14,0x08,0x00,0x00,0x00,0x00,0x00}, // >
	{0x00,0x06,0x01,0x01,0x59,0x09,0x09,0x06}, // ?
	{0x00,0x3e,0x41,0x5d,0x55,0x5d,0x51,0x5e}, // @
	{0x00,0x7e,0x01,0x09,0x09,0x09,0x09,0x7e}, // A
	{0x00,0x7f,0x41,0x49,0x49,0x49,0x49,0x36}, // B
	{0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x22}, // C
	{0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x3e}, // D
	{0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x41}, // E
	{0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x01}, // F
	{0x00,0x3e,0x41,0x49,0x49,0x49,0x49,0x79}, // G
	{0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x7f}, // H
	{0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // I
	{0x00,0x38,0x40,0x40,0x41,0x41,0x41,0x3f}, // J
	{0x00,0x7f,0x08,0x08,0x08,0x0c,0x0a,0x71}, // K
	{0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x40}, // L
	{0x00,0x7e,0x01,0x01,0x7e,0x01,0x01,0x7e}, // M
	{0x00,0x7e,0x01,0x01,0x3e,0x40,0x40,0x3f}, // N
	{0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x3e}, // O
	{0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x06}, // P
	{0x00,0x3e,0x41,0x41,0x71,0x51,0x51,0x7e}, // Q
	{0x00,0x7e,0x01,0x31,0x49,0x49,0x49,0x46}, // R
	{0x00,0x46,0x49,0x49,0x49,0x49,0x49,0x31}, // S
	{0x01,0x01,0x01,0x7f,0x01,0x01,0x01,0x00}, // T
	{0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x3f}, // U
	{0x00,0x0f,0x10,0x20,0x40,0x20,0x10,0x0f}, // V
	{0x00,0x3f,0x40,0x40,0x3f,0x40,0x40,0x3f}, // W
	{0x00,0x63,0x14,0x08,0x08,0x08,0x14,0x63}, // X
	{0x00,0x07,0x08,0x08,0x78,0x08,0x08,0x07}, // Y
	{0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x47}, // Z
	{0x00,0x7f,0x41,0x00,0x00,0x00,0x00,0x00}, // [
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // "\"
	{0x41,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // ]
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // ^
	{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00}, // _
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // `
	{0x00,0x7e,0x01,0x09,0x09,0x09,0x09,0x7e}, // A
	{0x00,0x7f,0x41,0x49,0x49,0x49,0x49,0x36}, // B
	{0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x22}, // C
	{0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x3e}, // D
	{0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x41}, // E
	{0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x01}, // F
	{0x00,0x3e,0x41,0x49,0x49,0x49,0x49,0x79}, // G
	{0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x7f}, // H
	{0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // I
	{0x00,0x38,0x40,0x40,0x41,0x41,0x41,0x3f}, // J
	{0x00,0x7f,0x08,0x08,0x08,0x0c,0x0a,0x71}, // K
	{0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x40}, // L
	{0x00,0x7e,0x01,0x01,0x7e,0x01,0x01,0x7e}, // M
	{0x00,0x7e,0x01,0x01,0x3e,0x40,0x40,0x3f}, // N
	{0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x3e}, // O
	{0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x06}, // P
	{0x00,0x3e,0x41,0x41,0x71,0x51,0x51,0x7e}, // Q
	{0x00,0x7e,0x01,0x31,0x49,0x49,0x49,0x46}, // R
	{0x00,0x46,0x49,0x49,0x49,0x49,0x49,0x31}, // S
	{0x01,0x01,0x01,0x7f,0x01,0x01,0x01,0x00}, // T
	{0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x3f}, // U
	{0x00,0x0f,0x10,0x20,0x40,0x20,0x10,0x0f}, // V
	{0x00,0x3f,0x40,0x40,0x3f,0x40,0x40,0x3f}, // W
	{0x00,0x63,0x14,0x08,0x08,0x08,0x14,0x63}, // X
	{0x00,0x07,0x08,0x08,0x78,0x08,0x08,0x07}, // Y
	{0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x47}, // Z
	{0x08,0x36,0x41,0x00,0x00,0x00,0x00,0x00}, // {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // |
	{0x41,0x36,0x08,0x00,0x00,0x00,0x00,0x00}, // }
	{0x02,0x01,0x01,0x02,0x02,0x01,0x00,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};



//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void lcd_driver_init(){

	//	Initialize SPI, needed to send data / commands to the LCD
	spi_init();

	//	LCD needs 6V supply.
	//	Can be generated by voltage pumps, but not instantly.
	//	Need to reset the display, and let it 'charge' up.

	LPC_GPIO0->FIOCLR = (1 << 8);	// p0.8 = RESET (active low)
	timer_wait_us(50);				// Wait for 50 us
	LPC_GPIO0->FIOSET = (1 << 8);	// p0.8 = RESET (active low)
	timer_wait_ms(5);				// Wait for 5  ms

	//sequence of commands for initializing the LCD
	lcd_driver_cmd(0xAE);	// Turn off display
	lcd_driver_cmd(0xA2);	// Set the bias voltage ratio  				(1/9 bias   )
	lcd_driver_cmd(0xA0);	// Set RAM address SEG output  	    		(A0: normal )
							//									 		(A1: reverse)
	lcd_driver_cmd(0xC8);	// Select COM output direction 				(column     )
	lcd_driver_cmd(0x22);	// Select internal resistor ratio			(Rb/Ra = 2  )
	lcd_driver_cmd(0x2F);	// Select internal power supply oper. mode	(= 7        )
	lcd_driver_cmd(0x40);	// Start line address						(= 0        )
	lcd_driver_cmd(0xAF);	// Turn on display
	lcd_driver_cmd(0x81);	// Set contrast
	lcd_driver_cmd(0x17);	// Set contrast
	lcd_driver_cmd(0xA6);	// Set the lcd display to normal
	lcd_driver_cmd(0xE0);	// Auto increment the column after a write


	printf("LCD initialized\n");
}

//	Send a command to the LCD
void lcd_driver_cmd(uint8_t command){
	//	To send commands A0 needs to be pulled down
	LPC_GPIO0->FIOCLR = (1 << 6);

	//	Send the command
	spi_sendData(command);

	//	Set A0 high again so we can send data
	LPC_GPIO0->FIOSET = (1 << 6);
}

void lcd_driver_place_cursor(uint8_t row, uint8_t column){
	//	Check if row is on the lcd
	if (row > 3){
		row = 0;
	}

	//	Check if column is on the lcd
	if (column > 127){
		column = 0;
	}

	//	Set the page
	row = (row & 0x03);		// Gives 0000 'row address'
	lcd_driver_cmd(0xB0 | row);

	//	Set the most significant 4 bits of the column
	char column_high = (column >> 4);	// Gives: 0000 'column high nibble'
	lcd_driver_cmd(0x10 | column_high);

	//	Set the least significant 4 bits of the column
	char column_low = (column & 0x0F);	// Gives: 0000 'column low  nibble'
	lcd_driver_cmd(0x00 | column_low);
}

void lcd_driver_clear_screen(){
	//	Loop over every page
	for(int i = 0; i < 4; i++){

		//	Set the page address
		lcd_place_cursor(i, 0);

		//	Loop over every column
		//	Columns auto-increment, so no need to set them)
		for(int j = 0; j < 128; j++){
			spi_sendData(0x00);
		}
	}
}



void lcd_driver_draw_char(char c){

	//	Get the index of the char
	c = c & 0x7F;	//	Highest ASCII char is 0x7F

	//	If we subtract the 'space' (decimal = 32) from the char, we get the
	//	position of the char in the array
	//	EX. if our char is '!' (decimal = 33) - 'space' (decimal = 32) we get
	//	the index of the '!' char, position 1 in the array.
	c -= ' ';

	for(int i = 0; i < 8; i++){
		spi_sendData(font[(uint8_t)c][i]);
	}
}

void lcd_driver_draw_string(char * str){
	//	Dereference the string
	while(*str){
		//	Draw the char and move on to the next one
		lcd_draw_char(*str++);
	}
}

void lcd_driver_draw_string_at_position(uint8_t row, uint8_t column, char * str){
	//	Set the cursor at the correct position
	lcd_place_cursor(row, column);

	//	Call draw string function
	lcd_draw_string(str);
}

void lcd_driver_draw_fan(){
	//	Navigate over the pages
	for(int i = 0; i < 4; i++){
		lcd_place_cursor(i, 90);
		//	Navigate over the sections
		for(int j = 0; j < 4; j++){
			//	Navigate over the columns
			for(int k = 0; k < 8; k++){
				spi_sendData(fan[i][j][k]);
			}
		}
	}
}

