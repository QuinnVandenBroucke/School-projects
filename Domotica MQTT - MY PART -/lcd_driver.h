/*
 * lcd_driver.h
 *
 *  Created on: 19 nov. 2020
 *      Author: quinn
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------
#include "LPC17xx.h"
#include "spi_driver.h"
#include "timer_driver.h"


// -----------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

//	Initialize the LCD
void lcd_driver_init(void);

//	Send commands to the LCD (through SPI)
//	@ param command : Byte that determines operation of the display
//	@ return void
void lcd_driver_cmd(uint8_t command);


//	Put the cursor at a certain position on the LCD
//	@ param page   : Determines the page on the LCD   (value between 0 - 3  )
//	@ param column : Determines the column on the LCD (value between 0 - 127)
//	@ return void
void lcd_driver_place_cursor(uint8_t page, uint8_t column);


//	Clear the LCD screen
void lcd_driver_clear_screen(void);


//	Draw a character on the LCD screen
//	@ param c : Character that needs to be displayed
//	@ return void
void lcd_driver_draw_char(char c);


//	Draw a string on the screen
//	@ param str : The string that needs to be displayed
//	@ return void
void lcd_driver_draw_string(char * str);


//	Draw a string at a specific position
//	@ param page   : Determines the page on the LCD   (value between 0 - 3  )
//	@ param column : Determines the column on the LCD (value between 0 - 127)
//	@ param str    : The string that needs to be displayed
//	@ return void
void lcd_driver_draw_string_at_position(uint8_t row, uint8_t column, char * str);


//	Draws a fan symbol on the LCD screen
void lcd_driver_draw_fan(void);

#endif /* LCD_DRIVER_H_ */
