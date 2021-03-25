#include "EthernetInterface.h"
#include "mbed.h"
#include "menu.h"
#include "sensors.h"
#include "frame.h"
#include "TCP_IP.h"
#include <string>



///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  Global Variables    /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/// Implements the lcd
C12832 lcd(D11, D13, D12, D7, D10);

/// Implements the joystick
DigitalIn joyUp(A2);
DigitalIn joyDown(A3);
DigitalIn joyLeft(A4);
DigitalIn joyRight(A5);
DigitalIn joyMiddle(D4);

/// Implements the led
PwmOut LED(D5);

/// Speaker PIN
PwmOut spkr(D6);


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////   Object delcaration     //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/// Create an object of sensoren
Sensors sensor;

/// Create an object of menu
Menu menu(lcd);

/// Create frame object
Frame frame;

/// Create TCP_IP object
TcpIP tcp;


///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////   Implementation of the tunes     //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// Struct for the tunes
struct Tune {
  int freq;
  int length;
  int delay;
};

// Array with structs for all the tunes
static Tune tunes[22] = {
    {110, 480, 100}, {110, 480, 100}, {110, 480, 100}, {98, 360, 75},
    {130, 120, 100}, {110, 480, 100}, {98, 360, 75},   {130, 120, 100},
    {110, 960, 100}, {165, 480, 100}, {165, 480, 100}, {165, 480, 100},
    {175, 360, 75},  {130, 120, 100}, {104, 480, 100}, {98, 360, 75},
    {130, 120, 100}, {110, 480, 100}, {110, 480, 100}, {110, 480, 100},
    {98, 360, 75},   {130, 120, 100}};



///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   State Machine     /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/// Enum with the states for the state machine
enum state { S_INIT, S_MENU, S_IP, S_VIEWDATA, S_SEND, S_LISTEN };

/// Porperties of the state
struct stateProp {
  state currentState = S_INIT;
  state prevState = S_MENU;
  const int statesOnPage = 4;
  bool broken = false;
  int prevButton = 0;
  int cursorPos = 0;
} s;


