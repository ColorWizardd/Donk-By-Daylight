#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include <windows.h>

class ScreenHandler {
    public:
        ScreenHandler();
        ScreenHandler(const char *windowTarget);
        bool initializeWindow();
        const char* getWindowTarget() const;
        void setWindowTarget(const char *target);
        HWND getWindow();
        long getWindowLength(HWND window) const;
        long getWindowHeight(HWND window) const;
        void setWindowLength(long length);
        void setWindowHeight(long height);
        bool doesExist();
        void setExist(bool state);
    private:
        const char *windowTarget;
        long length = 0;
        long height = 0;
        bool windowExists;
};

#endif