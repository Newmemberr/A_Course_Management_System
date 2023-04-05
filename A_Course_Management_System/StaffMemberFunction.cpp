#include"MyLib.h"
int School_Years_Page(string link, int& classes_or_courses, string& current_school_year)
{
	string temp;
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

	string* list = new string[cnt + 3];

	file.open(link_to_file, ios::in);
	for (int i = 0; getline(file, temp);i++)
	{
		list[i] = temp; // luu du lieu vao list
	}
	file.close();

	list[cnt] =     "Create new school year";
	list[cnt + 1] = "Log Out";
	list[cnt + 2] = "Quit";
	int your_choice = Choice(list, cnt + 3, 25, 2, "white", "blue");

	if (your_choice == cnt) // create new school year
	{
		Create_New_School_Year(link);
		Sort_File(link_to_file);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1)  // tro ve trang dang nhap
	{
		delete[] list;
		return 0;
	}
	if (your_choice == cnt + 2) // Thoat chuong trinh
	{
		delete[] list;
		return -1; 
	}
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
	int your_choice = Choice(s, 2, 32, 11, "white", "blue");
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
		list[i] = temp; // luu du lieu vao list
	}
	file.close();

	list[cnt] =     "Create new class";
	list[cnt + 1] = "Go back";

	int your_choice = Choice(list, cnt + 2, 25, 2, "white", "blue");

	if (your_choice == cnt) // create new class
	{
		Create_New_Class(link_to_class);
		Sort_File(link_to_class);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1)  // quay tro ve school_year_page
	{
		delete[] list;
		return -1;
	}
	int k = Add_Or_View_Student();

	string link_to_current_class = link_to_class + "\\" + list[your_choice] + ".TXT";
	delete[] list;

	if (k == 0) View_Student(link_to_current_class);
	else if (k == 1) Add_a_Student(link_to_current_class);
	//else if (k == 2) Add_a_List_of_Student(link_to_current_class);
	goto here;

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

	file << (name + '\n'); //dua vao file classes_list
	file.close();

	string link_to_file = link_to_class + "\\" + name + ".TXT"; //tao file class.txt
	file.open(link_to_file, ios::out);
	file.close();

	return;
}

int Add_Or_View_Student()
{
	Draw_Space_Rectangle(30, 10, 30, 5);
	Draw_Border(30, 10, 30, 5);
	string s[3];
	s[0] = "View all students";
	s[1] = "Add a student";
	s[2] = "Add a list of students";
	int your_choice = Choice(s, 3, 32, 11, "white", "blue");
	return your_choice;
}

void View_Student(string link_to_current_class)
{
	Transition();
	int cnt = 0;
	string temp;
	fstream file(link_to_current_class, ios::in);
	if (file.is_open())
	{
		while (getline(file, temp)) cnt++; // dem so luong hoc sinh
		file.close();
	}
	if (cnt > 0)
	{
		Student* student = new Student[cnt];
		file.open(link_to_current_class, ios::in);
		if (file.is_open())
		{
			for (int i = 0;i < cnt;i++)
			{
				Read_Student_Info(file, student[i]); // dua du lieu vao mang student
			}
			file.close();
			Show_Students_in_a_Class(student, cnt, 5, 3); // show student
		}

	}
}

void Add_a_Student(string link_to_current_class)
{
	int x = 20, y = 5;
	Student student;
	Draw_Space_Rectangle(x, y, 30, 8);
	Draw_Border(x, y, 30, 8);

	Write("Student ID   :", x + 1, y + 1);
	Write("First Name   :", x + 1, y + 2);
	Write("Last Name    :", x + 1, y + 3);
	Write("Gender       :", x + 1, y + 4);
	Write("Date of Birth:", x + 1, y + 5);
	Write("Social ID    :", x + 1, y + 6);

	Show_Cursor(true);
	Gotoxy(x + 16, y + 1); getline(cin, student.Student_ID);
	Gotoxy(x + 16, y + 2); getline(cin, student.First_Name);
	Gotoxy(x + 16, y + 3); getline(cin, student.Last_Name);
	Gotoxy(x + 16, y + 4); getline(cin, student.Gender);
	Gotoxy(x + 16, y + 5); getline(cin, student.Date_Of_Birth);
	Gotoxy(x + 16, y + 6); getline(cin, student.Social_ID);
	Show_Cursor(false);

	fstream file(link_to_current_class, ios::out | ios::app);
	if (file.is_open())
	{
		file << (student.Student_ID + ",");
		file << (student.First_Name + ",");
		file << (student.Last_Name + ",");
		file << (student.Gender + ",");
		file << (student.Date_Of_Birth + ",");
		file << (student.Social_ID);
		file << '\n';
		file.close();
	}
}

int Read_Student_Info(fstream& file, Student& a)
{

	if (file.is_open())
	{
		string temp;
		getline(file, a.Student_ID, ',');
		getline(file, a.First_Name, ',');
		getline(file, a.Last_Name, ',');
		getline(file, a.Gender, ',');
		getline(file, a.Date_Of_Birth, ',');
		getline(file, a.Social_ID);
	}
	else return 0;
	return 1;
} 

void Show_student_Info(Student& student, int x, int y)
{
	Gotoxy(x, y);
	printf("%8s ", student.Student_ID.c_str());
	printf("%8s ", student.First_Name.c_str());
	printf("%8s ", student.Last_Name.c_str());
	printf("%8s ", student.Gender.c_str());
	printf("%10s ", student.Date_Of_Birth.c_str());
	printf("%8s ", student.Social_ID.c_str());
	return;
}

void Show_Students_in_a_Class(Student* student, int size, int x, int y, string BG_Color, string Text_Color)
{
	Transition();
	int Max_line = 7;

	Draw_Space_Rectangle(x, y, 61, Max_line + 2);
	Draw_Border(x, y, 61, Max_line + 2);

	char c = 0;
	int page = 0;
	for (int i = 0; i < Max_line && i < size;i++)
	{
		Show_student_Info(student[i], x + 1, y + i + 1);
	}
	
	while (true)
	{
		c = _getch();
		if (c == -32)c = _getch();

		switch (c)
		{
			case 77:
			{
				page++;
				if (page * 7 >= size)
				{
					page--;
					break;
				}

				Draw_Space_Rectangle(x, y, 61, Max_line + 2);
				Draw_Border(x, y, 61, Max_line +2 );
				break;
			}
			case 75:
			{
				page--;
				if (page < 0)
				{
					page++;
					break;
				}

				Draw_Space_Rectangle(x, y, 61, Max_line + 2);
				Draw_Border(x, y, 61, Max_line + 2);
				break;

			}
			case 27:
			{
				return;
			}
		}

		for (int i = 0; i < Max_line && i < size;i++)
		{
			Show_student_Info(student[i + Max_line * page], x + 1, y + i + 1);
		}

	}

}