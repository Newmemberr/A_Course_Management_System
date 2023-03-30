#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#include<conio.h>
#include<Windows.h> 
#define Main_BG_Color "white"
#define Main_Text_Color "black"
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

//SupportFunction.cpp-----------------------------------------------
void Write(string s, int x, int y, string BG_Color, string Text_Color);

//di chuyen con tro chon theo phuong thang dung
int Choice1(string* s, int n, int x, int y, string BG_Color_1, string BG_Color_2, string Text_Color_1, string Text_Color_2);
//di chuyen con tro chon theo phuong ngang
int Choice2(string* s, int n, Pair* coordinate, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2);

//ve khung
void Draw_Border(int x, int y, int a, int b, string BG_Color, string Text_Color);

void Draw_Space_Rectangle(int x, int y, int a, int b, string Color);

void Transition_1(); // chuyen canh trong 1 page
void Transition_2(); // chuyen canh tu page nay sang page khac
//SupportFunction.cpp----------------------------------------------

//LoginFunction.cpp
int Main_Page(); // No.00

int SignIn_Page(int last_page); //No.01

int SignUp_Page(int last_page); //No.02
//LoginFunction.cpp