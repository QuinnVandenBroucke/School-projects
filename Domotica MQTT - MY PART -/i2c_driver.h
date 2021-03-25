/*
 * i2c_driver.h
 *
 *  Created on: 26 okt. 2020
 *      Author: quinn
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "LPC17xx.h"
#include <stdio.h>


//	----------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------

//	Initialize the I2C driver
void i2c_init(void);


//	Receives data from slave
//	@ param address	    : The 7 bit slave address.
//	@ param buff   	    : This is an array to write the receive data in.
//	@ param buff_length : The length of the buffer (in bytes).
//	@ return uint8_t    : Returns the error value (1 = error).
uint8_t i2c_receive(uint8_t address, uint8_t *buff, uint8_t buff_length);


#endif /* I2C_DRIVER_H_ */
