/*
 * LED.h
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

#ifndef LED_H_
#define LED_H_


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "led_driver.h"

//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initialize the LED
void led_init(void);


//	Set the rgb value
//	@ param red   : Set the amount of red
//	@ param green : Set the amount of green
//	@ param blue  : Set the amount of blue
//	@ return void
void led_setValue(uint8_t red, uint8_t green, uint8_t blue);


#endif /* LED_H_ */
