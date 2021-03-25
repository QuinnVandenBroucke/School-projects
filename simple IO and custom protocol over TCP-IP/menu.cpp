#include "menu.h"



Menu::Menu(C12832& lcd) : lcd(lcd) {}

int Menu::vertLine = 9;
int Menu::cursorPos = 0;


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  Display Data & Text    /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void Menu::mainMenu() {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Ip Configuration");
    lcd.line(0, vertLine, 70, vertLine, 1);
    lcd.locate(0, 10);
    lcd.printf("View Data");
    lcd.locate(0, 20);
    lcd.printf("Send Data");
    lcd.locate(80, 20);
    lcd.printf("Listen");
}


void Menu::endMenu(){
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("We have sent & received\nEnd of the demo");
}

void Menu::ipMenu() {
    lcd.cls();
    lcd.locate(0, 0);
}


void Menu::displayDataText(){
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Potentiometer: ");
    lcd.locate(0, 10);
    lcd.printf("Temperatuur: ");

}


void Menu::displayData(float potVal, float tempVal){
    lcd.locate(65, 0);
    lcd.printf("%.3f", potVal);
    lcd.locate(60, 10);
    lcd.printf("%.3f", tempVal);
}


///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  Cursor    /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int Menu::moveDown(){
     if (cursorPos < statesOnPage-1){
        cursorPos++;
        if (cursorPos == 3){
            lcd.line(0, vertLine, 70, vertLine, 0);
            lcd.line(75, vertLine, 120, vertLine, 1);
        }
        else{
            lcd.line(0, vertLine, 70, vertLine, 0);
            vertLine += vertLineJump;
            lcd.line(0, vertLine, 70, vertLine, 1);
        }
    }
    return cursorPos;
}


int Menu::moveUp(){
    if(cursorPos > 0){
        if (cursorPos == 3){
            lcd.line(0, vertLine, 70, vertLine, 1);
            lcd.line(75, vertLine, 120, vertLine, 0);
        }
        else{
            lcd.line(0, vertLine, 70, vertLine, 0);
            vertLine -= vertLineJump;
            lcd.line(0, vertLine, 70, vertLine, 1);
        }
        cursorPos--;
    }
    return cursorPos;
}



