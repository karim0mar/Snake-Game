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
    static void addControls(int, int);
    static void drawApple(int, int);
    static void clear(int, int);
    static int _width;
    static int _height;
private:
    HINSTANCE my_hinstance;
    HWND my_HWND;
};