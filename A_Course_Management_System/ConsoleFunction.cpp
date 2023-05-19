#include"MyLib.h"

void Show_Cursor(bool k) // xoa dau nhay 
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = k;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Gotoxy(short x, short y) //di chuyen con tro den vi tri (x,y)
{
    static HANDLE h = NULL;
    if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void SetColor(string BG_Color, string Text_Color) // doi mau
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
    SetColor(Default_BG_Color, Default_Text_Color);
}

void Change_Text_Size(int a, int b)
{
    // a la chieu ngang
    // b la chieu doc
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.dwFontSize.X = a;
    fontex.dwFontSize.Y = b;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
    /*CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = x;
    cfi.dwFontSize.Y = x;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_BOLD;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),FALSE, &cfi);*/
}
void Set_Full_Screen()
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void DisableCtrButton(bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void Setting_Interface()
{
    DisableCtrButton(1, 1);
    SetWindowSize(71, 18);
    DisableResizeWindow();
    ShowScrollbar(false);
    Show_Cursor(FALSE);
    Change_Text_Size(30, 30);
    system("color 70");
}
