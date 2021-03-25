/*
 * tempSensor_driver.h
 *
 *  Created on: 4 nov. 2020
 *      Author: quinn
 */

#ifndef TEMPSENSOR_DRIVER_H_
#define TEMPSENSOR_DRIVER_H_

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "LPC17xx.h"
#include "i2c_driver.h"
#include <stdio.h>


//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initialize the temperature sensor
void tempSensor_init(void);


//	Receive the temperature from the LM75B (temperature sensor)
//	@ return float : Returns the temperature as a float. If the value is -128 an
//					error has occurred.
float tempSensor_getValue(void);

#endif /* TEMPSENSOR_DRIVER_H_ */
