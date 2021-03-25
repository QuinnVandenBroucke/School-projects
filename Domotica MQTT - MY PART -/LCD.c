/*
 * LCD.c
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------

#include "LCD.h"


//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
uint8_t fan_mode = 0;
float temperature = 0;
char temp[2];

//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------


void lcd_init(void){
	lcd_driver_init();

	//	Set the fan text to off
    fan_mode = 0;
}

void lcd_place_cursor(uint8_t page, uint8_t column){
	lcd_driver_place_cursor(page, column);
}

void lcd_clear_screen(void){
	lcd_driver_clear_screen();
}

void lcd_draw_char(char c){
	lcd_driver_draw_char(c);
}

void lcd_draw_string(char * str){
	lcd_driver_draw_string(str);
}

void lcd_draw_string_at_position(uint8_t row, uint8_t column, char * str){
	lcd_driver_draw_string_at_position(row, column, str);
}

void lcd_draw_fan(void){
	lcd_driver_draw_fan();
}

void lcd_fan_mode(uint8_t mode){
	if(mode == 0){
		lcd_draw_string_at_position(0, 65, "    ");
		lcd_draw_string_at_position(1, 65, "OFF");
	}
	else if(mode == 1){
		lcd_draw_string_at_position(0, 65, "ON");
		lcd_draw_string_at_position(1, 65, "    ");
	}
}

void lcd_toggle_fan_text(void){
	//	Display the fan text
	if(fan_mode == 0){
		lcd_draw_string_at_position(0, 65, "    ");
		lcd_draw_string_at_position(1, 65, "OFF");
	}
	else if(fan_mode == 1){
		lcd_draw_string_at_position(0, 65, "ON");
		lcd_draw_string_at_position(1, 65, "    ");
	}

	//	Toggle the fan_mode variable
	if(fan_mode == 0){
		fan_mode = 1;
	}
	else if(fan_mode == 1){
		fan_mode = 0;
	}
}

void lcd_show_temperature(float temperature){
	sprintf(temp, "%.2f", temperature);

	//	Display temperature on screen
	lcd_draw_string_at_position(2, 0, temp);
	lcd_draw_string_at_position(3, 0, "degrees");
}

