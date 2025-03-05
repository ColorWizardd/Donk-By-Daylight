/*
DONK BY DAYLIGHT
----------------
V 0.0
A COLORWIZARDD PROJECT
*/

#include "../include/shared/KeyHandler.h"
#include "../include/shared/ScreenHandler.h"
#include "../include/shared/Settings.h"
#include <iostream>
#include <Windows.h>

// *  TEST CODE FOR ENUMERATING ALL WINDOWS/CLASSES  * 

// static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
//     int length = GetWindowTextLengthA(hWnd);
//     WCHAR* buffer = new WCHAR[length + 1];
//     char* className = new char[64];
//     RealGetWindowClassA(hWnd, className, 63);

//     GetWindowTextW(hWnd, buffer, length + 1);
//     std::wstring windowTitle(buffer);
//     std::string title(windowTitle.begin(), windowTitle.end());
//     delete[] buffer;

//     // List visible windows with a non-empty title
//     if (length != 0 && IsWindowVisible(hWnd)) {
//         std::cout << hWnd << ":  " << title << '\t' << className << std::endl;
//     }
//     return TRUE;
// }

// Basic keypress test
int main() {
    KeyHandler* SpaceCheck = new KeyHandler();
    ScreenHandler* ScreenCheck = new ScreenHandler("DeadByDaylight-Win64-Shipping");
    const int sleepTime = 1000;
    const int screenshotDelay = 500;

    // std::cout << "Enmumerating windows..." << std::endl;
    // EnumWindows(enumWindowCallback, NULL);
    // // std::cin.ignore();

    if(!ScreenCheck->initializeWindow()) {
        std::cout << "THIS AINT WORKING CHIEF... \n";
    }

    while(true) {
        if(SpaceCheck->getKeyState()) {
            std::cout << "SPACE PRESSED\n";
            RECT windowRect;
            RECT outRect;
            HWND currScreen = ScreenCheck->getWindow();
            if(currScreen == NULL) {
                std::cout << "IM GONNA KILL MYSELF\n";
            }
            if(!GetClientRect(currScreen, &windowRect)){
                std::cout << "I HATE RECTANGLES!!!!!\n";
            }
            else{
                std::cout << "Default X-VALS: " << windowRect.left << " " << windowRect.right << 
                "\nDefault Y-VALS: " << windowRect.bottom << " " << windowRect.top << '\n';

                std::cout << "Window Length: " << ScreenCheck->getWindowLength(currScreen) <<
                "\nWindow Height: " << ScreenCheck->getWindowHeight(currScreen) << '\n';

                Sleep(screenshotDelay);

                bool screenShotWorked = ScreenCheck->screenshot(currScreen, outRect);
                if(screenShotWorked) {
                    std::cout << "TEST RECT X-COORDS: " << outRect.left << ", " << outRect.right <<
                    "\nTEST RECT Y-COORDS: " << outRect.bottom << ", " << outRect.top << '\n';
                }
            }
        }
        Sleep(sleepTime);
    }

}