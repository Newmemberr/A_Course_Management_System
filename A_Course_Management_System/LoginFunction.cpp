#include"MyLib.h"
int Main_Page()
{
	//Draw
	Gotoxy(27, 9); cout << char(201);
	for (int i = 1;i < 16;i++)
	{
		Gotoxy(27 + i, 9); cout << char(205);
	}
	Gotoxy(43, 9); cout << char(187);
	for (int i = 1; i < 3; i++)
	{
		Gotoxy(27, 9 + i); cout << char(186);
		Gotoxy(43, 9 + i); cout << char(186);
	}
	Gotoxy(27, 12); cout << char(200);
	for (int i = 1;i < 16;i++)
	{
		Gotoxy(27 + i, 12); cout << char(205);
	}
	Gotoxy(43, 12); cout << char(188);
	//
	vector<string> s;
	int your_choice = 0;

	s.push_back("Sign In");
	s.push_back("Sign Up");
	your_choice = Choice(s, 32, 10, "white", "light blue", "white", "black");

	
	return your_choice;
}
