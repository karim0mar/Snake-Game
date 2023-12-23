#include "window.h"
HWND HH = nullptr;
HWND staticControl = nullptr;
HWND appleControl = nullptr;
int window::_width= 420;
int window::_height= 280;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam , LPARAM lParam){
    switch (uMsg) {
        case WM_CREATE:
            HH = hwnd; // بخلي ال window global
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

void window::addControls(int x , int y) {
    if (staticControl != nullptr) { // بحذف الText قبل ما اكتب الtext الي بعده
        DestroyWindow(staticControl);
        staticControl = nullptr;
        Sleep(30);
    }

        staticControl = CreateWindowW(L"static", L" * ", WS_VISIBLE | WS_CHILD, x, y, 20, 20, HH, nullptr, nullptr,
                                      nullptr); // بطبع ال text
}
    void window::drawApple(int x , int y) {// مكسل اكتب تاني نفس الكلام مع التفاحه
        if (appleControl != nullptr) {
            DestroyWindow(appleControl);
            appleControl = nullptr;
            Sleep(30);
        }
    appleControl = CreateWindowW(L"static",L" A ",WS_VISIBLE|WS_CHILD,x,y,20,20,HH,nullptr,nullptr,nullptr);
}
window::window()
     : my_hinstance(GetModuleHandle(nullptr))
{
WNDCLASS wndclass = {}; // El frame
wndclass.lpszClassName = "Game Class";
wndclass.hInstance = my_hinstance;
wndclass.hIcon = LoadIcon(NULL,IDI_WINLOGO);
wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
wndclass.lpfnWndProc = WindowProc;
wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;

RegisterClass(&wndclass);
DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX;
RECT rect;
rect.left = 250;// el style bta3 elfraim
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
