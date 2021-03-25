/*
 * input_control.c
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "input_control.h"


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void input_control_init(void){
	joy_init();
	pot_init();
}


uint8_t joystick_getValue(void){
	return joy_getValue();
}


uint8_t potentiometer_getValue (void){
	return pot_getValue();
}
