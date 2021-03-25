/*
 * joystick_driver.h
 *
 *  Created on: 12 okt. 2020
 *      Author: quinn
 */

#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_


// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------
#include "LPC17xx.h"
#include <assert.h>
#include <stdio.h>
#include "timer_driver.h"


// -----------------------------------------------------------------------------
// GLOBAL VARIABLES
// -----------------------------------------------------------------------------
extern uint8_t joystick_pressed;


// -----------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

//	Initializes the joystick
void joy_init(void);


//	Read the joystick value
//	@ param void
//	@ return uint8_t : returns the joystick value as an unsigned 8 bit integer
uint8_t joy_getValue(void);


#endif /* JOYSTICK_DRIVER_H_ */