/// Runs through the state machine
void caseStructure() {

    /// Variables used throughout the states
    float temprature;
    float potVal;
    int led;
    int tune;
    static bool sendOrReceived;    /// Makes sure we can only send & receive once

    /// Case to switch between the pages
    switch (s.currentState) {

        /// Initiliziation
        case S_INIT:
            /// Executes the first time we enter the state
            if (s.currentState != s.prevState) {
                s.prevState = S_INIT;
                lcd.locate(0, 0);
                lcd.printf("Hello welcome,\nWe are intilizing everything");

                /// Initilize the server socket
                tcp.initIp();
            }

            /// Executes every time
            s.currentState = S_MENU;
        break;

        /// Shows the main menu
        case S_MENU:
            /// Executes the first time we enter the state
            if (s.currentState != s.prevState) {
                s.prevState = S_MENU;

                /// Checks if we should load main or end menu
                if(sendOrReceived){
                    menu.endMenu();
                    ThisThread::sleep_for(5000);
                }
                menu.mainMenu();
                sendOrReceived = false;
            }
                
            /// Controls the movement of the joystick
            /// Joystick is moved up or down
            if ((joyDown == 1) && (joyDown != s.prevButton)) {
                s.cursorPos = menu.moveDown();
            }
            else if ((joyUp == 1) && (joyUp != s.prevButton)) {
                s.cursorPos = menu.moveUp();
            }
            /// Joystick is pressed: Go to other state
            else if ((joyMiddle == 1) && (joyMiddle != s.prevButton)){
                if(s.cursorPos == 0){
                    s.currentState = S_IP;
                }
                else if (s.cursorPos == 1){
                    s.currentState = S_VIEWDATA;
                }
                else if(s.cursorPos == 2){
                    s.currentState = S_SEND;
                }
                else if (s.cursorPos == 3){
                    s.currentState = S_LISTEN;
                }
            }
        break;

        /// Shows the ip menu & ip implementation
        case S_IP:
            /// Variables used for the IP address.
            static int ipTen = 0;
            static int ipUnit = 0;   

            /// Variable used to select the digits
            static int horizontalSel = 0;
            
                
            /// Executes the first time we enter the state
            if (s.currentState != s.prevState) {
                s.prevState = S_IP;
                menu.ipMenu();
                lcd.locate(0, 20);
                if (horizontalSel == 0){
                    lcd.printf("Changing Tens");
                } else {
                    lcd.printf("Changing Units");
                }
            }

            /// Print the ip address on screen
            lcd.locate(0, 0);
            TcpIP::ip.replace(11, 1, to_string(ipTen));
            TcpIP::ip.replace(12, 1, to_string(ipUnit));
            lcd.printf("%s", TcpIP::ip.c_str()); 


            /// Joystick movement to select the digits (Tens / Units)
            if ((joyRight == 1) && (joyRight != s.prevButton)){
                if (horizontalSel < 1){
                    horizontalSel++;
                    lcd.locate(0, 20);
                    lcd.printf("Changing Units");
                }
            }
            else if ((joyLeft == 1) && (joyLeft != s.prevButton)){
                if (horizontalSel > 0){
                    horizontalSel--;
                    lcd.locate(0, 20);
                    lcd.printf("Changing Tens");
                }
            }
            /// Increments / Decrements the digits
            if ((joyDown == 1) && (joyDown != s.prevButton)) {
                if (horizontalSel == 1){
                    if((ipUnit < 9) && (ipUnit > 0)){
                        ipUnit--;
                    }
                    else{
                        ipUnit = 0;
                    }
                }
                else{
                    if((ipTen < 9) && (ipTen > 0)){
                        ipTen--;
                    }
                    else{
                        ipTen = 0;
                    }
                }            
            }
            else if ((joyUp == 1) && (joyUp != s.prevButton)) {
                if (horizontalSel == 1){
                    if((ipUnit < 9) && (ipUnit >= 0)){
                        ipUnit++;
                    }
                    else{
                        ipUnit = 0;
                    }
                }
                else{
                    if((ipTen < 9) && (ipTen >= 0)){
                        ipTen++;
                    }
                    else{
                        ipTen = 0;
                    }
                }
            }
            /// END of Increments / Decrements the digits


            /// Return to the main menu
            if ((joyMiddle == 1) && (joyMiddle != s.prevButton)){
                s.currentState = S_MENU;
            }
        break;

        /// Shows the values of the potentiometer & temprature
        case S_VIEWDATA:
            /// Executes the first time we enter the state
            if (s.currentState != s.prevState) {
                s.prevState = S_VIEWDATA;
                menu.displayDataText();
            }
          
            /// Displays the temperature and potentiometer value  
            potVal = sensor.readPotMeter();
            temprature = sensor.readTempSensor();
            menu.displayData(potVal, temprature);

            /// Sets the value of the led
            LED = potVal;

            /// Return to the main menu
            if ((joyMiddle == 1) && (joyMiddle != s.prevButton)){
                s.currentState = S_MENU;
            }

        break;

        /// Transmits the data
        case S_SEND:
            /// Executes the first time we enter the state
            if (s.currentState != s.prevState) {
                s.prevState = S_SEND;
                lcd.cls();            
                lcd.locate(0, 0);

                /// Sends the data & checks for errors
                int result = tcp.send();
                if(result == 0){
                    lcd.printf("Data sent away!");
                }
                else{
                    lcd.printf("error: %i", result);
                }
                ThisThread::sleep_for(500);
            }

            /// Go to the main menu or the listen state
            if(sendOrReceived){
                s.currentState = S_MENU;
            }
            else{
                s.currentState = S_LISTEN;
            }
            sendOrReceived = true;

            /// Return to the main menu
            if ((joyMiddle == 1) && (joyMiddle != s.prevButton)){
                s.currentState = S_MENU;
            }
        break;

        /// Receive the data
        case S_LISTEN:
            if (s.currentState != s.prevState) {
                s.prevState = S_LISTEN;
                lcd.cls();                
                lcd.locate(0, 0);
                lcd.printf("Waiting to receive...");
                lcd.locate(0, 0);

                /// Receive the data & assign it to the variables
                bool result = tcp.receive(temprature, tune, led);
                if (result == false){
                    lcd.cls();
                    lcd.printf("CRC is NOT correct\nTemperature: %.3f\nLED value: %i", temprature, led);
                }
                else{
                    lcd.cls();
                    lcd.printf("CRC is correct\nTemperature: %.3f\nLED value: %i", temprature, led);     
                }

                /// Set the value of the LED
                LED = led;
                
                /// Decrement the tune so we can play element 0 from the array
                tune--;

                /// Play the tune
                ThisThread::sleep_for(tunes[tune].delay);
                spkr.period(1.0/tunes[tune].freq);
                spkr=0.5;
                ThisThread::sleep_for(tunes[tune].length);
                spkr = 0;
                ThisThread::sleep_for(500);
            }

            /// Go to the send state or menu
            if(sendOrReceived){
                s.currentState = S_MENU;
            }
            else{
                s.currentState = S_SEND;
            }
            sendOrReceived = true;


            /// Return to the main menu
            if ((joyMiddle == 1) && (joyMiddle != s.prevButton)){
                s.currentState = S_MENU;
            }
        break;

        /// Default case, entered when something is wrong
        default:
            s.broken = true;
        break;
    } 
    /// End of case structure


    /// Regulates the buttons, so you can't keep them pressed
    if (joyDown or joyLeft or joyRight or joyUp or joyMiddle){
        s.prevButton = 1;
    }
    else {
        s.prevButton = 0;
    }
}
/// End of method



///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   Main     ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main() {
    while (s.broken != true) {
        caseStructure();
    }
}
