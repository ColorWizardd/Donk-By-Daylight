/*
GLOBAL SETTINGS AND VARS
*/

#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
    const char *windowTarget;
    const char *className;
    int wRatio;
    int hRatio;
    const char *outFile;
    int actionKey;
};

extern Settings DBD_GLOBAL;

#endif