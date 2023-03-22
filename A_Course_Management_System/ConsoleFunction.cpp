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

Pair GetMousePosWin(MOUSE_EVENT_RECORD mer)
{
    Pair ans;
    int x, y;
    INPUT_RECORD Inrec;
    DWORD eventRead;
    HANDLE hStdIn;
    DWORD dwMode;
    bool Captured = false;
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    SetConsoleMode(hStdIn, dwMode | ENABLE_MOUSE_INPUT);

    GetConsoleMode(hStdIn, &dwMode);

    SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));
    do
    {
        PeekConsoleInput(hStdIn, &Inrec, 1, &eventRead);
        if (eventRead)
        {
            ReadConsoleInput(hStdIn, &Inrec, 1, &eventRead);
            ans.x = Inrec.Event.MouseEvent.dwMousePosition.X;
            ans.y = Inrec.Event.MouseEvent.dwMousePosition.Y;
            return ans;
        }
    } while (true);
}

Pair Show_Mouse_Pos()
{
    Pair ans;
    HANDLE hStdin;
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    fdwMode = ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hStdin, fdwMode);

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);

    while (true)
    {
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
        
        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType) {
            case MOUSE_EVENT: 
                ans = GetMousePosWin(irInBuf[i].Event.MouseEvent);
                return ans;
            default:
                break;
            }
        }
    }
}