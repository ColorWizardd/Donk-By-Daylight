/*
STORES A TARGET WINDOW AND SOME BASIC INFORMATION
*/

#include "../include/shared/ScreenHandler.h"

ScreenHandler::ScreenHandler() {
    setWindowHeight(0);
    setWindowLength(0);
    setWindowTarget("Dead By Daylight");
    setExist(initializeWindow());
}

ScreenHandler::ScreenHandler(const char *windowTarget) {
    setWindowHeight(0);
    setWindowLength(0);
    setWindowTarget(windowTarget);
    setExist(initializeWindow());
}

bool ScreenHandler::initializeWindow() {
    try{
        HWND window = getWindow();
        setWindowLength(getWindowLength(window));
        setWindowHeight(getWindowHeight(window));
        return true;
    }
    catch(const char *errTarget) {
        return false;
    }
}

const char *ScreenHandler::getWindowTarget() const {
    return this->windowTarget;
}

void ScreenHandler::setWindowTarget(const char *target) {
    this->windowTarget = target;
}

HWND ScreenHandler::getWindow() {
    return FindWindowA(NULL, getWindowTarget());
}

long ScreenHandler::getWindowLength(HWND window) const {
    LPRECT context;
    GetWindowRect(window, context);
    return (context->right - context->left);
}

long ScreenHandler::getWindowHeight(HWND window) const { 
    LPRECT context;
    GetWindowRect(window, context);
    return (context->bottom - context->top);
}

void ScreenHandler::setWindowLength(long length) {
    this->length = length;
}

void ScreenHandler::setWindowHeight(long height) {
    this->height = height;
}

bool ScreenHandler::doesExist() {
    return this->windowExists;
}

void ScreenHandler::setExist(bool state) {
    this->windowExists = state;
}