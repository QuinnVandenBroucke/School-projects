#ifndef FRAME_H
#define FRAME_H

#include "mbed.h"
#include "TCP_IP.h"
#include "crc.h"
#include <string>
#include <vector>
#include <tuple>


/// Frame class builds & deconstructs the frame
/// It also adds & and checks the crc
class  Frame {
    public:

        ///////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////  Function Declaration    ////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// Insert all the correct values in the frame array
        /// @param float tempVal - Temperature as a float
        /// @param float potVal - Potentiometer value range(0 - 255)
        /// @return char* buildframe - Returns a frame where all values (except crc) are filled in
        char* buildFrame(float tempVal, float potVal);

        /// Adds crc value to the correct frame position
        /// @param int crcVal - Value that will be added in calculation the CRC (should be 0x00)
        /// @return void
        void addCRC(int crcVal);

        /// Reads a received frame
        /// @param char * received - Frame that we received from the sender
        /// @param int size - Size of the received frame
        /// @return float - Returns the temperature
        /// @return float - Returns the value of the potentiometer (for the led)
        /// @return int = Returns the tune
        tuple<float, int, float> readFrame(char * received, int size);

        /// Checks if the received crc is correct
        /// @param char * received - Frame that we received from the sender
        /// @return int - Returns the remainder after CRC calculations
        int checkCRC(char * received);
        
        

        ///////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////  Public Variables    /////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// Length is the total length of the received frame
        int len;        /// 1 byte


    private:

        ///////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////  Private Variables    /////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////
        
        /// Frame will be filled up with all the different bytes (SOF, LEN,...)
        char frame[35];     /// 35 bytes to add a buffer if someone adds to many things to the frame

        /// ID of the destination mbed
        int idd;        /// 1 byte

        /// Temprature as a float
        float temperature;      /// 2 bytes

        /// Tune to select frequency, length and delay (Default value = 0)
        int tune = 0;       /// 1 byte

        /// Pwm value is the value of the potentiometer
        float pwm;      /// 1 byte

        /// ID is an int vector containing all the ID's of the devices
        vector <int> ID;        /// n bytes (n = number of devices)
        
        /// id_size is the amount of ID's in the frame
        int id_size = 0;
        
        /// CRC contains the CRC remainder
        int crc;        /// 1 byte
};


#endif