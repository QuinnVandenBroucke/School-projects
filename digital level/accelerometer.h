#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "FXOS8700Q.h"
#include "display.h"
#include "peripherals.h"
#include <cmath>
#include <string>


///     This class handles everything that has to do with the accelerometer FXOS8700Q
class Accelerometer{

    private:
        ///     MMA7660 variable 
        FXOS8700Q_acc accMeter;


        ///     Holds the X and Y position of the indicator
        int iXPos;
        int iYPos;


        ///     The angle that the users has entered expressed in G
        float fAngleInG;
        float fOldAngleInG = 0; 


        ///     Used to check if the data really changed or if it's just some variance
        float fRealX;
        float fRealY;


        ///     Struct that holds the x, y and z values of the accelerometer
        MotionSensorDataUnits data;


    public:
        ///     Constructor
        Accelerometer();


        ///     Initialize the components
        ///     @ return void
        void init();


        ///     Get the data from the accelerometer
        ///     @ param fData[] : a float array
        ///     @ return void
        void getAccPosition(float fData[]); /// In g's


        ///     Get the data from the accelerometer
        ///     @ param cData : MotionSensorDataUnits address
        ///     @ return void
        void getAccPosition(MotionSensorDataUnits & cData);


        ///     Update the accelerometer position
        ///     @ return void
        void updateAccPosition();


        ///     Display the indicator and boundry
        ///     `````````````````````````````````
        ///     Display an indicator (filled rectangle) and a boundry (rectangle) on the screen depending on 
        ///         on the acceleromter orientation and the angle that has been entered by the user
        ///     @ param fAngle : a float that is the angle entered by the user
        ///     @ return void
        void visualizePosition(float fAngle);
};

#endif