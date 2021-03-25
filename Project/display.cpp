#include "display.h"

///     STATIC DELARATIONS
int Display::iVerticalCursorPos = 0;
int Display::iVerticalItemSelector = 0;


Display::Display() : lcd(D11, D13, D12, D7, D10) {};



/// --------------------------------------------------------------------------------------------------------------------
/// Screen properties
/// --------------------------------------------------------------------------------------------------------------------

int Display::getHeight(){
    return lcd.height();
}


int Display::getWidth(){
    return lcd.width();
}


void Display::clearScreen(){
    lcd.cls();
}



/// --------------------------------------------------------------------------------------------------------------------
/// Print statements
/// --------------------------------------------------------------------------------------------------------------------

void Display::printf(int iXPos, int iYPos, const char * sText){
    lcd.locate(iXPos, iYPos);
    lcd.printf("%s", sText);
}


void Display::printf(int iXPos, int iYPos, float fValue){
    lcd.locate(iXPos, iYPos);
    lcd.printf("%f", fValue);
}


void Display::printf(int iXPos, int iYPos, int iValue){
    lcd.locate(iXPos, iYPos);
    lcd.printf("%i", iValue);
}


void Display::printf(int iXPos, int iYPos, const char * sText, float fValue){
    lcd.locate(iXPos, iYPos);
    lcd.printf("%s %f", sText, fValue);
}


void Display::printFormattedFloat(int iXPos, int iYPos, const char sFormatting[], float fValue){
    lcd.locate(iXPos, iYPos);
    lcd.printf(sFormatting, fValue);
}



/// --------------------------------------------------------------------------------------------------------------------
/// Draw shapes / lines on screen
/// --------------------------------------------------------------------------------------------------------------------

void Display::drawLine(int iX0, int iY0, int iX1, int iY1, bool bErase){
    lcd.line(iX0, iY0, iX1, iY1, bErase ? 0  : 1);
}


void Display::drawRectangle(int iRectX, int iRectY, int iWidth, int iHeight, bool bErase){
    int iRectX2 = iRectX + iWidth;
    int iRectY2 = iRectY + iHeight;

    lcd.rect(iRectX, iRectY , iRectX2, iRectY2, bErase ? 0 : 1);
}


void Display::drawFilledRectangle(int iRectX, int iRectY, int iWidth, int iHeight, bool bErase){
    int iRectX2 = iRectX + iWidth;
    int iRectY2 = iRectY + iHeight;

    lcd.fillrect(iRectX, iRectY , iRectX2, iRectY2, bErase ? 0 : 1);
}


void Display::drawCircle(int iCenterX, int iCenterY, int iRadius, bool bErase){
    lcd.circle(iCenterX, iCenterY, iRadius, bErase ? 0 : 1);
}



/// --------------------------------------------------------------------------------------------------------------------
/// Cursor functions / values
/// --------------------------------------------------------------------------------------------------------------------

void Display::moveCursorUp(){
    if(iVerticalItemSelector > 0)
    {
        printf(0, iVerticalCursorPos, " ");
        iVerticalCursorPos -= iVerticalOffset;
        iVerticalItemSelector--;
        printf(0, iVerticalCursorPos, ">");
    }
}


void Display::moveCursorDown(){
    int iSelBoundry = 2;   /// Number should be the amount of items on the screen - 1
    if(iVerticalItemSelector < iSelBoundry)
    {
        printf(0, iVerticalCursorPos, " ");
        iVerticalCursorPos += iVerticalOffset;
        iVerticalItemSelector++;
        printf(0, iVerticalCursorPos, ">");
    }
}


int Display::getVerticalCursorPos(){
    return iVerticalCursorPos;
}


int Display::getVerticalItemSelector(){
    return iVerticalItemSelector;
}
