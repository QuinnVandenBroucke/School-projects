#ifndef MENU_H
#define MENU_H

#include "C12832.h"
#include <string>


/// Menu class mainly shows text on screen
/// Another feature is that of moving a cursor up and down when the joystick is used
class Menu {
    public:
        /// Constructor for the menu class
        Menu(C12832&);


        ///////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////  Function Declaration    ////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// Displays the main menu
        /// @param void
        /// @return void
        void mainMenu(void);    

        /// Displays a menu when you're done
        /// @param void
        /// @return void
        void endMenu(void);    

        /// Displays the ip menu
        /// @param void
        /// @return void
        void ipMenu(void);

        /// Displays the data text screen
        /// @param void
        /// @return void
        void displayDataText(void);

        /// Displays the data on screen
        /// @param float potVal - Potentiometer value range(0 - 255)
        /// @param float tempVal - Temperature as a float
        /// @return void
        void displayData(float potVal, float tempVal);

        /// Move the selector down
        /// @param void
        /// @return int - returns the current cursorsposition
        int moveDown(void);

        /// Move the selector up
        /// @param void
        /// @return int - returns the current cursorsposition
        int moveUp(void);

    private:

        ///////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////  Private Variables    ////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////

        /// A C12832 object called lcd
        C12832& lcd;

        /// Cursorpostion indicates where the cursor is displayed on screen
        static int cursorPos;

        /// Indicates how many states or on 1 page
        const int statesOnPage = 4;


        /// Indicates how far down/up the cursor needs to move
        const int vertLineJump = 10;

        /// Position where the line will be displayed (y - coordinate)
        static int vertLine;         
};


#endif