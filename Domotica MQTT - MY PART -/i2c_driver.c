/*
 * i2c_driver.c
 *
 *  Created on: 26 okt. 2020
 *      Author: quinn
 */




//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "i2c_driver.h"



//	----------------------------------------------------------------------------
//	ADDITIONAL INFORMATION
//	----------------------------------------------------------------------------
// DIP 28 = SDA2 (p0.10)
// DIP 27 = SCL2 (p0.11)


//	----------------------------------------------------------------------------
//	CONSTANTS
//	----------------------------------------------------------------------------
#define AA  (1 << 2)
#define SI  (1 << 3)
#define STO (1 << 4)
#define STA (1 << 5)



//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
volatile uint8_t slave_address;
volatile uint8_t *buffer;
volatile uint32_t buffer_length;
volatile uint32_t index;

volatile uint8_t i2c_busy;
volatile uint8_t error;

//	Volatile if the compiler doesn't have to optimize the value
//	(because it can change through the program)



//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------
void i2c_init(void){
	//	Initialize the buffer
	buffer = 0;
	buffer_length = 0;
	i2c_busy = 0;

	//	Enable the power for i2c2
	//	On by default, just to be sure
	LPC_SC->PCONP |= (1 << 26);


	//	Select the peripheral CLK (CCLK = PCLK = 100Mhz)
	LPC_SC->PCLKSEL1 |= (1 << 20);


	//	Select the clock and data line
	LPC_PINCON->PINSEL0 |= (2 << 20);
	LPC_PINCON->PINSEL0 |= (2 << 22);


	//	Enable the pull-up resistors
	LPC_PINCON->PINMODE0 &= ~(3 << 20);
	LPC_PINCON->PINMODE0 &= ~(3 << 22);


	//	Enable the open drain
	LPC_PINCON->PINMODE_OD0 |= (1 << 10);
	LPC_PINCON->PINMODE_OD0 |= (1 << 11);


	//	Enable the i2c interface
	LPC_I2C2->I2CONSET |= (1 << 6);

	//	Set the duty cycle of the clock line
	//	PCLK = 100Mhz
	//	I2Cbitfreq = PCLK / (SCLH + SCLL)
	//	High half word
	LPC_I2C2->I2SCLH = 1000;
	//	Low half word
	LPC_I2C2->I2SCLL = 1000;


	//	Enable interrupts
	NVIC_EnableIRQ(I2C2_IRQn);

	printf("I2C initialized!\n");
}



uint8_t i2c_receive(uint8_t address, uint8_t *buff, uint8_t buff_length){
	//	Set to status to 'busy'
	i2c_busy = 1;

	//	Set the error to false (0)
	error = 0;

	//	Load in the slave address and set read bit
	slave_address = address << 1 | 0x01;

	buffer = buff;
	buffer_length = buff_length;
	index = 0;

	// Trigger the start condition & interrupt
	LPC_I2C2->I2CONSET |= STA;
	LPC_I2C2->I2CONSET |= SI;

	//	We need to wait while the interrupt happens
	while (i2c_busy);

	return error;
}


void I2C2_IRQHandler(void) {

	//	What is the status of i2c
	uint8_t status = LPC_I2C2->I2STAT;


	switch (status) {
		//	start condition has been transmitted
		//	Send the slave address + r/w bit
		//	In case of the transmit -> The start has to be cleared
		case 0x08:
			LPC_I2C2->I2CONCLR = STA;			// Clear start bit
			LPC_I2C2->I2DAT = slave_address; 	// Load the address + r/w bit
			LPC_I2C2->I2CONCLR = SI ; 			// Reset the interrupt
		break;


		case 0x20:
			LPC_I2C2->I2CONSET = STO;
			LPC_I2C2->I2CONCLR = SI;
			i2c_busy = 0;
		break;


		//	Receiver mode
		//	`````````````
		//	Slave address + r bit have been transmitted
		//	-> We received an ACK
		case 0x40:
			//	Check if we want to receive more than 1 byte
			if(buffer_length > 1){
				LPC_I2C2->I2CONSET = AA;  // Return ACK  after data byte is recv
			}
			else{
				LPC_I2C2->I2CONCLR = AA;  // Return NACK after data byte is recv
			}

			//	Clear the interrupt flag
			LPC_I2C2->I2CONCLR = SI;
		break;


		//	Slave address + r bit have been transmitted
		//	-> We received a NACK
		case 0x48:
			//	Send a stop bit
			LPC_I2C2->I2CONSET = STO;
			i2c_busy = 0;

			//	Something went wrong so we return an error
			error = 1;

			//	Clear the interrupt flag
			LPC_I2C2->I2CONCLR = SI;
		break;


		//	Data byte has been received
		//	-> We returned an ACK
		case 0x50:
			//	Load the buffer with the data
			buffer[index] = LPC_I2C2->I2DAT;
			index++;

			//	Check if there is more data to be received
			if (index < buffer_length - 1){
				LPC_I2C2->I2CONSET = AA;  // Return ACK  after data byte is recv
			}
			else{
				LPC_I2C2->I2CONCLR = AA;  // Return NACK after data byte is recv
			}

			//	Clear the interrupt flag
			LPC_I2C2->I2CONCLR = SI;
		break;


		//	Data has been received
		//	-> We returned a NACK
		case 0x58:
			//	Load the buffer with the data
			buffer[index] = LPC_I2C2->I2DAT;
			index++;

			//	Send a stop bit
			LPC_I2C2->I2CONSET = STO;
			i2c_busy = 0;

			//	Clear the interrupt flag
			LPC_I2C2->I2CONCLR = SI;
		break;


		//	Default case
		default:
		break;
	}

}

