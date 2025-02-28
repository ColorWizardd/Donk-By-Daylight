/*
KEYBOARD INPUT HANDLER USING WIN32 API
*/

#include "../include/shared/KeyHandler.h"
#include "../include/shared/Settings.h"

KeyHandler::KeyHandler(){
    setListenTarget(DBD_GLOBAL.actionKey);
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