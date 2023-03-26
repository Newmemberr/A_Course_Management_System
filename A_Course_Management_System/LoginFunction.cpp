#include"MyLib.h"
int Main_Page()
{
	Draw_Border(27, 9, 17, 5);
	string s[3];
	int your_choice = 0;

	s[0] = "Sign In";
	s[1] = "Sign Up";
	s[2] = "  Exit  ";
	your_choice = Choice1(s, 3,  32, 10, "white", "light blue", "white", "black");
	return your_choice;
}
void SignIn_Page()
{
	bool Wrong_Username = false;
	bool Wrong_Password = false;
	Transition();

here:

	Write("Username: ", 20, 7, "white", "black");
	Draw_Border(30,6, 20, 3);

	Write("Password: ", 20, 10, "white", "black");
	Draw_Border(30, 9, 20, 3);
	//---------------
	string s[2];

	s[0] = "Sign in as a student";
	s[1] = "Sign in as a staff member";

	Pair coordinate[2];

	coordinate[0].x = 10;
	coordinate[0].y = 13;

	coordinate[1].x = 40;
	coordinate[1].y = 13;

	for (int i = 0;i < 2;i++)
	{
		Gotoxy(coordinate[i].x, coordinate[i].y); cout << s[i];
	}
	//---------------

	if (Wrong_Username)
	{
		Write("Wrong Username", 27, 5, "white", "red");
		Wrong_Username = false;
	}
	if (Wrong_Password)
	{
		Write("Wrong Password", 27, 5, "white", "red");
		Wrong_Password = false;
	}

	Gotoxy(31, 7);
	Invisible_Cursor(TRUE);
	string username;
	cin >> username;

	Gotoxy(31, 10);
	string password;
	cin >> password;
	Invisible_Cursor(FALSE);

	int your_choice = 0;
	your_choice = Choice2(s, 2, coordinate, "white", "blue", "white", "black"); //
	//-----------------------------------------------------------------------//
	string job;
	if (your_choice == 0) job = "Student";
	else if (your_choice == 1) job = "Staff_member";

	//Ktra username--------------------------------
	string temp = "Data\\\\" + job + "\\\\List_Of_Users.TXT";
	fstream list;
	list.open(temp, ios::in);
	while (list >> temp)
	{
		if (temp == username)
		{
			list.close();
			break;
		}
	}
	if (list.is_open())
	{
		list.close();
		Wrong_Username = true;
		system("cls");
		goto here;
	}

	string link = "Data\\\\" + job + "\\\\" + username + "\\\\" + "Password.TXT"; //khoi tao link

	fstream file;
	file.open(link, ios::in);

	string true_password;
	file >> true_password;
	if (true_password != password) // ktra password
	{
		Wrong_Password = true;
		system("cls");
		file.close();
		goto here;
	}
	file.close();
	return;
}
