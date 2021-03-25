#ifndef SENSORS_H
#define SENSORS_H

#include "mbed.h"
#include "LM75B.h"


/// Sensors declares the used sensors
/// Here we can easily add more if necessary
class  Sensors {
    public:
    
        ///////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////  Function Declaration    //////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// Reads the value of the potentiometer
        /// @param void
        /// @return float - value of the potentiometer
        static float readPotMeter(void);

        /// Reads the value of the temperature sensor
        /// @param void
        /// @return float - value of the temperature sensor
        static float readTempSensor(void);

    private:    
};


#endif