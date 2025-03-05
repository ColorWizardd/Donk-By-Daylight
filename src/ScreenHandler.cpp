/*
STORES A TARGET WINDOW AND SOME BASIC INFORMATION
*/

#include "../include/shared/ScreenHandler.h"
#include "../include/shared/Settings.h"

ScreenHandler::ScreenHandler() {
    setWindowHeight(0);
    setWindowLength(0);
    setWindowTarget(DBD_GLOBAL.windowTarget);
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

const char *ScreenHandler::getFileTarget() const {
    return this->outFile;
}

void ScreenHandler::setFileTarget(const char *target) {
    this->outFile = target;
}

/*
For now, only the window target seems to work.
Looks like there's some obfsucation with how Unreal Engine loads or names windows.
SIDE NOTE: I guess this will work with anything that uses Unreal Engine?
*/ 
HWND ScreenHandler::getWindow() {
    return FindWindowA(DBD_GLOBAL.className, NULL);
}

long ScreenHandler::getWindowLength(HWND window) const {
    RECT context;
    GetWindowRect(window, &context);
    return (context.right - context.left);
}

long ScreenHandler::getWindowHeight(HWND window) const { 
    RECT context;
    GetWindowRect(window, &context);
    return (context.bottom - context.top);
}

void ScreenHandler::setWindowLength(long length) {
    this->length = length;
}

void ScreenHandler::setWindowHeight(long height) {
    this->height = height;
}

bool ScreenHandler::doesExist() const{
    return this->windowExists;
}

void ScreenHandler::setExist(bool state) {
    this->windowExists = state;
}

bool ScreenHandler::screenshot(HWND window, RECT &testRect) {
    /*
    Cropping the top-right corner of the window to isolate text
    ASSUMES THE APPLICATION IS RUNNING IN FULL-SCREEN
    */
    RECT rect;
    bool isShot = GetClientRect(window, &rect);
    if(isShot) {
        const HDC displayContext = GetDC(window);
        const HDC windowCap = CreateCompatibleDC(displayContext);

        if(windowCap == NULL || displayContext == NULL) {
            MessageBoxA(window, "CreateCompatibleDC has failed", NULL, MB_OK);
            DeleteObject(windowCap);
            ReleaseDC(window, displayContext);
            exit(EXIT_FAILURE);
        }

        rect.left = rect.left + ((rect.right * (DBD_GLOBAL.wRatio - 1)) / DBD_GLOBAL.wRatio);
        rect.bottom = rect.bottom - ((rect.bottom * (DBD_GLOBAL.hRatio - 1) / DBD_GLOBAL.hRatio));

        testRect = rect;

    HBITMAP hbMap = CreateCompatibleBitmap(displayContext, (rect.right - rect.left), (rect.bottom - rect.top));

    if(hbMap == NULL) {
        MessageBoxA(window, "CreateCompatibleBitmap has failed", NULL, MB_OK);
        DeleteObject(hbMap);
        DeleteObject(windowCap);
        ReleaseDC(window, displayContext);
        exit(EXIT_FAILURE);
    }

    BITMAP bMapScreen;

    SelectObject(windowCap, hbMap);

    // Copying an inverted-color window capture into a compatible DC

    if(!BitBlt(
        windowCap, 0, 0, 
        (rect.right - rect.left), 
        (rect.bottom - rect.top),
        displayContext,
        rect.left, rect.top,
        SRCCOPY
    )) {
        MessageBoxA(window, "BitBlt has failed", NULL, MB_OK);
        DeleteObject(hbMap);
        DeleteObject(windowCap);
        ReleaseDC(window, displayContext);
        exit(EXIT_FAILURE);
    }

    GetObjectA(hbMap, sizeof(BITMAP), &bMapScreen);

    // CREATING ACTUAL BITMAP

    BITMAPINFOHEADER bMapIHead;
    BITMAPFILEHEADER bFileHead;

    DWORD bmpSize = 0;
    DWORD bytesWritten = 0;
    DWORD sizeOfDIB = 0;

    bMapIHead.biSize = sizeof(BITMAPINFOHEADER);
    bMapIHead.biWidth = bMapScreen.bmWidth;
    bMapIHead.biHeight = bMapScreen.bmHeight;
    bMapIHead.biPlanes = 1;
    bMapIHead.biBitCount = 32;
    bMapIHead.biCompression = BI_RGB;
    bMapIHead.biSizeImage = 0;
    bMapIHead.biXPelsPerMeter = 0;
    bMapIHead.biYPelsPerMeter = 0;
    bMapIHead.biClrUsed = 0;
    bMapIHead.biClrImportant = 0;

    bmpSize = ((bMapScreen.bmWidth * bMapIHead.biBitCount + 31) / 32) * 4 * bMapScreen.bmHeight;

    // MEMEORY ALLOCATION

    HANDLE hDIB = LocalAlloc(GHND, bmpSize);
    char *lpbMap = (char*)GlobalLock(hDIB);

    // Get bits from bmap

    GetDIBits(
        displayContext, hbMap,
        0, (UINT)bMapScreen.bmHeight,
        lpbMap, (BITMAPINFO*)&bMapIHead,
        DIB_RGB_COLORS
    );

    // Create/Write bmp to file

    HANDLE hFile = CreateFileA(
        DBD_GLOBAL.outFile,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(hFile == INVALID_HANDLE_VALUE) {
        MessageBoxA(window, "File handle not valid", NULL, MB_OK);
        LocalUnlock(hDIB);
        LocalFree(hDIB);
        CloseHandle(hFile);

        DeleteObject(hbMap);
        DeleteObject(windowCap);
        ReleaseDC(window, displayContext);
        exit(EXIT_FAILURE);
    }

    sizeOfDIB = bmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bFileHead.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
    bFileHead.bfSize = sizeOfDIB;
    bFileHead.bfType = 0x4D42; //BM type required for header
    WriteFile(hFile, (LPSTR)&bFileHead, sizeof(BITMAPFILEHEADER), &bytesWritten, NULL);
    WriteFile(hFile, (LPSTR)&bMapIHead, sizeof(BITMAPINFOHEADER), &bytesWritten, NULL);
    WriteFile(hFile, (LPSTR)lpbMap, bmpSize, &bytesWritten, NULL);

    LocalUnlock(hDIB);
    LocalFree(hDIB);
    CloseHandle(hFile);

    DeleteObject(hbMap);
    DeleteObject(windowCap);
    ReleaseDC(window, displayContext);

    return isShot;

}
return isShot;
}