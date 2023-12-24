#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include "window.h"
enum eDir{STOP=0,UP,DOWN,LEFT,RIGHT};
eDir dir;
int x,y,appleX,appleY;
int Tall;
const int range = 15;
bool running = true;
int score = 0;

bool inRangeW(int x){
    if (x < 10 || x > window::_width)
        return false;
    return true;
}
bool inRangeH(int y){
    if (y < 10 || y+10 > window::_height)
        return false;
    return true;
}
bool inRangeApple(int r, int i){
    if ((appleX < r + 15 && appleX > r - 15) && (appleY < i + 15 && appleY > i - 15))
        return true;
    return false;
}
void generateApple() {
    appleX = rand() % window::_width;
    appleY = rand() % window::_height;
    window::changeApplePos(appleX, appleY);
    Tall++;
}
void setup(){
dir = STOP;
x = window::_width /2;
y = window::_height /2;
appleX = rand() % window::_width;
appleY = rand() % window::_height;
window::setup(appleX,appleY);
}
void Draw(){
    if (!inRangeW(x + range) || !inRangeH(y + range)) {
        running = false;
        std::cout << "Lose";
    }
    Sleep(60);
    window::changeSnackPos(x, y);
    if (inRangeApple(x,y)) {
        score+=10;
        generateApple();
    }

}
void Logic(){
    switch (dir) {
        case UP:
            y-=range;
            break;
        case DOWN:
            y+=range;
            break;
        case RIGHT:
            x+=range;
            break;
        case LEFT:
            x-=range;
            break;
        default:
            break;
    }
}
void Input(){
    if (GetKeyState(VK_UP) & 0x8000)
        dir = UP;
    else if (GetKeyState(VK_DOWN) & 0x8000)
        dir = DOWN;
    else if(GetKeyState(VK_LEFT) & 0x8000)
        dir = LEFT;
    else if (GetKeyState(VK_RIGHT) & 0x8000)
        dir = RIGHT;
}

using namespace std;
int main (){
    window* pWindow =new window();
    setup();
    while (running){
        Draw();
        Input();
        Logic();
        if (!pWindow->ProcessMessages()){
            cout << "Closing";
            running = false;
        }
    }
    delete pWindow;
    return 0;
}
