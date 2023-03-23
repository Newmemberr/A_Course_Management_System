#include<iostream>
#include<fstream>
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

void Change_Text_Size(int a, int b);
//ConsoleFnction.cpp

//SupportFunction.cpp
void Write(string s, int x, int y, string BG_Color, string Text_Color);
int Choice(vector<string> s, int x, int y, string BG_Color_1, string BG_Color_2, string Text_Color_1, string Text_Color_2);
//SupportFunction.cpp

//LoginFunction.cpp
int Main_Page();
//LoginFunction.cpp