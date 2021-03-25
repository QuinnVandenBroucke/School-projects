/*
 ===============================================================================
 Name        : Lab_Programeertechnieken.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */



//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lcd_driver.h"

#include "input_control.h"
#include "LCD.h"
#include "LED.h"
#include "temperature.h"

//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------
void float_to_string(char dest[], float value){
	sprintf(dest, "%.2f", value);
}

void concat_strings(char str1[], char str2[]){
	strcat(str1, str2);
}

void global_init(){
	//	Initialize the LCD
	lcd_init();

	//	LED initialization
	led_init();

	input_control_init();

	temperature_init();

}

//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
char str[2];

int main ( ) {

	global_init();

	//	Clear the screen
	lcd_clear_screen();

	//	Draw the static values on screen
	lcd_draw_fan();
	lcd_draw_string_at_position(0, 65, "ON");		// Start by printing 'on'


	while(1){


		lcd_show_temperature(temperature_getValue());



		//	Check if the joystick is pressed to turn the fan on and off.
		if(joystick_pressed){
			printf("Joystick pressed!\n");

			lcd_toggle_fan_text();

			joystick_pressed = 0;
		}

	}

}

