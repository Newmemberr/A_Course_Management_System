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

	string link_to_list = link + "\\School_Year_List.TXT"; 
	if (Check_If_String_Is_Existed(link_to_list, name))  //ktr xem co ton tai nam hoc giong nhau hay khong
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

	string link_to_directory = link + "\\" + name; //tao thu muc new school year
	string temp = "MD " + link_to_directory;

	string link_to_Semester_Directory= temp + "\\Semester"; // tao thu muc Semester trong muc new school year
	system(link_to_Semester_Directory.c_str());

	// tao file Semesters_List
	string link_to_Semesters_List = link_to_Semester_Directory + "\\Semesters_List.TXT";
	fstream file_Semesters_List(link_to_Semesters_List, ios::out);
	file_Semesters_List << 0; // dua vao file so 0 nghia la chua co hoc ki nao dc tao ra
	file_Semesters_List.close();
	
	string link_to_Classes_Directory = temp + "\\Classes"; // tao thu muc Classes trong muc new school year
	system(link_to_Classes_Directory.c_str());

	// dua lop nam 2, 3, 4 vao thu muc classes
	Add_Old_Class_Into_New_School_Year(link, name);
}

int Add_Old_Class_Into_New_School_Year(string link, string current_school_year)
{

	// tach school name thanh 2 bien int school name 1 va 2
	int school_year_1, school_year_2;
	int index1 = 0;
	string school_year;
	while (index1 < current_school_year.size() && current_school_year[index1]!='-')
	{
		school_year += current_school_year[index1];
		index1++;
	}
	school_year_1 = atoi(school_year);
	index1++;
	school_year = "";
	while (index1 < current_school_year.size())
	{
		school_year += current_school_year[index1];
		index1++;
	}
	school_year_2 = atoi(school_year);

	string link_to_current_school_year = link + "\\" + current_school_year;
	string link_to_current_class_list = link_to_current_school_year + "\\Classes\\Classes_List.TXT";
	string link_to_school_year_list = link + "\\" + "School_Year_List.TXT";

	string graduated_year = itoa(school_year_1 - 4) + "-" + itoa(school_year_2-4);
	string link_to_graduated_class_list = link + "\\" + graduated_year + "\\Classes\\Classes_List.TXT";

	fstream School_Year_List_File(link_to_school_year_list, ios::in); // mo file school_year_list
	if (School_Year_List_File.is_open())
	{
		for (int i = 0;i < 3;i++)// lan luot duyet qua 3 nam trc do
		{
			school_year_1 -= 1;
			school_year_2 -= 1;
			school_year = itoa(school_year_1) + "-" + itoa(school_year_2); // school_year : ten cua nam hoc trc do

			if (Check_If_String_Is_Existed(link_to_school_year_list, school_year)) // ktr xem nam hoc trc do co ton tai khong
			{
				string link_to_old_class_list = link + "\\" + school_year + "\\Classes\\Classes_List.TXT";
				fstream old_class_list(link_to_old_class_list, ios::in); // mo file classes_list cua nam hoc trc do
				if (old_class_list.is_open())
				{
					string old_class_name;
					while (getline(old_class_list, old_class_name)) // doc cac lop tu file classes_list cua nam hoc trc do va luu vao bien old_class_name
					{
						if (Check_If_String_Is_Existed(link_to_current_class_list, old_class_name)) // ktra xem lop cu da dc them vao nam hoc moi hay chua
						{
							// neu da ton tai thi khong them nua
							continue;
						}
						if (Check_If_String_Is_Existed(link_to_graduated_class_list, old_class_name)) // ktra xem lop nay da tot nghiep hay chua
						{
							// neu da tot nghiep roi thi ko them nua
							continue;
						}
						fstream current_class_list(link_to_current_class_list, ios::out | ios::app); // mo file class_list hien tai
						if (current_class_list.is_open())
						{
							current_class_list << (old_class_name + "\n"); // luu class nay vao lai current_class_list
							current_class_list.close();
						}

						string link_to_old_class = link + "\\" + school_year + "\\Classes\\" + old_class_name + ".TXT";
						fstream old_class(link_to_old_class, ios::in); // mo cac class_file cu the
						if (old_class.is_open())
						{
							string link_to_class = link_to_current_school_year + "\\Classes\\" + old_class_name + ".TXT";

							fstream new_old_class(link_to_class, ios::out); // tao file moi cua old class trong nam hoc moi
							if (new_old_class.is_open())
							{
								string temp;
								while (getline(old_class, temp)) // chuyen du lieu cua lop cu sang file cua nam hoc moi 
								{
									new_old_class << temp << "\n";
								}
								new_old_class.close();
							}
							old_class.close();
						}
					}
					old_class_list.close();
				}
			}

		}
		School_Year_List_File.close();
	}
	
	return 1;
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

int Classes_Page(string link, string Current_School_Year)
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
	else if (k == 1) Add_a_Student(link_to_current_class, 20, 5);
	else if (k == 2) Add_a_List_of_Student(link_to_current_class, 15, 5);
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

void Add_a_Student(string link_to_current_class,int x, int y)
{
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

	int cnt = 0;
	string temp;
	fstream file(link_to_current_class, ios::in);
	if (file.is_open())
	{
		while (getline(file, temp))
		{
			cnt++;                          // dem so luong hoc sinh
		}
		file.close();
	}

	file.open(link_to_current_class, ios::out | ios::app); // dua du lieu vao file
	if (file.is_open())
	{
		file << cnt + 1 << ",";
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

void Add_a_List_of_Student(string link_to_current_class, int x, int y)
{
	string CSV_File_Link;
	int cnt_csv = 0; // so hoc sinh trong file csv
	int cnt_current_class = 0; // so hoc sinh trong file current class
	Draw_Space_Rectangle(x, y, 40, 3);
	Draw_Border(x, y, 40, 3);
	Write("CSV File:", x+1, y+1);
	Gotoxy(x + 11, y + 1); 

	Show_Cursor(TRUE);
	getline(cin, CSV_File_Link);     
	Show_Cursor(false);

	
	for (int i = 0;i < CSV_File_Link.size();i++)
	{
		if (CSV_File_Link[i] == '\\')
		{
			CSV_File_Link.insert(CSV_File_Link.begin() + i, '\\');
			i++;
		}
	}
	fstream file(CSV_File_Link, ios::in);
	if (file.is_open())
	{
		string temp;
		while (getline(file, temp)) cnt_csv++; // dem so luong hoc sinh trong file csv
		file.close();
	}
	Student* student = new Student[cnt_csv];

	file.open(CSV_File_Link, ios::in);
	if (file.is_open())
	{
		for (int i = 0;i < cnt_csv;i++)
		{
			Read_Student_Info(file, student[i]); // dua du lieu tu file csv vao mang student
		}
		file.close();
	}

	file.open(link_to_current_class, ios::in);
	if (file.is_open())
	{
		string temp;
		while (getline(file, temp)) cnt_current_class++;     //dem so hoc sinh cu trong class
		file.close();
	}
	file.open(link_to_current_class, ios:: out | ios::app);
	if (file.is_open())
	{
		for (int i = 0; i < cnt_csv; i++)                        // dua du lieu tu mang student vao file class.txt
		{
			file << i + 1 + cnt_current_class << ",";
			file << (student[i].Student_ID + ",");
			file << (student[i].First_Name + ",");
			file << (student[i].Last_Name + ",");
			file << (student[i].Gender + ",");
			file << (student[i].Date_Of_Birth + ",");
			file << (student[i].Social_ID);
			file << '\n';
		}
		file.close();
	}
	return;
}

int Read_Student_Info(fstream& file, Student& a)
{

	if (file.is_open())
	{
		string temp;
		getline(file, temp, ','); a.No = atoi(temp.c_str());
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
	printf("%3d ", student.No);
	printf("%8s ", student.Student_ID.c_str());
	printf("%8s ", student.First_Name.c_str());
	printf("%8s ", student.Last_Name.c_str());
	printf("%4s ", student.Gender.c_str());
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
		if (c == -32) c = _getch();

		switch (c)
		{
			case 77:
			{
				page++;
				if (page * Max_line >= size)
				{
					page--;
					break;
				}

				Draw_Space_Rectangle(x, y, 61, Max_line + 2);
				Draw_Border(x, y, 61, Max_line + 2);
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

		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			Show_student_Info(student[i + Max_line * page], x + 1, y + i + 1);
		}

	}

}

int Semesters_Page(string link, string current_school_year)
{
	string link_to_Semester = link + "\\" + current_school_year + "\\Semester";
	string link_to_Semesters_List = link_to_Semester + "\\Semesters_List.TXT";

here:

	Transition();
	fstream file_Semesters_List(link_to_Semesters_List, ios::in);
	int cnt = 0; // so luong hoc ki da tao ra
	if (file_Semesters_List.is_open())
	{
		file_Semesters_List >> cnt;
		file_Semesters_List.close();
	}

	int your_choice = 0;

	string* list;
	if (cnt < 3) // neu so luong hoc ki < 3 thi co the them hoc ki moi
	{
		list = new string[cnt + 2];

		for (int i = 0; i < cnt;i++)
		{
			list[i] = "Semester " + itoa(i+1);
		}

		list[cnt] = "Create new semester";
		list[cnt + 1] = "Go back";

		your_choice = Choice(list, cnt + 2, 25, 2, "white", "blue");

		if (your_choice == cnt) // create new semester
		{
			Create_New_Semester(link_to_Semester);
			delete[] list;
			goto here;
		}
		if (your_choice == cnt + 1)  // quay tro ve school_year_page
		{
			delete[] list;
			return -1;
		}
	}
	else // neu so luong hoc ki = 3 thi khong the them hoc ki moi
	{
		list = new string[cnt + 1];

		for (int i = 0; i < cnt;i++)
		{
			list[i] = "Semester " + itoa(i+1);
		}

		list[cnt] = "Go back";

		your_choice = Choice(list, cnt + 1, 25, 2, "white", "blue");

		if (your_choice == cnt)  // quay tro ve school_year_page
		{
			delete[] list;
			return -1;
		}
	}

	string link_to_current_Semester = link_to_Semester + "\\" + list[your_choice];
	Courses_Page(link_to_current_Semester);
	goto here;
	return 0;
}

void Create_New_Semester(string link_to_Semester)
{
	string link_to_Semesters_List = link_to_Semester + "//Semesters_List.TXT";
	int cnt = 0;
	fstream file_Semesters_List(link_to_Semesters_List, ios::in);
	if (file_Semesters_List.is_open())
	{
		file_Semesters_List >> cnt;  // so luong hoc ki da tao ra
		file_Semesters_List.close();
	}
	file_Semesters_List.open(link_to_Semesters_List, ios::out);
	if (file_Semesters_List.is_open())
	{
		cnt++; // so luong hoc ki tang len 1
		file_Semesters_List << cnt;  // dua du lieu moi vao file
		file_Semesters_List.close();
	}
	//tao thu muc cua hoc ki moi
	string link_to_new_Semester = "MD " + link_to_Semester + "\\" + "Semester_" + itoa(cnt);
	system(link_to_new_Semester.c_str()); 
	
	// tao file courses_list trong hoc ki moi tao ra
	string link_to_courses_list = link_to_Semester + "\\" + "Semester_" + itoa(cnt) + "\\Courses_List.TXT";
	fstream file_courses_list(link_to_courses_list, ios::out);
	file_courses_list.close();
}

void Courses_Page(string link_to_current_Semester)
{

}