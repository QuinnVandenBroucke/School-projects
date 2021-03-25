#ifndef CRC_H
#define CRC_H

/// Handles the crc encryption and decryption
class Crc{
    public:
        /// Calculates the CRC
        /// @param char* message - contains the data on wich the crc will be executed
        /// @param int size - contains the size of message
        /// @param int crcValue - crc value that is received from the frame (insert 0x00 if you need to send the frame)
        /// @return int - returns calculated value
        static int crc6(char* message, int size, int crcValue);   
};


#endif