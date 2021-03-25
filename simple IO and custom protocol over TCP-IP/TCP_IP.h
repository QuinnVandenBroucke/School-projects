#ifndef TCP_IP_H
#define TCP_IP_H

#include <string>
#include "mbed.h"
#include "EthernetInterface.h"
#include "frame.h"
#include "sensors.h"


/// TcpIP zorgt voor het verzenden en ontvangen van de frames
class TcpIP{
    public:

        ///////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////  Function Declaration    ///////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// Initilize the tcp components
        /// @param void
        /// @return void
        void initIp(void);

        /// Sends the data
        /// @param void
        /// @return nsapi_error_t - returns an integer that represents an error
        nsapi_error_t send(void);

        /// Receives a frame
        /// @param float &temperature - pass the temperature by reference
        /// @param int &tune - pass the tune variable by reference
        /// @param int &led - pass the led variable by reference
        int receive(float &temperature, int &tune, int &led);
    

        ///////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////  Variable Declaration    ///////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// ip stores the users complete IP
        static string ip;

    private:
};


#endif