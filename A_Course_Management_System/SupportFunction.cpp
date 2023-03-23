#include"MyLib.h"
void Write(string s, int x, int y, string BG_Color, string Text_Color)
{
	Gotoxy(x, y);
	SetColor(BG_Color, Text_Color);
	cout << s;
	ResetColor();
	return;
}

int Choice(vector<string> s, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < s.size();i++)
	{
		Gotoxy(x, y + i); cout << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		switch (c)
		{
		case 'w':
		{
			if (your_choice > 0)
			{
				Write(s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 's':
		{
			if (your_choice < s.size() - 1)
			{
				Write(s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 13:
			return your_choice;
		}
	}
}