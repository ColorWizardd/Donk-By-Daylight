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
    KeyHandler *SpaceCheck = new KeyHandler(0x20);
    const int sleepTime = 20;

    while(true) {
        if(SpaceCheck->getKeyState()) {
            std::cout << "SPACE PRESSED\n";
        }
        else {
            std::cout << "NO KEY PRESSED\n";
        }
        Sleep(sleepTime);
    }

}