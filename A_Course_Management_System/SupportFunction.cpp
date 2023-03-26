#include"MyLib.h"
// Viet chu tai vi tri (x,y)
void Write(string s, int x, int y, string BG_Color, string Text_Color)
{
	Gotoxy(x, y);
	SetColor(BG_Color, Text_Color);
	cout << s;
	ResetColor();
	return;
}

int Choice1(string* s, int n, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < n;i++)
	{
		Gotoxy(x, y + i); cout << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case 72:
		{
			if (your_choice > 0)
			{
				Write(s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 80:
		{
			if (your_choice < n - 1)
			{
				Write(s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 13:
			ResetColor();
			return your_choice;
		}
	}
}
int Choice2(string* s, int n, Pair* coordinate, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(coordinate[0].x, coordinate[0].y); cout << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < n;i++)
	{
		Gotoxy(coordinate[i].x, coordinate[i].y); cout << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case 75:
		{
			if (your_choice > 0)
			{
				Write(s[your_choice], coordinate[your_choice].x, coordinate[your_choice].y , BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(s[your_choice], coordinate[your_choice].x, coordinate[your_choice].y , BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 77:
		{
			if (your_choice < n - 1)
			{
				Write(s[your_choice], coordinate[your_choice].x, coordinate[your_choice].y , BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(s[your_choice], coordinate[your_choice].x, coordinate[your_choice].y , BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 13:
			ResetColor();
			return your_choice;
		}
	}
}

// Ve khung bat dau tu (x,y) co chieu ngang a don vi, chieu doc b don vi
void Draw_Border(int x, int y, int a, int b)
{
	ResetColor();
	a--;
	b--;
	Gotoxy(x, y); cout << char(201);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y); cout << char(205);
	}
	Gotoxy(x+a, y); cout << char(187);
	for (int i = 1; i < b; i++)
	{
		Gotoxy(x, y + i); cout << char(186);
		Gotoxy(x+a, y + i); cout << char(186);
	}
	Gotoxy(x, y+b); cout << char(200);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y+b); cout << char(205);
	}
	Gotoxy(x+a, y+b); cout << char(188);
}

void Transition()
{
	system("cls");
}