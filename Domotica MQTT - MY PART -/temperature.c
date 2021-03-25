/*
 * temperature.c
 *
 *  Created on: 2 dec. 2020
 *      Author: quinn
 */

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "temperature.h"


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------


void temperature_init(void){
	tempSensor_init();
}

float temperature_getValue(void){
	return tempSensor_getValue();
}
