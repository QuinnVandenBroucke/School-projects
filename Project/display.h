#ifndef DISPLAY_H
#define DISPLAY_H

#include "C12832.h"


///     This class is used to display info on the screen
class Display{

    private:
        ///     C12832 variable
        C12832 lcd;


        ///     Variables to move the cursor
        const int iVerticalOffset = 10;
        static int iVerticalCursorPos;
        static int iVerticalItemSelector;        


    public:
        ///     Constructor
        Display();

        /// ------------------------------------------------------------------------------------------------------------
        /// Screen properties
        /// ------------------------------------------------------------------------------------------------------------

        ///     Get the screen width
        ///     @ return int : an integer with the screen width
        int getWidth();


        ///     Get the screen height
        ///     @ return int : an integer with the screen height
        int getHeight();


        ///     Clear the screen
        ///     @ return void
        void clearScreen();



        /// ------------------------------------------------------------------------------------------------------------
        /// Print statements
        /// ------------------------------------------------------------------------------------------------------------

        ///     Overload the print method so we can print everything on screen
        ///     ``````````````````````````````````````````````````````````````

        ///     Print a string on screen
        ///     @ param iXPos              : integer that holds the x position of the text
        ///     @ param iYPos              : integer that holds the y position of the text
        ///     @ param const char * sText : constant pointer to a char that is the text
        ///     @ return void
        void printf(int iXPos, int iYPos, const char * sText);


        ///     Print a float on screen
        ///     @ param iXPos  : integer that holds the x position of the float
        ///     @ param iYPos  : integer that holds the y position of the float
        ///     @ param fValue : a float value
        ///     @ return void
        void printf(int iXPos, int iYPos, float fValue);


        ///     Print a integer on screen
        ///     @ param iXPos  : integer that holds the x position of the integer
        ///     @ param iYPos  : integer that holds the y position of the integer
        ///     @ param iValue : an integer value
        ///     @ return void
        void printf(int iXPos, int iYPos, int iValue);


        ///     Print a string and float on screen
        ///     @ param iXPos              : integer that holds the x position of the text / float
        ///     @ param iYPos              : integer that holds the y position of the text / float
        ///     @ param const char * sText : constant pointer to a char that is the text
        ///     @ param fValue             : a float value
        ///     @ return void
        void printf(int iXPos, int iYPos, const char* sText, float fValue);


        ///     Print formatted floats
        ///     @ param iXPos                    : integer that holds the x position of the float
        ///     @ param iYPos                    : integer that holds the y position of the float
        ///     @ param const char sFormatting[] : constant character array that holds the formatting
        ///     @ param fValue                   : a float value 
        ///     @ return void
        void printFormattedFloat(int iXPos, int iYPos, const char sFormatting[],  float fValue);
        


        /// ------------------------------------------------------------------------------------------------------------
        /// Draw shapes / lines on screen
        /// ------------------------------------------------------------------------------------------------------------

        ///     Draw a line on the screen
        ///     @ param iX0    : integer that holds the starting x position of the line
        ///     @ param iY0    : integer that holds the starting y position of the line
        ///     @ param iX1    : integer that holds the end x position of the line
        ///     @ param iY1    : integer that holds the end y position of the line
        ///     @ param bErase : boolean to erase the line
        ///     @ return void
        void drawLine(int iX0, int iY0, int iX1, int iY1, bool bErase);


        ///     Draw a rectangle on the screen
        ///     @ param iRectX  : integer with the top left x position of the rectangle 
        ///     @ param iRectY  : integer with the top left y position of the rectangle
        ///     @ param iWidth  : integer that holds the width  of the rectangle
        ///     @ param iHeight : integer that holds the height of the rectangle
        ///     @ param bErase  : boolean to erase the rectangle
        ///     @ return void
        void drawRectangle(int iRectX, int iRectY, int iWidth, int iHeight, bool bErase);


        ///     Draw a filled rectangle on the screen
        ///     @ param iRectX  : integer with the top left x position of the filled rectangle 
        ///     @ param iRectY  : integer with the top left y position of the filled rectangle
        ///     @ param iWidth  : integer that holds the width  of the filled rectangle
        ///     @ param iHeight : integer that holds the height of the filled rectangle
        ///     @ param bErase  : boolean to erase the filled rectangle
        ///     @ return void
        void drawFilledRectangle(int iRectX, int iRectY, int iWidth, int iHeight, bool bErase);


        ///     Draw a circle on the screen
        ///     @ param iCenterX : integer with the center x position of the circle
        ///     @ param iCenterY : integer with the center y position of the circle
        ///     @ param iRadius  : integer with the radius of the circle 
        ///     @ param bErase   : boolean to erase the circle
        ///     @ return void
        void drawCircle(int iCenterX, int iCenterY, int iRadius, bool bErase);



        /// ------------------------------------------------------------------------------------------------------------
        /// Cursor functions / values
        /// ------------------------------------------------------------------------------------------------------------

        ///     Method to move the cursor up (in the menu)
        ///     @ return void
        void moveCursorUp();


        ///     Method to move the cursor down (in the menu)
        ///     @ return void
        void moveCursorDown();


        ///     Get the vertical cursor position
        ///     ````````````````````````````````
        ///     This return the y location of the cursor so that we can draw it again on the position where it was last
        ///     @ return int : an integer with the y position of the cursor
        int getVerticalCursorPos();


        ///     Get the position of the item that is currently selected
        ///     ```````````````````````````````````````````````````````
        ///     This returns the index of what item is currently selected in the menu
        ///     @ return int : an integer with the index of the selected menu item
        int getVerticalItemSelector();
};

#endif