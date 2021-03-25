/*
 * LCD.h
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

#ifndef LCD_H_
#define LCD_H_


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "lcd_driver.h"

#include <stdio.h>
#include <string.h>


// -----------------------------------------------------------------------------
// GLOBAL VARIABLES
// -----------------------------------------------------------------------------
extern uint8_t fan_mode;


//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initialize the LCD
void lcd_init(void);


//	Put the cursor at a certain position on the LCD
//	@ param page   : Determines the page on the LCD   (value between 0 - 3  )
//	@ param column : Determines the column on the LCD (value between 0 - 127)
//	@ return void
void lcd_place_cursor(uint8_t page, uint8_t column);


//	Clear the LCD screen
void lcd_clear_screen(void);


//	Draw a character on the LCD screen
//	@ param c : Character that needs to be displayed
//	@ return void
void lcd_draw_char(char c);


//	Draw a string on the screen
//	@ param str : The string that needs to be displayed
//	@ return void
void lcd_draw_string(char * str);


//	Draw a string at a specific position
//	@ param page   : Determines the page on the LCD   (value between 0 - 3  )
//	@ param column : Determines the column on the LCD (value between 0 - 127)
//	@ param str    : The string that needs to be displayed
//	@ return void
void lcd_draw_string_at_position(uint8_t row, uint8_t column, char * str);


//	Draws a fan symbol on the LCD screen
void lcd_draw_fan(void);


//	Display fan on off text
//	@ param mode: A bit that detmines if the fan is on (1) or off (0)
//	@ return void
void lcd_fan_mode(uint8_t mode);


//	Toggle between on and off
void lcd_toggle_fan_text(void);


//	Display the temperature on screen
//	@ param temperature : the temperature that needs to be displayed
//	@ return void
void lcd_show_temperature(float temperature);

#endif /* LCD_H_ */
