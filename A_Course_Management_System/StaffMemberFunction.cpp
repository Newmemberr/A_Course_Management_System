#include"MyLib.h"
int School_Years_Page(string link, int& classes_or_courses, string& current_school_year)
{
	string temp;
	temp = "MD " + link;
	system(temp.c_str()); // tao thu mua School_Year
	string link_to_file= link + "\\School_Year_List.TXT";

here:

	Transition();
	
	fstream file;
	file.open(link_to_file, ios::in);
	int cnt = 0;
	
	while (getline(file, temp))
	{
		cnt++;                          // so luong nam hoc da co
	}
	file.close();

	string* list = new string[cnt + 2];

	file.open(link_to_file, ios::in);
	for (int i = 0; getline(file, temp);i++)
	{
		list[i] = "> " + temp; // luu du lieu vao list
	}
	file.close();

	list[cnt] =     "> Create new school year";
	list[cnt + 1] = "> Quit          ";
	int your_choice = Choice(list, cnt + 2, 25, 2, "white", "blue");

	if (your_choice == cnt) // create new school year
	{
		Create_New_School_Year(link);
		Sort_File(link_to_file);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1) return -2; // thoat chuong trinh

	//xoa nhung ki tu dac biet o dau
	list[your_choice].erase(list[your_choice].begin(), list[your_choice].begin() + 2);
	
	classes_or_courses = Classes_Or_Semester();
	current_school_year =  list[your_choice];

	delete[] list;
	return 5;
}

void Create_New_School_Year(string link)
{

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

	string link_to_file = link + "\\School_Year_List.TXT"; 
	if (Check_If_String_Is_Existed(link_to_file, name))  //ktr xem co ton tai nam hoc giong nhau hay khong
	{
		Write("This name is existed", 42, 9, "black", "white");
		while (true)
		{
			char k = _getch();
			if (k == 13) return;
		}
	}
	fstream file(link_to_file, ios::out | ios::app); 
	
	file << (name + '\n'); //dua vao file
	file.close();

	string link_to_directory = link + "\\" + name; //tao thu muc new school year
	string temp = "MD " + link_to_directory;
	string link_to_Semester_Directory= temp + "\\Semester"; // tao thu muc Semester trong muc new school year
	system(link_to_Semester_Directory.c_str());
	
	string link_to_Classes_Directory = temp + "\\Classes"; // tao thu muc Classes trong muc new school year
	system(link_to_Classes_Directory.c_str());
	return;
}

int Classes_Or_Semester()
{
	Draw_Space_Rectangle(30, 10, 16, 4);
	Draw_Border(30, 10, 16, 4);
	string s[2];
	s[0] = "Classes";
	s[1] = "Semester";
	int your_choice = Choice(s, 2, 34, 11, "white", "blue");
	return your_choice;
}

int Classes_Page(int last_page, string link, string Current_School_Year, string& Class_Name)
{
	string link_to_class = link + "\\" + Current_School_Year + "\\Classes";
	string link_to_list = link_to_class + "\\Classes_List.TXT";
	
here:

	Transition();
	fstream file(link_to_list, ios::in);
	string temp;
	int cnt = 0;

	while (getline(file, temp))
	{
		cnt++;                          // so luong lop da co
	}
	file.close();

	string* list = new string[cnt + 2];

	file.open(link_to_list, ios::in);
	for (int i = 0; getline(file, temp);i++)
	{
		list[i] = "> " + temp; // luu du lieu vao list
	}
	file.close();

	list[cnt] =     "> Create new class";
	list[cnt + 1] = "> Go back    ";

	int your_choice = Choice(list, cnt + 2, 25, 2, "white", "blue");

	if (your_choice == cnt) // create new school year
	{
		Create_New_Class(link_to_class);
		Sort_File(link_to_class);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1) return -1; // quay tro ve school_year_page

	//xoa nhung ki tu khong can thiet o dau
	list[your_choice].erase(list[your_choice].begin(), list[your_choice].begin() + 2);

	Show_Student(link_to_class, list[your_choice]);
	return 0;
}

void Create_New_Class(string link_to_class)
{

	Draw_Space_Rectangle(42, 10, 25, 3);
	Draw_Border(42, 10, 25, 3);
	Write("Name: ", 43, 11);

	Show_Cursor(true);
	string name;
	getline(cin, name); //Nhap ten lop hoc moi
	Show_Cursor(false);

	for (int i = 0;i < name.size();i++) //chuan hoa name
	{
		if (name[i] == ' ')
		{
			name.erase(name.begin() + i, name.begin() + i + 1);
			i--;
		}
	}

	string link_to_list = link_to_class + "\\Classes_List.TXT";
	if (Check_If_String_Is_Existed(link_to_list, name))  //ktr xem co ton tai class giong nhau hay khong
	{
		
		Write("This name is existed", 42, 9, "black", "white");
		while (true)
		{
			char k = _getch();
			if (k == 13) return;
		}
	}
	fstream file(link_to_list, ios::out | ios::app);

	file << (name + '\n'); //dua vao file
	file.close();

	string link_to_file = link_to_class + "\\" + name + ".TXT"; //tao file class.txt
	file.open(link_to_file, ios::out);
	file.close();

	return;
}

void Show_Student(string link_to_class, string current_class)
{
	
}
