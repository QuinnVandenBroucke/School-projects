#include "crc.h"

int Crc::crc6(char * message, int size, int crcValue){
    
    int crcRegister = 0b0000000;
    /// Polynomial value
    const int divider = 0b01010011;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < 8; j++){

            /// Load your crc register
            crcRegister <<= 1;
            crcRegister += ((message[i] >> (7-j)) & 0b00000001);

            /// Check if value = 1
            if((crcRegister & 0b01000000) == 0b01000000){
                
                /// XOR
                crcRegister ^= divider;
            }
        }
    }
    /// Add your crc to the crc Register
    for(int i = 0; i < 6; i++){
        crcRegister <<= 1;
        crcRegister += ((crcValue >> (5-i)) & 0b00000001);
        
        if((crcRegister & 0b01000000) == 0b01000000){
            crcRegister ^= divider;
        }
    }
    
    /// Return the result
    return crcRegister;

}