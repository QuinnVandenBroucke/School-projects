#include "TCP_IP.h"



///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////   Constants & Static declarations     ////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

string TcpIP::ip = "192.168.0.100";
const SocketAddress senderIp("192.168.0.117", 4000);
const SocketAddress subnetMask("255.255.255.0");


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////   Object delcaration     //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/// Create an object of ethernetInterface
EthernetInterface eth;

/// Create 2 sockets
TCPSocket clientSocket;
TCPSocket serverSocket;

/// Create a frame object
Frame f;

/// Create a sensor object
Sensors sens;



void TcpIP::initIp(){
    eth.set_network(senderIp, subnetMask, "192.168.0.1");
    eth.connect();
    serverSocket.open(&eth);
    serverSocket.bind(4000);
    serverSocket.listen();
}


nsapi_error_t TcpIP::send(){
    /// Open socket
    clientSocket.open(&eth);

    /// Set the receiver address
    SocketAddress ipReceiver(ip.c_str(), 4000);

    /// Check connection
    nsapi_error_t result = clientSocket.connect(ipReceiver);

    /// Build the frame
    char *buildedFrame = f.buildFrame(sens.readTempSensor(), sens.readPotMeter());
    
    /// Add crc to frame
    f.addCRC(0x00);

    /// Send the frame
    clientSocket.send(buildedFrame, f.len);

    /// Close the socket
    clientSocket.close();

    return result;
}


int TcpIP::receive(float &temprature, int &tune, int &led){

    /// Bool to check the crc
    bool correct = false;

    /// Open socket to receive on
    TCPSocket *SocketPtr = serverSocket.accept();   /// Returns a pointer to a socket

    /// Maximum length of the Frame should be 33 bytes 
    /// Added some buffer should someone have added more bytes
    char data[35];
    nsapi_error_t err;
    err = SocketPtr->recv(&data, 35);           /// The error returns the amount of bytes that are received
                                                /// We can use this to know the size of the frame

    if (err < 0){
        /// Error
    } 
    else{
        
        /// Asign data to the variables
        tie(temprature, led, tune) = f.readFrame(data, err);

        /// Check if the crc was correct
        if(f.checkCRC(data) == 0){
            correct = true;
        }
        else{
            correct = false;
        }
    }

    // Close the socket
    SocketPtr->close();

    return correct;
}
