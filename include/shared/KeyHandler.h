#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <windows.h>

class KeyHandler{
    public:
        KeyHandler();
        KeyHandler(int listenTarget);
        int getListenTarget() const;
        void setListenTarget(int target);
        bool getKeyState();

    private:
        int listenTarget;
};

#endif