#include"MyLib.h"
int Main_Page()
{
	Draw_Border(27, 9, 17, 5, Main_BG_Color, Main_Text_Color);
	string s[3];
	int your_choice = 0;

	s[0] = "Sign In";
	s[1] = "Sign Up";
	s[2] = "  Exit  ";
	your_choice = Choice1(s, 3, 32, 10, "white", "light blue", Main_BG_Color, Main_Text_Color);
	return your_choice;
}

int SignIn_Page(int last_page)
{
	bool Wrong_Username = false;
	bool Wrong_Password = false;

here:

	Transition_1();

	//ve khung-----------------------------
	if (Wrong_Username) //truong hop sai username
	{
		Write("Wrong Username", 27, 3, Main_BG_Color, "red");
		Wrong_Username = false;
		Write("Username: ", 20, 5, Main_BG_Color, Main_Text_Color);
		Draw_Border(30, 4, 20, 3, Main_BG_Color, "red");
	}
	else
	{
		Write("Username: ", 20, 5, Main_BG_Color, Main_Text_Color);
		Draw_Border(30, 4, 20, 3, Main_BG_Color, Main_Text_Color);
	}
	if (Wrong_Password) //truong hop sai password
	{
		Write("Wrong Password", 27, 3, Main_BG_Color, "red");
		Wrong_Password = false;
		Write("Password: ", 20, 8, Main_BG_Color, Main_Text_Color);
		Draw_Border(30, 7, 20, 3, Main_BG_Color, "red");
	}
	else
	{
		Write("Password: ", 20, 8, Main_BG_Color, Main_Text_Color);
		Draw_Border(30, 7, 20, 3, Main_BG_Color, Main_Text_Color);
	}
	//--------------------------

	string s[3];

	s[0] = "->   Sign in as a student   ";
	s[1] = "-> Sign in as a staff member";
	s[2] = "->         Go back          ";

	for (int i = 0;i < 3;i++)
	{
		Gotoxy(25,10+i); cout << s[i];
	}
	//----------------------------------------------------------
	Gotoxy(31, 5);
	Invisible_Cursor(TRUE);
	string username; 
	getline(cin,username); //Nhap username

	Gotoxy(31, 8);
	string password;
	getline(cin,password); //Nhap password
	Invisible_Cursor(FALSE);

	int your_choice = 0;
	your_choice = Choice1(s, 3, 25, 10, "white", "blue", Main_BG_Color, Main_Text_Color); //
	if (your_choice == 2) return last_page;

	//Phan loai kieu nguoi dung (student, staff_member)--------------------------------------------------------------//
	string job;
	if (your_choice == 0) job = "Student";
	else if (your_choice == 1) job = "Staff_member";

	//Ktra username--------------------------------
	string temp = "Data\\" + job + "\\List_Of_User.TXT"; // open file
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
		goto here;
	}
	//-----------------------------------
	string link = "Data\\" + job + "\\" + username + "\\Password.TXT"; // open file
	fstream file;
	file.open(link, ios::in);
	string true_password;
	file >> true_password;

	if (true_password != password) // ktra password
	{
		Wrong_Password = true;
		file.close();
		goto here;
	}
	file.close();
	return 1; // di toi trang tiep theo
}

int SignUp_Page(int last_page)
{
	bool valid_username = true;
	bool valid_password = true;
	bool existed_username = false;
here:

	Transition_1();
	//ve khung-----------------------------------------------------
	if (!valid_username)
	{
		Write("Username is invalid", 27, 3, Main_BG_Color, "red");
		valid_username = true;
	}
	else if (existed_username)
	{
		Write("Username is existed", 27, 3, Main_BG_Color, "red");
		existed_username = false;
	}
	else if (!valid_password)
	{
		Write("Password is invalid", 27, 3, Main_BG_Color, "red");
		valid_password = true;
	}
	Write("Username: ", 20, 5, Main_BG_Color, Main_Text_Color);
	Draw_Border(30, 4, 20, 3, Main_BG_Color, Main_Text_Color);
	Write("Password: ", 20, 8, Main_BG_Color, Main_Text_Color);
	Draw_Border(30, 7, 20, 3, Main_BG_Color, Main_Text_Color);
	//--------------------//
	string s[3];

	s[0] = "->   Sign in as a student   ";
	s[1] = "-> Sign in as a staff member";
	s[2] = "->         Go back          ";

	for (int i = 0;i < 3;i++)
	{
		Gotoxy(25, 10 + i); cout << s[i];
	}
	//---------------------------------------------------------
	
	Gotoxy(31, 5);
	Invisible_Cursor(TRUE);
	string username;
	getline(cin, username); //Nhap username

	Gotoxy(31, 8);
	string password;
	getline(cin,password); //Nhap password

	Invisible_Cursor(FALSE);
	//-------------------------------
	int your_choice = 0;
	your_choice = Choice1(s, 3, 25, 10, "white", "blue", Main_BG_Color, Main_Text_Color); //
	if (your_choice == 2) return last_page;

	string job;
	if (your_choice == 0) job = "Student";
	else if (your_choice == 1) job = "Staff_member";

	// ktra username da ton tai hay chua va dua username vao list_of_users-------------------
	for (int i = 0;i < username.size();i++) // ktra tinh hop le cua username
	{
		if (!(isalpha(username[i]) || isdigit(username[i])))
		{
			valid_username = false;
			goto here;
		}
	}
	string link = "Data\\" + job + "\\List_Of_User.TXT"; // ktra username co ton tai hay chua
	fstream file(link, ios::in);
	string temp;
	while (file >> temp)
	{
		if (temp == username)
		{
			existed_username = true;
			file.close();
			goto here;
		}
	}
	file.close();
	//---------------------------------------------------------------------
	for (int i = 0;i < password.size();i++) //ktra tinh hop le cua password
	{
		if (!(isalpha(password[i]) || isdigit(password[i]))) 
		{
			valid_password = false;
			goto here;
		}
	}
	//-----------------------------------------
	file.open(link, ios::out | ios::app);
	file << (username + '\n'); // neu da hop le va chua ton tai thi ghi username vao file list_of_user
	file.close();
	//----------------------------------------------------------------------------//
	// tao thu muc Data\job\username -----------------
	temp = "MD Data\\" + job + "\\" + username;
	system(temp.c_str());
	// tao file password.txt trong thu muc username
	link = "Data\\" + job + "\\" + username+"\\Password.txt";
	file.open(link, ios::out);
	file << password; // ghi password vao file password.txt
	file.close();
	return your_choice;
}
