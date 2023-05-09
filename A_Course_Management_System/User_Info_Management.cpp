#include"MyLib.h"
int Starting_Page(string link)
{

	while (true)
	{
		Transition();
		string list[4]{ "Start","Change Password","View profile infomation","Log out" };
		int your_choice = Choice(list, 4, 25, 2, "white", "blue");
		switch (your_choice)
		{
		case 0:
		{
			return 1; // bat dau lam viec voi he thong
		}
		case 1:
		{
			Change_Password(link);
			break;
		}
		case 2:
		{
			View_Profile_Infomation(link);
			break;
		}
		case 3:
		{
			return 0;
		}
		}
	}
	
}
void Change_Password(string link)
{
	string list[2]{ "Old Password:", "New Password:" };
	string old_pass, new_pass;
	string true_pass;
here:
	//ve bang
	int x = 20, y = 7;
	Draw_Space_Rectangle(x, y, 30, 4);
	Draw_Border(x, y, 30, 4);
	x++; y++;
	for (int i = 0;i < 2;i++)
	{
		Write(list[i], x, y + i);
	}
	
	// Nhap password
	Show_Cursor(true);
	Gotoxy(x + (int)list[0].size() + 1, y);
	getline(cin, old_pass);

	Gotoxy(x + (int)list[1].size() + 1, y + 1);
	getline(cin, new_pass);
	Show_Cursor(false);

	//lay password dung tu file
	string link_to_password = link + "\\Password.TXT";
	fstream file(link_to_password, ios::in);
	if (file.is_open())
	{
		file >> true_pass;
		file.close();
	}
	if (old_pass != true_pass)
	{
		Write("Wrong Password", x - 1, y - 2, "white", "red");
		goto here;
	}
	// luu password moi vao file
	file.open(link_to_password, ios::out | ios::trunc);
	if (file.is_open())
	{
		file << new_pass;
		file.close();
	}
}

void View_Profile_Infomation(string link)
{
	string info_attr[3]{ "ID:","Name:","Date of birth:" };
	string info[3];
	//mo file lay du lieu
	string link_to_info = link + "\\Information.TXT";
	fstream file(link_to_info, ios::in);
	if (file.is_open())
	{
		for (int i = 0;i < 3;i++)
		{
			getline(file, info[i]);
		}
		file.close();
	}
	// ve bang
	int x = 13, y = 7;
	Draw_Space_Rectangle(x, y, 35, 5);
	Draw_Border(x, y, 35, 5);
	x++; y++;
	for (int i = 0;i < 3;i++)
	{
		Write(info_attr[i] + " " + info[i], x, y + i);
	}
	char c = 0;
	while ((c != 27) && (c != 13)) // c != Enter hoac Esc
	{
		c = _getch();
	}
}
string Get_User_ID(string link)
{
	string link_to_info = link + "\\Information.TXT";
	string user_id;
	fstream file(link_to_info, ios::in);
	if (file.is_open())
	{
		getline(file, user_id);
		file.close();
	}
	return user_id;
}