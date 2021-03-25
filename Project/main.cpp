 
//#include "mbed.h"
#include "display.h"
#include "accelerometer.h"
#include "peripherals.h"
#include <cmath>


//  --------------------------------------------------------------------------------------------------------------------
//  Object Declaration
//  --------------------------------------------------------------------------------------------------------------------

///     Create an accelerometer object
Accelerometer acceleroMeter;

///     Create an display object 
Display lcd;

///     Create a peripheral object
Peripherals peripherals;

///     Enum for the joystick
enum joystickMovement {Up, Right, Down, Left, Pressed, Released};
joystickMovement joystickPosition;



//  --------------------------------------------------------------------------------------------------------------------
//  Variable declaration
//  --------------------------------------------------------------------------------------------------------------------

///     2 ways to read data from the accelerometer
float fAccelerometerData[3];
MotionSensorDataUnits acceleroData;

///     Variables used to represent the angle
float fAngle;
float fTens;
float fUnits;
float fPot1Value;
float fOldPot1Value;
float fPot2Value;
const int iUnitsMaxX = 5;
const int iUnitsMinX = -5;
const int iTensMaxX = 85;
const int iTensMinX = -85;



//  --------------------------------------------------------------------------------------------------------------------
//  Interrupt Implementation
//  --------------------------------------------------------------------------------------------------------------------

///     Interrupts
InterruptIn joystickDown(A3);
InterruptIn joystickUp(A2);
InterruptIn joystickPressed(D4);
InterruptIn joystickRight(A5);
InterruptIn joystickLeft(A4);


///     Functions that get called from interrupt
void ButtonDown(){
    joystickPosition = Down;
}
void ButtonUp(){
    joystickPosition = Up;
}
void ButtonPressed(){
    joystickPosition = Pressed;
}
void ButtonRight(){
    joystickPosition = Right;
}
void ButtonLeft(){
    joystickPosition = Left;
}



//  --------------------------------------------------------------------------------------------------------------------
//  State Machine
//  --------------------------------------------------------------------------------------------------------------------

///     States for the state machine
enum states{S_INIT, S_MENU, S_ACCELEROMETERDATA, S_LEVELING, S_ANGLE};


///     Properties of the states
struct stateProperties{
    states currentState = S_INIT;
    states previousState = S_LEVELING;
    bool error = false;
}s;


