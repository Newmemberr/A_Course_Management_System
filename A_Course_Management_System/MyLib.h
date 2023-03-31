#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#include<conio.h>
#include<Windows.h> 
#define Default_BG_Color "white"
#define Default_Text_Color "black"
using namespace std;

//-------------------------Struct-----------------------------------------------------
typedef struct
{
    int x; 
    int y;
} Pair;


//------------------------ConsoleFnction.cpp-----------------------------------------------------
void Show_Cursor(bool k);

void Gotoxy(short x, short y);

void SetColor(string BG_Color, string Text_Color);
void ResetColor();

void Change_Text_Size(int a, int b);

//------------------------SupportFunction.cpp------------------------------------------------------
void Write(string s, int x, int y, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

//   di chuyen con tro chon theo phuong thang dung
int Choice(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

//   ve khung
void Draw_Border(int x, int y, int a, int b, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

void Draw_Space_Rectangle(int x, int y, int a, int b, string Color = Default_BG_Color);

void Transition(); 

bool Check_If_String_Is_Existed(string link, string s); // ktra xem 1 string co ton  tai trong 1 file hay khong

void Sort_File(string link); // sap xep du lieu trong file theo chieu tang dan

//------------------------Management.cpp------------------------------------------------------ 
int Management();

//------------------------LoginFunction.cpp------------------------------------------------------
int Main_Page(); // No.00

int SignIn_Page(int last_page, string& username, string& userjob); //No.01

int SignUp_Page(int last_page, string& username, string& userjob); //No.02

//-------------------------StaffMemberFunction.cpp-----------------------------------------------------
int Begining_Of_A_School_Year_Page(int last_page, string link, int& classes_or_courses, string& current_school_year); // No.03
void Create_New_School_Year(string link);
int Classes_Or_Semester();