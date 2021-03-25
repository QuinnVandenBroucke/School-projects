#include "accelerometer.h"


///     OBJECT DECLARATTIONS
Display screen;
Peripherals pher;


Accelerometer::Accelerometer() : accMeter(PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1) {};



void Accelerometer::init(){
    ///     The FXOS8700 (accelerometer) needs to be enable
    accMeter.enable();


    pher.turnOffRedLED();
    pher.turnOffGreenLED();
}


void Accelerometer::getAccPosition(float fData[]){
    accMeter.getAxis(this->data);
    fData[0] = this->data.x;
    fData[1] = this->data.y;
    fData[2] = this->data.z;
}


void Accelerometer::getAccPosition(MotionSensorDataUnits & cData){
    accMeter.getAxis(cData);
}


void Accelerometer::updateAccPosition(){
    accMeter.getAxis(data);
}


void Accelerometer::visualizePosition(float fAngle){

    ///     Rouding to x decimals
    int iMulitplier = pow(10.0, 2); // 2 = amount of decimal

    float fNewRealX = round(data.x  *  iMulitplier) / iMulitplier; 
    float fNewRealY = round(data.y * iMulitplier) / iMulitplier;


    ///     Check if the new value is something we want to measure
    ///     Or if it's just some variance
    ///     If it's variance, exit the method
    if (fNewRealX == fRealX && fNewRealY == fRealY) 
    {
        return;
    }
    fRealX = fNewRealX;
    fRealY = fNewRealY;


    ///     Get the screen width and height
    int SCREENWIDTH = screen.getWidth();
    int SCREENHEIGHT = screen.getHeight();


    ///     Calculate the angle in G's
    fAngleInG = fAngle / 90;


    ///     Calculate the indicator's x & y values
    int iIndicatorX = iXPos - 1;
    int iIndicatorY = iYPos - 1;
    int iIndicatorSize = 2;


    ///     Calculate the boundry's  x & y values
    ///     fAngleInG * SCREENWIDTH / 2 is to place it to the left or right
    int iBoundrySize = 4;
    int iBoundryX = (SCREENWIDTH / 2) + (fOldAngleInG * SCREENWIDTH / 2) - iBoundrySize / 2;  ///  EX. angle = 0.5 => 64 + (0.5 * 64) - 2 = 94;
    int iBoundryY = (SCREENHEIGHT / 2) - iBoundrySize / 2;


    ///     Now that we have cleared the screen, we can pass the new value of the angle
    fOldAngleInG = fAngleInG;


    ///     Clear the previous indicator & boundry from the screen
    screen.drawFilledRectangle(iIndicatorX, iIndicatorY, iIndicatorSize, iIndicatorSize, true);
    screen.drawRectangle(iBoundryX, iBoundryY, iBoundrySize, iBoundrySize, true);

    ///     Calculate the new x position of the boundry
    iBoundryX = (SCREENWIDTH / 2) + (fAngleInG * SCREENWIDTH / 2) - iBoundrySize / 2;
     


    ///     Checks on which axis we will be using to measure
    bool bUseY;
    float fThreshold = 0.03;
    bUseY = abs(data.y)  > fThreshold + abs(data.x);


    ///     Calculate the x & y position
    iXPos = SCREENWIDTH  / 2  +   (bUseY ?  data.y : data.x)  * SCREENWIDTH  / 2;
    iYPos = SCREENHEIGHT / 2  + (-(bUseY ?  data.x : data.y)) * SCREENHEIGHT / 2;   /// -sign to make the dot move in the right direction 


    ///     Update the indicator values
    iIndicatorX = iXPos - 1;
    iIndicatorY = iYPos - 1;


    ///     Draw the indicator and boundry on screen
    screen.drawFilledRectangle(iIndicatorX, iIndicatorY, iIndicatorSize, iIndicatorSize, false);
    screen.drawRectangle(iBoundryX, iBoundryY, iBoundrySize, iBoundrySize, false);


    ///     Display to the user which axis we are using to measure
    string sDisplayAxis = "Axis: ";
    sDisplayAxis.append(bUseY ? "y" : "x");

    screen.printf(0, 23, sDisplayAxis.c_str());


    ///     Display to the user what the angle is
    string sDisplayAngle = "Angle: %+03.0f deg";
    screen.printFormattedFloat(62, 23, sDisplayAngle.c_str(), fAngle);


    ///     Control the LED: 
    ///     Green LED if the mbed is level with the surface
    ///     Red LED if the mbed is not level with the surface
    if(iIndicatorX  >=  iBoundryX && iIndicatorX + iIndicatorSize <= iBoundryX + iBoundrySize)
    {
        if(iIndicatorY >= iBoundryY && iIndicatorY + iIndicatorSize <= iBoundryY + iBoundrySize)
        {
            pher.turnOnGreenLED();
            pher.turnOffRedLED();
        }
    }
    else 
    {
        pher.turnOffGreenLED();
        pher.turnOnRedLED();
    }
    
}