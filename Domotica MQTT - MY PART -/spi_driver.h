/*
 * spi_driver.c
 *
 *  Created on: 6 nov. 2020
 *      Author: quinn
 */

#ifndef SPI_DRIVER_C_
#define SPI_DRIVER_C_

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "LPC17xx.h"
#include <stdio.h>


//	----------------------------------------------------------------------------
//	FUNCTION DECLARATION
//	----------------------------------------------------------------------------

//	Initializes the SPI driver
void spi_init(void);

//	Send data over SPI
//	@ param data : The byte you want to send
//	@ return void
void spi_sendData(uint8_t data);


#endif /* SPI_DRIVER_C_ */
