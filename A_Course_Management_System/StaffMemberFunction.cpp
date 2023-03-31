#include"MyLib.h"
int Begining_Of_A_School_Year_Page(int last_page, string link, int& classes_or_courses, string& current_school_year)
{
	string link_to_file= link + "\\School_Year_List.txt";

here:

	Transition();
	fstream file(link_to_file, ios::in);
	int cnt = 0;
	string temp;
	while (getline(file, temp))
	{
		cnt++;                          // so luong nam hoc da co
	}
	file.close();

	string* list = new string[cnt + 2];
	file.open(link_to_file, ios::in);
	for (int i = 0; getline(file, temp);i++)
	{
		list[i] = "      " + temp;
	}
	
	list[cnt] = "Create a new school year";
	list[cnt + 1] = "         Quit           ";
	int your_choice = Choice(list, cnt + 2, 25, 2, "white", "blue");

	delete[] list;

	if (your_choice == cnt) // create new school year
	{
		Create_New_School_Year(link);
		Sort_File(link_to_file);
		goto here;
	}
	if (your_choice == cnt + 1) return -1; // thoat chuong trinh
	//xoa dau cach
	while (list[your_choice][0] == ' ') list[your_choice].erase(list[your_choice].begin(), list[your_choice].begin() + 1);

	classes_or_courses = Classes_Or_Semester();
	current_school_year =  list[your_choice];
	return 5;
}
void Create_New_School_Year(string link)
{
	bool name_is_existed = false;

here:

	if (name_is_existed)
	{
		Write("This name is existed", 34, 6, "black", "white");
	}
	Draw_Space_Rectangle(42, 10, 25, 3);
	Draw_Border(42, 10, 25, 3);
	Write("Name: ", 43, 11);
	
	Show_Cursor(true);
	string name;
	getline(cin, name); //Nhap ten new school year
	Show_Cursor(false);

	for (int i = 0;i < name.size();i++) //chuan hoa name
	{
		if (name[i] == ' ')
		{
			name.erase(name.begin() + i, name.begin() + i + 1);
			i--;
		}
	}

	string link_to_file = link + "\\School_Year_List.txt"; 
	if (Check_If_String_Is_Existed(link_to_file, name))  //ktr xem co ton tai nam hoc giong nhau hay khong
	{
		name_is_existed = true;
		goto here;
	}
	fstream file(link_to_file, ios::out | ios::app); 
	file << (name + '\n'); //dua vao file
	file.close();
	
	string link_to_directory = link + "\\" + name; //tao thu muc new school year
	string temp = "MD " + link_to_directory;
	system(temp.c_str());
	return;
}
int Classes_Or_Semester()
{
	Draw_Space_Rectangle(30, 10, 10, 4);
	Draw_Border(30,10,10,4);
	string s[2];
	s[0] = "Classes";
	s[1] = "Semester";
	int your_choice = Choice(s, 2, 31, 11, "white", "blue");
	return your_choice;
}