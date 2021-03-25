/*
 * potentiometer_driver.h
 *
 *  Created on: 5 okt. 2020
 *      Author: quinn
 */

#ifndef POTENTIOMETER_DRIVER_H_
#define POTENTIOMETER_DRIVER_H_


// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------
#include "LPC17xx.h"
#include <stdio.h>

// -----------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

// Initializes the potentiometer
void pot_init(void);


// Get the potentiometer value
// @ param void
// @ return uint8_t : return the potentiometer value as a value between 0 -> 100
uint8_t pot_getValue (void);


#endif /* POTENTIOMETER_DRIVER_H_ */
