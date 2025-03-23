/*
DONK BY DAYLIGHT
----------------
V 0.0
A COLORWIZARDD PROJECT
*/

#include "../include/shared/KeyHandler.h"
#include "../include/shared/ScreenHandler.h"
#include "../include/shared/Settings.h"
#include <tesseract/baseapi.h>
#include <allheaders.h>
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




class TessLib {
    public:
    // Static method for returning text from image
    static void processText(char *txt) {
        tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
        if(api->Init(NULL, "eng")) {
            std::cout << "ERROR: Could not initialize tesseract\n";
            return;
        }

        if(txt != nullptr) {
            delete[] txt;
        }

        Pix *img = pixRead(DBD_GLOBAL.outFile);
        api->SetImage(img);
        char *imgText = api->GetUTF8Text();

        txt = imgText;
        api->End();
        delete api;
        delete[] imgText;
        pixDestroy(&img);
        return;
    }
    // Static method for matching text to given range of options
    

};

const char* outFile = DBD_GLOBAL.outFile;

// Basic keypress test
int main() {
    KeyHandler* SpaceCheck = new KeyHandler();
    ScreenHandler* ScreenCheck = new ScreenHandler("MozillaWindowClass");
    const int sleepTime = 1000;
    const int screenshotDelay = 500;

    // TESSERACT TEST

    // char *txt = nullptr;

    // TessLib::processText(txt);

    // std::cout << "Result: " << txt << '\n';


    // std::cout << "Enmumerating windows..." << std::endl;
    // EnumWindows(enumWindowCallback, NULL);
    // // std::cin.ignore();

    if(!ScreenCheck->initializeWindow(DBD_GLOBAL.className)) {
        std::cout << "THIS AINT WORKING CHIEF... \n";
    }

    while(true) {
        if(SpaceCheck->getKeyState()) {
            std::cout << "SPACE PRESSED\n";
            RECT windowRect;
            RECT outRect;
            HWND currScreen = ScreenCheck->getWindow(DBD_GLOBAL.className);
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