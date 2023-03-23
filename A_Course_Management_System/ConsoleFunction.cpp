#include"MyLib.h"

void Invisible_Cursor() // xoa dau nhay 
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Gotoxy(int x, int y) //di chuyen con tro den vi tri (x,y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void SetColor(string BG_Color, string Text_Color) // change color
{
    int backgound_color = 0, text_color = 0;
    string a[16]{ "black", "blue", "green", "aqua", "red", "purple", "yellow", "white", "gray", "light blue", "light green", " light aqua", "light red", "light purple", "light yellow", "bright white"};
    for (int i = 0;i < 16;i++)
    {
        if (a[i] == BG_Color) backgound_color = i;
        if (a[i] == Text_Color) text_color = i;
    }
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
    /*
    0.black 1.blue 2.green 3.aqua 4.red 5.purple 6.yellow 7.white 8.gray 9.light blue 10.light green
    11.light aqua 12.light red 13.light purple 14.light yellow 15.bright white
    */
}

void ResetColor() //dat lai mau goc
{
    SetColor("black", "white");
}

void Change_Text_Size(int a, int b)
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.dwFontSize.X = a;
    fontex.dwFontSize.Y = b;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}
