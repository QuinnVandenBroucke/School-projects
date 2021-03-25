#include "peripherals.h"


///     PHERIPHERAL DECLARATIONS

///     Potentiometers
AnalogIn pot1 (A0);
AnalogIn pot2 (A1);

///     LED
PwmOut r (D5);
PwmOut g (D9);



float Peripherals::getPot1Value(){
    return pot1.read();
}

float Peripherals::getPot2Value(){
    return pot2.read();
}


void Peripherals::turnOnRedLED(){
    r = iLEDon;
}

void Peripherals::turnOffRedLED(){
    r = iLEDoff;
}

void Peripherals::turnOnGreenLED(){
    g = iLEDon;
}

void Peripherals::turnOffGreenLED(){
    g = iLEDoff;
}