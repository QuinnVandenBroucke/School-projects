/*
 * led_driver.h
 *
 *  Created on: 19 okt. 2020
 *      Author: quinn
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------
#include "LPC17xx.h"
#include "system_LPC17xx.h"


// -----------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

//	Initialize the LED
void led_driver_init(void);


//	Set the rgb value
//	@ param red   : Set the amount of red
//	@ param green : Set the amount of green
//	@ param blue  : Set the amount of blue
//	@ return void
void led_driver_setValue(uint8_t red, uint8_t green, uint8_t blue);


#endif /* LED_DRIVER_H_ */