void stateMachine(){

    switch(s.currentState){
        //  ------------------------------------------------------------------------------------------------------------
        case S_INIT:
        //  ------------------------------------------------------------------------------------------------------------
            if(s.currentState != s.previousState)
            {
                s.previousState = S_INIT;
                acceleroMeter.init();
            }

            ///     Go to the menu state
            s.currentState = S_MENU;
        break;

        //  ------------------------------------------------------------------------------------------------------------
        case S_MENU:
        //  ------------------------------------------------------------------------------------------------------------
            if(s.currentState != s.previousState)
            {
                s.previousState = S_MENU;

                ///     Display the text on the screen
                lcd.printf(0, lcd.getVerticalCursorPos(), ">");
                lcd.printf(10, 0, "Accelerometer data");
                lcd.printf(10, 10, "Start Leveling");
                lcd.printf(10, 20, "Set the measuring angle");
            }


            ///     Checks the position of the cursor
            if(joystickPosition == Down){
                lcd.moveCursorDown();
            }
            else if(joystickPosition == Up){
                lcd.moveCursorUp();
            }
            else if (joystickPosition == Pressed) {
                int cursorPos = lcd.getVerticalItemSelector();
                
                     if (cursorPos == 0) s.currentState = S_ACCELEROMETERDATA;
                else if (cursorPos == 1) s.currentState = S_LEVELING;
                else if (cursorPos == 2) s.currentState = S_ANGLE;
            }


            ///     Place the joystick in Released position so that we don't move 2 positions
            joystickPosition = Released; 
        break;

        // -------------------------------------------------------------------------------------------------------------
        case S_ACCELEROMETERDATA:
        // -------------------------------------------------------------------------------------------------------------
            if(s.currentState != s.previousState)
                {
                    s.previousState = S_ACCELEROMETERDATA;
                    
                    ///     Display this on screen
                    lcd.clearScreen();
                    lcd.printf(0,  0, "X value: ");
                    lcd.printf(0, 10, "Y value: ");
                    lcd.printf(0, 20, "Z value: ");
                }

                ///     Get the accelerometer values and print them
                acceleroMeter.getAccPosition(acceleroData);
                lcd.printf(40,  0, acceleroData.x);
                lcd.printf(40, 10, acceleroData.y);
                lcd.printf(40, 20, acceleroData.z);
        break;

        // -------------------------------------------------------------------------------------------------------------
        case S_LEVELING:
        // -------------------------------------------------------------------------------------------------------------
            if(s.currentState != s.previousState)
            {
                s.previousState = S_LEVELING;
                lcd.clearScreen();
            }
            
            ///     Update the accelerometer data
            acceleroMeter.updateAccPosition();
            
            
            ///     Draw a boundry and an indicator depending on the angle entered by the user
            acceleroMeter.visualizePosition(fAngle);

        break;

        // -------------------------------------------------------------------------------------------------------------
        case S_ANGLE:
        // -------------------------------------------------------------------------------------------------------------
            if(s.currentState != s.previousState)
            {
                s.previousState = S_ANGLE;

                lcd.clearScreen();
                lcd.printf(0, 0, "Choose your angle: ");
                lcd.printf(104, 0, "deg"); 

                fOldPot1Value = 0;
            }
            
            /// Change the angle value with the 2 potentiometers
            /// ````````````````````````````````````````````````
            ///     With the left potentiometer we want to display values between -85 and 85.
            ///         If the potentiometer is turned, only the tens should change.
            ///     With the right potentiometer it's possible to do 'fine tuning'.
            ///         It changes between -5 and 5.

            ///     The pot meter has a value between '0' en '1'
            ///         We have to normalize the values, for this we use Unity-based normalization

            ///     Unity-based normalization: Z = (X - Min(X)) / (Max(X) - Min(X))
            ///         -> Z = normalized value (so the pot value)
            ///         -> X = the values we want to have (tens : -85 -> 85
            ///                                            units: -5  -> 5);


            ///     We read the value from the potentiometer
            fPot1Value = peripherals.getPot1Value();
            fPot1Value = fPot1Value*(iTensMaxX - iTensMinX) + iTensMinX;

            ///     We want to know the ten of the number
            fPot1Value = (int) fPot1Value / 10 * 10;

            ///     If the prev value of pot meter is different from this one, we want to change it
            if(abs(fOldPot1Value) - 5 != abs(fPot1Value))
            {
                fPot1Value > 0  ? fPot1Value += 5
                                : fPot1Value -= 5;

                fOldPot1Value = fPot1Value;
                fTens = fPot1Value;
            }


            ///     Now we can use the unity normalization for the units
            fPot2Value = peripherals.getPot2Value();
            fUnits = fPot2Value*(iUnitsMaxX - iUnitsMinX) + iUnitsMinX;



            ///     Calculate the angle and display it on screen
            fAngle = round(fTens + fUnits);
                        
            static string format = "%+03.0f\n";
            lcd.printFormattedFloat(85, 0, "%+03.0f\n", fAngle); 



            ///     Display instruction on screen
            lcd.printf(0, 23, "Use pot meters to set angle");

        break;

        // -------------------------------------------------------------------------------------------------------------
        default:
        // -------------------------------------------------------------------------------------------------------------
            s.error = true;
            
        break;
    }


    ///     Makes sure we can return to the menu by pressing the joystick
    if(joystickPosition == Pressed){
        s.currentState = S_MENU;
        lcd.clearScreen();
        joystickPosition = Released;
    }
}



//  --------------------------------------------------------------------------------------------------------------------
//  Main
//  --------------------------------------------------------------------------------------------------------------------

 int main() {

    ///     If an interrupt gets a rising edge we go to the specified method
    joystickDown.rise(&ButtonDown);
    joystickUp.rise(&ButtonUp);
    joystickPressed.rise(&ButtonPressed);
    joystickRight.rise(&ButtonRight);
    joystickLeft.rise(&ButtonLeft);

    
    ///     As long as no error occurs, the loop keeps going
    while(s.error == false){

        ///     Enter the case structure
        stateMachine();

    }
}
 