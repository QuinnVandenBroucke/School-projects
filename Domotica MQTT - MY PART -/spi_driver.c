/*
 * spi_driver.c
 *
 *  Created on: 6 nov. 2020
 *      Author: quinn
 */


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "spi_driver.h"


//	----------------------------------------------------------------------------
//	ADDITIONAL INFORMATION
//	----------------------------------------------------------------------------

//	MOSI  	: DIP 5  = p0.9		(Master out, slave in)
//	RESET 	: DIP 6  = p0.8		(Reset)
//	SCK	  	: DIP 7  = p0.7		(Serial clock)
//	LCD_A0	: DIP 8  = p0.6		(Register select (0 = instruction) (1 = data))
//	LCD_CS_N: DIP 11 = p0.18	(Slave select)

//	We will be using SSP1 for the SPI since SPI is a legacy peripheral


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void spi_init(void){


	//	Enable power
	//	On by default, but just in case
	LPC_SC->PCONP |= (1 << 10);

	//	Enable the clock and use PCLK = CCLK = 100MHz
	LPC_SC->PCLKSEL0 |= (1 << 20);

	//	Divide the clock so that SPI has a clock of 1MHZ
	//	(Only even numbers)
	LPC_SSP1->CPSR |= 100;

	//	Pin configuration
	LPC_PINCON->PINSEL0 |=  (2 << 14);	// p0.7  = SCK1
	LPC_PINCON->PINSEL0 |=  (2 << 18); 	// p0.9  = MOSI
	LPC_PINCON->PINSEL0 &= ~(3 << 16); 	// p0.8  = RESET
	LPC_PINCON->PINSEL0 &= ~(3 << 12); 	// p0.6  = REGISTER SELECT
	LPC_PINCON->PINSEL1 &= ~(3 << 4 ); 	// p0.18 = CS

	//	Set desired pins as output
	LPC_GPIO0->FIODIR |= (1 << 6 ); 	// p0.6  = REGISTER SELECT
	LPC_GPIO0->FIODIR |= (1 << 8 ); 	// p0.8  = RESET
	LPC_GPIO0->FIODIR |= (1 << 18); 	// p0.18 = CS

	//	SSP Control register
	//	````````````````````
	//	Transfer 8 bits
	LPC_SSP1->CR0 |= (7 << 0);

	//	Clock polarity and clock phase
	//	By default, the clock is low and the data is sampled on the rising edge
	//	& shifted on the falling edge
	//	LPC_SSP1->CR0 |= (1 << 6);	// Set clock polarity to high
	//	LPC_SSP1->CR0 |= (1 << 7);	// Invert clock phase

	//	Enable SSP1
	LPC_SSP1->CR1 |= (1 << 1);

	//	Enable master mode
	//	On by default, but just in case
	LPC_SSP1->CR1 &= ~(1 << 2);


	//	The CS and RESET are active low and we will always send data (1)
	LPC_GPIO0->FIOSET |= (1 << 6 ); 	// p0.6  = REGISTER SELECT
	LPC_GPIO0->FIOSET |= (1 << 8 ); 	// p0.8  = RESET
	LPC_GPIO0->FIOSET |= (1 << 18);		// p0.18 = CS


	printf("SPI initialized\n");
}


void spi_sendData(uint8_t data){

	//	Select the slave (LCD in our case, active low)
	LPC_GPIO0->FIOCLR = 1 << 18;

	//	Send the data
	LPC_SSP1->DR = data;

	//	Check if the SSPn controller is sending/receiving a frame
	while ((LPC_SSP1->SR & (1 << 4))){
		//	Busy waiting
	}

	//	Release the slave
	LPC_GPIO0->FIOSET = 1 << 18;
}
