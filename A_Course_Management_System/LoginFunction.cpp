#include"MyLib.h"
int Main_Page()
{
	Draw_Border(27, 9, 17, 5);
	string s[3];
	int your_choice = 0;

	s[0] = "Sign In";
	s[1] = "Sign Up";
	s[2] = " Exit  ";
	your_choice = Choice(s, 3, 32, 10, "white", "blue");
	switch (your_choice)
	{
		case 0:
			return 1;
		case 1:
			return 2;
		case 3:
			return -2;
		default:
			return -1;
	}
}

int SignIn_Page(string& username, string& userjob)
{
	bool Wrong_Username = false;
	bool Wrong_Password = false;

here:

	Transition();

	//ve khung-----------------------------
	Write("Sign In:", 13, 3, Default_BG_Color, "blue");
	if (Wrong_Username) //truong hop sai username
	{
		Write("Wrong Username", 27, 3, Default_BG_Color, "red");
		Wrong_Username = false;
		Write("Username: ", 20, 5);
		Draw_Border(30, 4, 20, 3, Default_BG_Color, "red");
	}
	else
	{
		Write("Username: ", 20, 5);
		Draw_Border(30, 4, 20, 3);
	}
	if (Wrong_Password) //truong hop sai password
	{
		Write("Wrong Password", 27, 3, Default_BG_Color, "red");
		Wrong_Password = false;
		Write("Password: ", 20, 8);
		Draw_Border(30, 7, 20, 3, Default_BG_Color, "red");
	}
	else
	{
		Write("Password: ", 20, 8);
		Draw_Border(30, 7, 20, 3);
	}
	//--------------------------

	string s[3];

	s[0] = "   Sign in as a student   ";
	s[1] = " Sign in as a staff member";
	s[2] = "         Go back          ";

	for (int i = 0;i < 3;i++)
	{
		Gotoxy(25,10+i); cout << s[i];
	}
	//----------------------------------------------------------
	Gotoxy(31, 5);
	Show_Cursor(TRUE);
 
	getline(cin,username); //Nhap username

	Gotoxy(31, 8);
	string password;
	char c;
	while (true) //Nhap password
	{
		c = _getch();
		if (c == 13) break;
		else if (c == 8)
		{
			password.erase(password.end() - 1, password.end());
			Gotoxy(31 + (int)password.size(), 8);
			cout << " ";
			Gotoxy(31 + (int)password.size(), 8);
		}
		else
		{
			password += c;
			cout << "*";
		}
	}
	Show_Cursor(FALSE);

	int your_choice = 0;
	your_choice = Choice(s, 3, 25, 10, "white", "blue"); //
	if (your_choice == 2) return -1;

	//Phan loai kieu nguoi dung (student, staff_member)--------------------------------------------------------------//
	if (your_choice == 0) userjob = "Student";
	else if (your_choice == 1) userjob = "Staff_member";

	//Ktra username--------------------------------
	string link = "Data\\" + userjob + "\\List_Of_User.TXT"; // open file
	
	if (!Check_If_String_Is_Existed(link, username)) //ktra xem user name co ton tai hay khong
	{
		//neu khong ton tai username
		Wrong_Username = true;
		goto here;
	}
	//-----------------------------------
	link = "Data\\" + userjob + "\\" + username + "\\Password.TXT"; // open file
	fstream file(link, ios::in);
	string true_password;
	file >> true_password;
	
	if (true_password != password) // ktra password
	{
		Wrong_Password = true;
		file.close();
		goto here;
	}
	file.close();
	
	switch (your_choice) // di toi trang tiep theo
	{
		case 0:
			return 3; //student
		case 1:
			return 4; //staff member
		case 2:
			return -1; //go back
		default:
			return -1; 
	}
}

int SignUp_Page(string& username, string& userjob)
{
	bool valid_username = true;
	bool valid_password = true;
	bool existed_username = false;
here:

	Transition();
	Write("Sign Up:", 13, 3, Default_BG_Color, "blue");
	//ve khung-----------------------------------------------------
	if (!valid_username)
	{
		Write("Username is invalid", 27, 3, Default_BG_Color, "red");
		valid_username = true;
	}
	else if (existed_username)
	{
		Write("Username is existed", 27, 3, Default_BG_Color, "red");
		existed_username = false;
	}
	else if (!valid_password)
	{
		Write("Password is invalid", 27, 3, Default_BG_Color, "red");
		valid_password = true;
	}
	Write("Username: ", 20, 5);
	Draw_Border(30, 4, 20, 3);
	Write("Password: ", 20, 8);
	Draw_Border(30, 7, 20, 3);
	//--------------------//
	string s[3];

	s[0] = "   Sign in as a student   ";
	s[1] = " Sign in as a staff member";
	s[2] = "         Go back          ";

	for (int i = 0;i < 3;i++)
	{
		Gotoxy(25, 10 + i); cout << s[i];
	}
	//---------------------------------------------------------
	
	Gotoxy(31, 5);
	Show_Cursor(TRUE);
	getline(cin, username); //Nhap username

	Gotoxy(31, 8);
	string password;
	char c;
	while (true) //Nhap password
	{
		c = _getch();
		if (c == 13) break;
		else if (c == 8)
		{
			password.erase(password.end() - 1, password.end());
			Gotoxy(31 + (int)password.size(), 8);
			cout << " ";
			Gotoxy(31 + (int)password.size(), 8);
		}
		else
		{
			password += c;
			cout << "*";
		}
	}

	Show_Cursor(FALSE);
	//-------------------------------
	int your_choice = 0;
	your_choice = Choice(s, 3, 25, 10, "white", "blue"); 
	if (your_choice == 2) return -1;

	if (your_choice == 0) userjob = "Student";
	else if (your_choice == 1) userjob = "Staff_Member";

	// ktra username da ton tai hay chua va dua username vao list_of_users-------------------
	for (int i = 0;i < username.size();i++) // ktra tinh hop le cua username
	{
		if (!(isalpha(username[i]) || isdigit(username[i])))
		{
			valid_username = false;
			goto here;
		}
	}
	string link = "Data\\" + userjob + "\\List_Of_User.TXT"; // ktra username co ton tai hay chua
	if (Check_If_String_Is_Existed(link, username))
	{
		existed_username = true;
		goto here;
	}
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
	fstream file(link, ios::out | ios::app);
	file << (username + '\n'); // neu da hop le va chua ton tai thi ghi username vao file list_of_user
	file.close();
	//----------------------------------------------------------------------------//
	// tao thu muc Data\userjob\username -----------------
	string temp = "MD Data\\" + userjob + "\\" + username;
	system(temp.c_str());
	// tao file password.txt trong thu muc username
	link = "Data\\" + userjob + "\\" + username+"\\Password.TXT";
	file.open(link, ios::out);
	file << password; // ghi password vao file password.txt
	file.close();


	switch (your_choice) // di toi trang tiep theo
	{
		case 0:
			return 3; //student
		case 1:
			return 4; // staff member
		case 2:
			return -1; // go back
		default:
			return -1;
	}
}
