#include "sensors.h"

AnalogIn potSensor (A0);
LM75B tempSensor (D14, D15);

float Sensors::readPotMeter(){
    return potSensor;
}

float Sensors::readTempSensor(){
    return tempSensor.temp();
}