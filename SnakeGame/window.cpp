#include <string>
#include "window.h"
#pragma execution_character_set("utf-8")
HWND HH = nullptr;
HWND snackControl = nullptr;
HWND appleControl = nullptr;
int window::_width= 420;
int window::_height= 280;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam , LPARAM lParam){
    switch (uMsg) {
        case WM_CREATE:
            HH = hwnd;
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
void window::setup(int aX,int aY) {
    snackControl = CreateWindowW(L"static", L"*", WS_VISIBLE | WS_CHILD, _width/2, _height/2, 25, 15, HH, nullptr, nullptr,
                                 nullptr);
    HFONT snackFont=CreateFont (25, 15, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    HFONT appleFont=CreateFont (25, 25, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    appleControl = CreateWindowW(L"static",L"🍎",WS_VISIBLE|WS_CHILD,aX,aY,50,50,HH,nullptr,nullptr,nullptr);
    SendMessage (appleControl, WM_SETFONT, WPARAM (appleFont), TRUE);
    SendMessage (snackControl, WM_SETFONT, WPARAM (snackFont), TRUE);

}
void window::changeSnackPos(int x , int y) {
        Sleep(10);
    SetWindowPos(snackControl,HWND_BOTTOM,x,y,25,15, SWP_NOSIZE);
}
    void window::changeApplePos(int x , int y) {
            Sleep(10);
            SetWindowPos(appleControl,HWND_TOP,x,y,25,15, SWP_NOSIZE);

    }
window::window()
     : my_hinstance(GetModuleHandle(nullptr))
{
WNDCLASS wndclass = {};
wndclass.lpszClassName = "Game Class";
wndclass.hInstance = my_hinstance;
wndclass.hIcon = LoadIcon(NULL,IDI_WINLOGO);
wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
wndclass.lpfnWndProc = WindowProc;
wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;

RegisterClass(&wndclass);
DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX;
RECT rect;
rect.left = 250;
rect.top = 250;
rect.right = rect.left + _width;
rect.bottom = rect.top + _height;
AdjustWindowRect(&rect,style,false);
my_HWND = CreateWindowExA(0,"Game Class","Snake Game :)",style,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,nullptr,nullptr,my_hinstance,nullptr);

ShowWindow(my_HWND,SW_SHOW);
}
window ::~window(){
    UnregisterClass("Game Class",my_hinstance);
}
bool window::ProcessMessages() {
    MSG msg = {};
    while (PeekMessage(&msg, nullptr,0u,0u,PM_REMOVE)){
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}
