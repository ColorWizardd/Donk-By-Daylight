/*
KEYBOARD INPUT HANDLER USING WIN32 API
*/

#include "../include/shared/KeyHandler.h"

KeyHandler::KeyHandler(){
    setListenTarget(0x20);
}

KeyHandler::KeyHandler(int listenTarget){
    setListenTarget(listenTarget);          
}

int KeyHandler::getListenTarget() const{
    return this->listenTarget;
}

void KeyHandler::setListenTarget(int target) {
    this->listenTarget = target;
}

// Using winuser GetKeyState to check if key is pressed
bool KeyHandler::getKeyState() {
    return GetKeyState(this->listenTarget) & 0x8000;
}