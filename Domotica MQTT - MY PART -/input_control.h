/*
 * input_control.h
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

#ifndef INPUT_CONTROL_H_
#define INPUT_CONTROL_H_


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "potentiometer_driver.h"
#include "joystick_driver.h"


//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initializes the joystick and the potentiometer
void input_control_init(void);


//	Read the joystick value
//	@ param void
//	@ return uint8_t : returns the joystick value as an unsigned 8 bit integer
uint8_t joystick_getValue(void);


// Get the potentiometer value
// @ param void
// @ return uint8_t : return the potentiometer value as a value between 0 -> 100
uint8_t potentiometer_getValue (void);

#endif /* INPUT_CONTROL_H_ */
