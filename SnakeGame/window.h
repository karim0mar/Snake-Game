#pragma once
#include "Windows.h"
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam ,LPARAM lParam);
class window{
public:
    window();
    window(const window&) = delete;
    window& operator = (const window&) = delete;
    ~window();
    bool ProcessMessages();
    static void setup(int, int);
    static void changeSnackPos(int, int);
    static void changeApplePos(int, int);
    static int _width;
    static int _height;
private:
    HINSTANCE my_hinstance;
    HWND my_HWND;
};
