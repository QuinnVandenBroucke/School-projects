#include "frame.h"



///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  Frame     /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

char* Frame::buildFrame(float tempVal, float potVal)  {         

    /// SOF
    frame[0] = 0xAA;
    frame[1] = 0xBB;


    /// LEN
    len = id_size + 12;         /// Standard frame = 11 Bytes
    frame[2] = len;             /// Add your own ID = 12 Bytes
                                /// + Id from others (id_size)


    /// IDD
    idd = std::stoi(TcpIP::ip.substr(10,3));    /// Only works in this case (192.168.0.XXX)
    frame[3] = idd;


    /// TMP
    int16_t intTemp = (int16_t) tempVal * 8.0;    /// * 8 to get the correct resolution (shift 3 times)
    frame[4] = intTemp >> 8;                      /// shift so you the leftmost bits get shifted
    frame[5] = intTemp & 0xff;                    /// and so you only have the last 8 bits left


    /// PWM
    int PWMSignal = potVal * 255;
    frame[6] = PWMSignal;


    /// ID0 - IDn
    ID.push_back(117);      /// My IP
    for(int i = 0; i <= id_size; i++){
        frame[8 + i] = ID[i];
    }


    /// EOF
    frame[10 + id_size] = 0xCC;
    frame[11 + id_size] = 0xDD;

    
    /// TUN
    tune++;
    frame[7] = tune;

    ///Increment id_size because we added our own
    id_size++;          

    return frame;
}


tuple<float, int, float> Frame::readFrame(char received[], int size){


    //We take the LEN parameter to know the relevant length
    len = received[2];

    //We only need the ID so the other 11 bytes can go
    id_size = size - 11;


    /// TMP
    temperature = (received[4] * 256 + received[5]) / 8; /// bcs we shifted 8 times to send it (2^8) // / 8 bcs we did *8 to send it

    /// TUNE
    tune = received[7];

    /// PWM
    pwm = (float) received[6] / 255.0;


    ////////////////////////////////////////////////////////////////////////////    WERKT NIET      ////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < id_size ; i++){
        ID.push_back(received[i + 8]);
    }
    
    printf("Relevant length = %i\n", len);
    printf("Amount of id's: %i\n", id_size);

    ////////////////////////////////////////////////////////////////////////////    WERKT NIET      ////////////////////////////////////////////////////////////////////////////
    /// CRC
    crc = received[8 + id_size];


    return make_tuple(temperature, pwm, tune );
}



///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  CRC    ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void Frame::addCRC(int crcVal){

    /// Data we want to send to the crc function
    char dataForCRC[id_size + 6];                   /// Without any ID's we have to 6 bytes to CRC (LEN, IDD, TMP, PWM, TUN)
    
    
    int j = 0;
    for(int i = 2; i < id_size + 8; i++){           /// We need to send 6 packets + id_size (but we start from 2)

        dataForCRC[j] = frame[i];
        j++;
    }

    /// Add CRC to the fame
    frame[8 + id_size] = Crc::crc6(dataForCRC, id_size + 6, crcVal);    /// No ID's => CRC comes on pos 8 in the frame
}


int Frame::checkCRC(char * received){

      /// Data we want to send to the crc function
    char dataForCRC[id_size + 6];                   /// Without any ID's we have to 6 bytes to CRC (LEN, IDD, TMP, PWM, TUN)
    
    
    int j = 0;
    for(int i = 2; i < id_size + 8; i++){           // We need to send 6 packets + id_size (but we start from 2)

        dataForCRC[j] = received[i];
        j++;
    }

    /// Return CRC remainder (should be 0 if data was correct)
    return Crc::crc6(dataForCRC, id_size + 6, crc);      
}

