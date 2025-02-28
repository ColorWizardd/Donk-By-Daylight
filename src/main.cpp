/*
DONK BY DAYLIGHT
----------------
V 0.0
A COLORWIZARDD PROJECT
*/

#include "../include/shared/KeyHandler.h"
#include "../include/shared/ScreenHandler.h"
#include <iostream>

// Basic keypress test
int main() {
    KeyHandler *SpaceCheck = new KeyHandler();
    ScreenHandler *ScreenCheck = new ScreenHandler("New Tab - Google Chrome");
    const int sleepTime = 100;

    if(!ScreenCheck->initializeWindow()) {
        std::cout << "THIS AINT WORKING CHIEF... \n";
    }

    while(true) {
        if(SpaceCheck->getKeyState()) {
            std::cout << "SPACE PRESSED\n";
            LPRECT windowRect;
            if(ScreenCheck->getWindow() == NULL) {
                std::cout << "IM GONNA KILL MYSELF'\n";
            }
            else if(!GetWindowRect(ScreenCheck->getWindow(), windowRect)){
                std::cout << "I HATE RECTANGLES!!!!!\n";
            }
            else{
                std::cout << "Window Length: " << ScreenCheck->getWindowLength(ScreenCheck->getWindow()) <<
                "\nWindow Height: " << ScreenCheck->getWindowHeight(ScreenCheck->getWindow()) << '\n';
            }
        }
        else {
            std::cout << "NO KEY PRESSED\n";
        }
        Sleep(sleepTime);
    }

}