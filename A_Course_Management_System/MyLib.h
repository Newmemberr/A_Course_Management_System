#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<Windows.h> 

using namespace std;

//struct
typedef struct
{
    int x; 
    int y;
} Pair;

//struct

//ConsoleFnction.cpp
void Invisible_Cursor(bool k);

void Gotoxy(short x, short y);

void SetColor(string BG_Color, string Text_Color);
void ResetColor();

void Change_Text_Size(int a, int b);
//ConsoleFnction.cpp

//SupportFunction.cpp
void Write(string s, int x, int y, string BG_Color, string Text_Color);

int Choice1(string* s, int n, int x, int y, string BG_Color_1, string BG_Color_2, string Text_Color_1, string Text_Color_2);
int Choice2(string* s, int n, Pair* coordinate, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2);

void Draw_Border(int x, int y, int a, int b);

void Transition();
//SupportFunction.cpp

//LoginFunction.cpp
int Main_Page();

void SignIn_Page();
//LoginFunction.cpp