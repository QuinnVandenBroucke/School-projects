#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "mbed.h"


///     This class includes all the peripherals
class Peripherals{
    private:
        ///     Constants to turn the LED's on and off
        const int iLEDon = 0;
        const int iLEDoff = 255;

    public:

        /// ------------------------------------------------------------------------------------------------------------
        /// Potentiometer properties
        /// ------------------------------------------------------------------------------------------------------------

        ///     Get the value of the first (left) potentiometer
        ///     @ return void
        float getPot1Value();


        ///     Get the value of the second (right) potentiometer
        ///     @ return void
        float getPot2Value();



        /// ------------------------------------------------------------------------------------------------------------
        /// LED properties
        /// ------------------------------------------------------------------------------------------------------------

        ///     Turn on the red led
        ///     @ return void
        void turnOnRedLED();

        
        ///     Turn off the red led
        ///     @ return void
        void turnOffRedLED();

        
        ///     Turn on the green led
        ///     @ return void
        void turnOnGreenLED();

        
        ///     Turn off the green led
        ///     @ return void
        void turnOffGreenLED();
};

#endif