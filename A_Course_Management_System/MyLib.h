#include<iostream>
#include<time.h>
#include<vector>
#include<string.h>
#include<conio.h>
#include<Windows.h> 
using namespace std;
//struct
struct Pair
{
    int x; 
    int y;
};
//struct

//ConsoleFnction.cpp
void Invisible_Cursor();

void Gotoxy(int x, int y);

void SetColor(string BG_Color, string Text_Color);
void ResetColor();

Pair Show_Mouse_Pos();
Pair GetMousePosWin(MOUSE_EVENT_RECORD mer);

//ConsoleFnction.cpp
