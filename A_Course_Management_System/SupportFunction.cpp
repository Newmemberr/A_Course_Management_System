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

int Choice1(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < sizeOfs;i++)
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
			if (your_choice < sizeOfs - 1)
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
	ResetColor();
}
int Choice2(string* s, int sizeOfs, Pair* coordinate, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(coordinate[0].x, coordinate[0].y); cout << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < sizeOfs;i++)
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
			if (your_choice < sizeOfs - 1)
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
	ResetColor();
}


void Draw_Border(int x, int y, int a, int b, string BG_Color, string Text_Color)
{
	// Ve khung bat dau tu (x,y) co chieu ngang a don vi, chieu doc b don vi
	SetColor(BG_Color, Text_Color);
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
	ResetColor();
}
void Draw_Space_Rectangle(int x, int y, int a, int b, string Color)
{
	SetColor(Color, Color);
	for (int i = 0;i < b;i++)
	{
		Gotoxy(x, y+i);
		for (int j = 0;j < a;j++)
		{
			cout << " ";
		}
	}
	ResetColor();
}
void Transition_1() 
{
	Draw_Border(0, 0, 71, 19, Main_BG_Color, Main_Text_Color);
	Draw_Space_Rectangle(1, 1, 69, 17,"white");
}
void Transition_2() 
{
	system("cls");
	Draw_Border(0, 0, 71, 19, Main_BG_Color, Main_Text_Color);
}