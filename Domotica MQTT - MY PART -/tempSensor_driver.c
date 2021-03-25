/*
 * tempSensor_driver.c
 *
 *  Created on: 4 nov. 2020
 *      Author: quinn
 */

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "tempSensor_driver.h"



//	----------------------------------------------------------------------------
//	CONSTANTS
//	----------------------------------------------------------------------------
#define slave_address 0x48



//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------


void tempSensor_init(void){
	//	Initialize I2C, needed to get the temperature value
	i2c_init();
}


float tempSensor_getValue(){

	int16_t temperature;
	uint8_t buff[2];


	//	Check if there is an error with the slave
	if(i2c_receive(slave_address, buff, 2) == 1){
		printf("Error whilst connecting to slave %x!\n", 0x48);
		return -128;
	}
	else{
		//	buff[0] contains the MSByte of the temperature sensor
		//	buff[1] contains the LSbyte, where the 5 most LSBits
		//	are not taken into account
		temperature = (buff[0] << 8);
		temperature = (temperature | buff[1]) >> 5;

		return (float)temperature * 0.125;
	}
}
