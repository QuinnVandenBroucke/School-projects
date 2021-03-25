/*
 * temperature.h
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "tempSensor_driver.h"


//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initialize the temperature sensor
void temperature_init(void);


//	Receive the temperature from the LM75B (temperature sensor)
//	@ return float : Returns the temperature as a float. If the value is -128 an
//					error has occurred.
float temperature_getValue(void);


#endif /* TEMPERATURE_H_ */
