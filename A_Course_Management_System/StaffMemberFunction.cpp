#include"MyLib.h"
int School_Years_Page(string link, int& classes_or_courses, string& current_school_year)
{
	string temp;
	string link_to_file= link + "\\School_Year_List.TXT";

here:

	Transition();
	Write(" School Years's Page : ", 4, 2, "black", "bright white");
	int cnt = 0;

	cnt = Number_of_Line(link_to_file); // so luong nam hoc da co

	string* list = new string[cnt + 2];

	fstream file(link_to_file, ios::in);
	if (file.is_open())
	{
		for (int i = 0; getline(file, temp);i++)
		{
			list[i] = temp; // luu du lieu vao list
		}
		file.close();
	}

	list[cnt] =     "Create new school year";
	list[cnt + 1] = "Go back";
	int your_choice = Choice(list, cnt + 2, 25, 4, "white", "blue");

	if (your_choice == cnt) // create new school year
	{
		Create_New_School_Year(link);
		Sort_File(link_to_file);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1) // quay tro ve
	{
		delete[] list;
		return 6; 
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
						// tao thu muc class o nam hoc moi
						string link_to_new_class = link_to_current_school_year + "\\Classes\\" + old_class_name;
						string create_link_to_new_class_dir = "MD " + link_to_new_class;
						system(create_link_to_new_class_dir.c_str());
						// Copy students_list tu nam hoc moi sang nam hoc cu
						string link_to_old_class = link + "\\" + school_year + "\\Classes\\" + old_class_name;
						Copy_File(link_to_old_class + "\\Students_List.TXT", link_to_new_class + "\\Students_List.TXT");
						// tao file Scoreboard.TXT
						string link_to_new_class_scoreboard = link_to_new_class + "\\Scoreboard.TXT";
						fstream file_to_new_class_scoreboard(link_to_new_class_scoreboard, ios::out);
						if (file_to_new_class_scoreboard.is_open())
						{
							file_to_new_class_scoreboard.close();
						}
					}
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
	Write(" Classes's Page: ", 4, 2, "black", "bright white");
	int cnt = 0;

	cnt = Number_of_Line(link_to_list);// so luong lop da co

	string* list = new string[cnt + 2];

	fstream file(link_to_list, ios::in);
	string temp;
	for (int i = 0; getline(file, temp);i++)
	{
		list[i] = temp; // luu du lieu vao list
	}
	file.close();

	list[cnt] =     "Create new class";
	list[cnt + 1] = "Go back";

	int your_choice = Choice(list, cnt + 2, 25, 4, "white", "blue");

	if (your_choice == cnt) // create new class
	{
		Create_New_Class(link_to_class);
		Sort_File(link_to_list);
		delete[] list;
		goto here;
	}
	if (your_choice == cnt + 1)  // quay tro ve school_year_page
	{
		delete[] list;
		return -1;
	}
	int k = Add_Or_View_Student();

	string link_to_current_class = link_to_class + "\\" + list[your_choice] + "\\Students_List.TXT";
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
	// tao thu muc lop hoc moi
	string link_to_class_dir = "MD " + link_to_class + "\\" + name;
	system(link_to_class_dir.c_str());

	string link_to_file = link_to_class + "\\" + name + "\\Students_List.TXT"; //tao file Students_List.txt
	file.open(link_to_file, ios::out);
	if (file.is_open())
	{
		file << "No,Student ID,First Name,Last Name,Gender,Date of Birth,Social ID\n";
		file.close();
	}
	
	// tao file scoreboard
	link_to_file = link_to_class + "\\" + name + "\\Scoreboard.TXT";
	file.open(link_to_file, ios::out);
	if (file.is_open())
	{
		file.close();
	}
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

void View_Student(string link_to_file)
{
	int cnt = 0;
	string temp;

	cnt = Number_of_Line(link_to_file) - 1;// dem so luong hoc sinh
	
	if (cnt > 0)
	{
		Student* student = new Student[cnt];
		fstream file(link_to_file, ios::in);
		if (file.is_open())
		{
			getline(file, temp); // bo dong dau tien
			for (int i = 0;i < cnt;i++)
			{
				Read_Student_Info(file, student[i]); // dua du lieu vao mang student
			}
			file.close();
			Show_Students(student, cnt, 3, 3); // show student
		}
	}
	else
	{
		Draw_Error_Board("No Data", 25, 7);
	}
}

void Add_a_Student(string link_to_file,int x, int y)
{
	Student student;
	Draw_Space_Rectangle(x, y, 30, 8);
	Draw_Border(x, y, 30, 8);

	int cnt = 0;
	string temp;
	cnt = Number_of_Line(link_to_file) - 1;// dem so luong hoc sinh
	
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

	fstream file(link_to_file, ios::out | ios::app); // dua du lieu vao file
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

void Add_a_List_of_Student(string link_to_file, int x, int y)
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
	if (file.fail())
	{
		Draw_Error_Board("Path is not exist", 23, 7);
		return;
	}
	else file.close();
	// bo dong dau tien
	// dem so luong hoc sinh trong file csv
	cnt_csv = Number_of_Line(CSV_File_Link) - 1;
	
	Student* student = new Student[cnt_csv];
	
	file.open(CSV_File_Link, ios::in);
	if (file.is_open())
	{
		string temp;
		getline(file, temp); // bo dong dau tien
		
		for (int i = 0;i < cnt_csv;i++)
		{
			Read_Student_Info(file, student[i]); // dua du lieu tu file csv vao mang student
		}
		file.close();
		
	}
	//dem so hoc sinh cu trong class
	cnt_current_class = Number_of_Line(link_to_file) - 1;
	
	file.open(link_to_file, ios:: out | ios::app);
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
	printf("%10s ", student.Student_ID.c_str());
	printf("%10s ", student.First_Name.c_str());
	printf("%9s ", student.Last_Name.c_str());
	printf("%6s ", student.Gender.c_str());
	printf("%9s ", student.Date_Of_Birth.c_str());
	printf("%9s ", student.Social_ID.c_str());
	return;
}

void Show_Students(Student* student, int size, int x, int y)
{
	Transition();
	int Max_line = 10;

	char c = 0;
	int page = 0;

	// ve bang
	Draw_Space_Rectangle(x, y, x + 62, Max_line + 4);

	for (int i = 0; i < Max_line && i < size;i++)
	{
		Show_student_Info(student[i], x + 1, y + i + 1);
	}

	// ve bang
	int arr[6]{5,16,27,37,44,53};
	Draw_Table(x, y - 2, x + 62, Max_line + 4, arr, 6);
	

	int coor_X[7];
	int coor_Y[7];
	coor_X[0] = x + 1;
	coor_Y[0] = y - 1;
	for (int i = 1;i < 7;i++)
	{
		coor_X[i] = x + arr[i - 1] + 1;
		coor_Y[i] = y - 1;
	}

	string title[7]{ "STT", "Student ID", "First Name", "Last Name", "Gender", "Birthday", "Social ID" };
	Write_Title(coor_X, coor_Y, title, 7);

	while (true)
	{
		c = _getch();
		if (c == -32) c = _getch();

		switch (c)
		{
			case 77: // right
			{
				page++;
				if (page * Max_line >= size)
				{
					page--;
					break;
				}
				break;
			}
			case 75: //left
			{
				page--;
				if (page < 0)
				{
					page++;
					break;
				}
				break;

			}
			case 27: //Esc
			{
				return;
			}
		}
		Draw_Space_Rectangle(x, y, x + 62, Max_line + 4);

		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			Show_student_Info(student[i + Max_line * page], x + 1, y + i + 1);
		}
		//ve bang
		
		Draw_Table(x, y - 2, x + 62, Max_line + 4, arr, 6);

	}

}

int Semesters_Page(string link, string current_school_year)
{
	string link_to_Semester = link + "\\" + current_school_year + "\\Semester";
	string link_to_Semesters_List = link_to_Semester + "\\Semesters_List.TXT";

here:

	Transition();
	Write(" Semesters's Page: ", 4, 2, "black", "bright white");
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
			list[i] = "Semester_" + itoa(i+1);
		}

		list[cnt] = "Create new semester";
		list[cnt + 1] = "Go back";

		your_choice = Choice(list, cnt + 2, 25, 4, "white", "blue");

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
			list[i] = "Semester_" + itoa(i+1);
		}

		list[cnt] = "Go back";

		your_choice = Choice(list, cnt + 1, 25, 4, "white", "blue");

		if (your_choice == cnt)  // quay tro ve school_year_page
		{
			delete[] list;
			return -1;
		}
	}

	string link_to_current_Semester = link_to_Semester + "\\" + list[your_choice];
	Courses_Page(link_to_current_Semester);
	delete[] list;
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
	string link_to_list = link_to_current_Semester + "\\Courses_List.TXT";

here:

	Transition();
	Write(" Courses's Page: ", 4, 2, "black", "bright white");
	string temp;
	int cnt = 0;
	cnt = Number_of_Line(link_to_list);// so luong khoa hoc da co
	
	string* ID_list = new string[cnt + 2];
	string* Name_list = new string[cnt + 2];

	fstream File_To_List(link_to_list, ios::in);
	if (File_To_List.is_open())
	{
		Name_list[0] = "Create new course";
		string Course_ID = "";
		string Course_Name = "";
		for (int i = 1; getline(File_To_List, Course_ID);i++)
		{
			// Tim Course_Name tu file
			string link_to_course_information = link_to_current_Semester + "\\" + Course_ID +"\\Information.TXT";
			fstream file_to_course_information(link_to_course_information, ios::in);
			if (file_to_course_information.is_open())
			{
				getline(file_to_course_information, temp);  // lay ra id
				getline(file_to_course_information, temp); // lay ra ten
				Course_Name = temp;
				file_to_course_information.close();
			}

			ID_list[i] = Course_ID; // luu ID cua khoa hoc
			Name_list[i] = Course_Name; // luu TEN cua khoa hoc vao list
		}
		File_To_List.close();
		Name_list[cnt + 1] = "Go back";
	}
	
	int your_choice = Choice(Name_list, cnt + 2, 25, 4, "white", "blue");

	if (your_choice == 0) // create new course
	{
		Create_New_Course(link_to_current_Semester);
		delete[] Name_list;
		delete[] ID_list;
		goto here;
	}
	if (your_choice == cnt + 1)  // quay tro ve 
	{
		delete[] Name_list;
		delete[] ID_list;
		return ;
	}
	string link_to_current_course = link_to_current_Semester + "\\" + ID_list[your_choice];
	Work_With_Course(link_to_current_course);

	delete[] Name_list;
	delete[] ID_list;
	goto here;
}

void Create_New_Course(string link_to_current_Semester)
{

	Transition();
	Course New_Course;
	//ve bang
	int x = 20, y = 4;
	Draw_Space_Rectangle(x, y, 40, 10);
	Draw_Border(x, y, 40, 10);
	x++;
	y++;
	Write("ID:", x, y);
	Write("Name:", x, y + 1);
	Write("Class:", x, y + 2);
	Write("Teacher:", x, y + 3);
	Write("Number of credits:", x, y + 4);
	Write("Maximum number of students:", x, y + 5);
	Write("Day:", x, y + 6);
	Write("Session:", x, y + 7);
	
	// dien thong tin
	Show_Cursor(true);
	Gotoxy(x + 4, y); getline(cin, New_Course.ID);
	Gotoxy(x + 6, y + 1); getline(cin, New_Course.Name);
	Gotoxy(x + 7, y + 2); getline(cin, New_Course.Class);
	Gotoxy(x + 9, y + 3); getline(cin, New_Course.Teacher);
	Gotoxy(x + 19, y + 4); getline(cin, New_Course.Number_Of_Credits);
	Gotoxy(x + 28, y + 5); getline(cin, New_Course.Maximum_Student);
	Gotoxy(x + 5, y + 6); getline(cin, New_Course.Day_Of_Week);
	Gotoxy(x + 9, y + 7); getline(cin, New_Course.Session);
	Show_Cursor(false);

	// kiem tra xem khoa hoc co ton tai hay chua
	string temp;
	string link_to_course_list = link_to_current_Semester + "\\Courses_List.TXT";
	fstream file_to_course_list(link_to_course_list, ios::in);
	if (file_to_course_list.is_open())
	{
		while (getline(file_to_course_list, temp))
		{
			if (temp == New_Course.ID)
			{
				Draw_Error_Board("Course is already existed", x + 4, y + 2);
				return;
			}
		}
		file_to_course_list.close();
	}
	// dua khoa hoc moi vao course list
	file_to_course_list.open(link_to_course_list, ios::out | ios::app);
	if (file_to_course_list.is_open())
	{
		file_to_course_list << New_Course.ID << "\n";
		file_to_course_list.close();
	}
	//tao thu muc khoa hoc moi
	string New_Course_Dir = "MD " + link_to_current_Semester + "\\" + New_Course.ID;
	system(New_Course_Dir.c_str());
	//tao file information va dua thong tin vao
	string link_to_course_information = link_to_current_Semester + "\\" + New_Course.ID + "\\Information.TXT";
	fstream file_to_course_information(link_to_course_information, ios::out);
	if (file_to_course_information.is_open())
	{
		file_to_course_information << New_Course.ID << "\n";
		file_to_course_information << New_Course.Name << "\n";
		file_to_course_information << New_Course.Class << "\n";
		file_to_course_information << New_Course.Teacher << "\n";
		file_to_course_information << New_Course.Number_Of_Credits << "\n";
		file_to_course_information << New_Course.Maximum_Student << "\n";
		file_to_course_information << New_Course.Day_Of_Week << "\n";
		file_to_course_information << New_Course.Session << "\n";
		file_to_course_information.close();
	}
	//tao file student list
	string link_to_course_student_list = link_to_current_Semester + "\\" + New_Course.ID + "\\Students_List.TXT";
	fstream file_to_course_student_list(link_to_course_student_list, ios::out);
	if (file_to_course_student_list.is_open())
	{
		file_to_course_student_list << "No,Student ID,First Name,Last Name,Gender,Date of Birth,Social ID\n";
		file_to_course_student_list.close();
	}
	// tao file scoreboard
	string link_to_scoreboard = link_to_current_Semester + "\\" + New_Course.ID + "\\Scoreboard.TXT";
	fstream file_to_scoreboard(link_to_scoreboard, ios::out);
	if (file_to_scoreboard.is_open())
	{
		file_to_scoreboard << "No,Student ID,Student Full Name,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
		file_to_scoreboard.close();
	}
}

void Work_With_Course(string link_to_current_course)
{
	string link_to_course_information = link_to_current_course + "\\Information.TXT";
	string link_to_student_list = link_to_current_course + "\\Students_List.TXT";

	// doc tu file so luong hoc sinh toi da trong 1 khoa hoc
	int Max_Student_in_Course = 0;
	fstream file_to_course_information(link_to_course_information, ios::in);
	if (file_to_course_information.is_open())
	{
		string temp;
		for (int i = 0;i < 6;i++) getline(file_to_course_information, temp);
		Max_Student_in_Course = atoi(temp);
		file_to_course_information.close();
	}

	int x = 20, y = 4;
	string s[11];
	s[0] = "View all student in this course";
	s[1] = "Add a student";
	s[2] = "Add a list of student";
	s[3] = "Update course information";
	s[4] = "Remove a student";
	s[5] = "Export a list of students";
	s[6] = "Import the scoreboard";
	s[7] = "View scoreboard of a course";
	s[8] = "Update student's result"; 
	s[9] = "Delete course";
	s[10] = "Go back";

	while (true)
	{
		Transition();

		int your_choice = Choice(s, 11, x, y, "white", "blue");

		switch (your_choice)
		{
			case 0:
			{
				// hien thi tat ca hoc sinh
				View_Student(link_to_student_list);
				break;
			}
			case 1:
			{
				// so luong hoc sinh hien tai trong khoa hoc
				int number_of_student = Number_of_Line(link_to_student_list) - 1;
				// them hoc sinh vao khoa hoc
				if (number_of_student == Max_Student_in_Course)
				{
					Draw_Error_Board("Course is full! ", 23, 7);
				}
				else
				{
					Add_a_Student(link_to_student_list, 30, 6);
					number_of_student++;
				}
				break;
			}
			case 2:
			{
				// them hoc sinh vao khoa hoc dung file csv
				Add_a_List_of_Student(link_to_student_list, 20, 5);
				// so luong hoc sinh hien tai trong khoa hoc
				int number_of_student = Number_of_Line(link_to_student_list)-1;
				if (number_of_student > Max_Student_in_Course)
				{
					Draw_Error_Board("Too many students are added into course", 23, 7);
					Student* student = new Student[Max_Student_in_Course];
					// dua 'Max_Student_in_Course' hoc sinh tu file vao mang student
					fstream file_to_student_list(link_to_student_list, ios::in);
					if (file_to_student_list.is_open())
					{
						string temp;
						getline(file_to_student_list, temp); // bo dong dau tien

						for (int i = 0;i < Max_Student_in_Course; i++)
						{
							Read_Student_Info(file_to_student_list, student[i]);
						}
						file_to_student_list.close();
					}
					// dua du lieu tu mang student vao file
					file_to_student_list.open(link_to_student_list, ios::out, ios::trunc);
					if (file_to_student_list.is_open())
					{
						file_to_student_list << "No,Student ID,First Name,Last Name,Gender,Date of Birth,Social ID\n";
						for (int i = 0;i < Max_Student_in_Course; i++)
						{
							file_to_student_list << i + 1 << ",";
							file_to_student_list << student[i].Student_ID << ",";
							file_to_student_list << student[i].First_Name << ",";
							file_to_student_list << student[i].Last_Name << ",";
							file_to_student_list << student[i].Gender << ",";
							file_to_student_list << student[i].Date_Of_Birth << ",";
							file_to_student_list << (student[i].Social_ID);
							file_to_student_list << '\n';
						}
						file_to_student_list.close();
					}
					delete[] student;
				}
				number_of_student = Max_Student_in_Course;
				break;
			}
			case 3:
			{
				//update course info
				Update_Course_Info(link_to_current_course);
				// cap nhat lai bien Max_Student_in_Course
				file_to_course_information.open(link_to_course_information, ios::in);
				if (file_to_course_information.is_open())
				{
					string temp;
					for (int i = 0;i < 6;i++) getline(file_to_course_information, temp);
					Max_Student_in_Course = atoi(temp);
					file_to_course_information.close();
				}
				break;
			}
			case 4:
			{
				//xoa hoc sinh ra khoi khoa hoc
				int cnt = 0; string temp;
				// doc so luong hoc sinh trong khoa hoc
				cnt = Number_of_Line(link_to_student_list) - 1;
				if (cnt == 0)
				{
					Draw_Error_Board("This course has no student", 20, 5);
					break;
				}
				Student* student = new Student[cnt];
				// dua du lieu vao mang student
				fstream file_to_student_list(link_to_student_list, ios::in);

				getline(file_to_student_list, temp); // bo dong dau tien

				for (int i = 0;i < cnt;i++)
				{
					Read_Student_Info(file_to_student_list, student[i]);
				}
				Show_and_Delete_Students_in_a_Course(student, cnt, 3,3,"white", "blue");
				Update_Student_List(link_to_student_list, student, cnt);
				delete[] student;
				break;
			}
			case 5:
			{
				Export_Students_List(link_to_current_course);
				break;
			}
			case 6:
			{
				Import_Scoreboard(link_to_current_course);
				break;
			}
			case 7:
			{
				Show_Scoreboard(2, 3, link_to_current_course);
				break;
			}
			case 8:
			{
				Show_and_Update_Student_Result(2, 3, link_to_current_course, "white", "blue");
				break;
			}
			case 9:
			{
				// xoa khoa hoc
				bool check = Draw_Warning_Board("Are you sure? ", 25, 7);
				if (check == false) return;
				else Delete_Course(link_to_current_course);
				return;
			}
			case 10:
			{
				// quay ve
				return;
			}
		}
	}

}

void Update_Course_Info(string& link_to_course)
{
	// luu thong tin khoa hoc vao bien course_info
	string link_to_course_information = link_to_course + "\\Information.TXT";
	string course_info[8];
	fstream file_to_course_information(link_to_course_information, ios::in);
	if (file_to_course_information.is_open())
	{
		for (int i = 0;i < 8;i++) file_to_course_information >> course_info[i];

		file_to_course_information.close();
	}
	string Course_Old_ID = course_info[0]; // luu id khoa hoc
	// ve bang
	int x = 20, y = 4;
	Draw_Space_Rectangle(x, y, 40, 10);
	Draw_Border(x, y, 40, 10);
	x++;
	y++;
	Write("ID: " + course_info[0], x, y);
	Write("Name: " + course_info[1], x, y + 1);
	Write("Class: " + course_info[2], x, y + 2);
	Write("Teacher: " + course_info[3], x, y + 3);
	Write("Number of credits: " + course_info[4], x, y + 4);
	Write("Maximum number of students: " + course_info[5], x, y + 5);
	Write("Day: " + course_info[6], x, y + 6);
	Write("Session: " + course_info[7], x, y + 7);
	// thao tac cua nguoi dung
	int a[8]{ 4,6,7,9,19,28,5,9 };
	Gotoxy(int(x + a[0] + course_info[0].size()), y);
	Show_Cursor(true);
	int your_choice = 0;
	while (true)
	{
		bool isalphaordigit = true;
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			isalphaordigit = false;
		}
		switch (c)
		{
			case 72: //up
			{
				if (your_choice > 0)
				{
					your_choice--;
					Gotoxy(int(x + a[your_choice] + course_info[your_choice].size()), y + your_choice);
				}
				break;
			}
			case 80: //down
			{
				if (your_choice < 8)
				{
					your_choice++;
					Gotoxy(int(x + a[your_choice] + course_info[your_choice].size()), y + your_choice);
				}
				break;
			}
			case 8: //backspace
			{
				if (course_info[your_choice].size() > 0)
				{
					course_info[your_choice].erase(course_info[your_choice].end() - 1, course_info[your_choice].end()); //xoa du lieu

					// hien thi lai du lieu moi
					Gotoxy(int(x + a[your_choice] + course_info[your_choice].size()), y + your_choice);
					cout << " ";
					Gotoxy(int(x + a[your_choice] + course_info[your_choice].size()), y + your_choice);
				}
				break;
			}
			case 13: //Enter
			{
				// ktra xem ID sau khi sua co trung voi cac khoa hoc khac ko
				string link_to_course_list = link_to_course + "\\..\\Courses_List.TXT";
				if (course_info[0] != Course_Old_ID && Check_If_String_Is_Existed(link_to_course_list, course_info[0]))
				{
					
					Draw_Error_Board("ID is already existed", 25, 7);
					return;

				}
				// luu thong tin vao file
				file_to_course_information.open(link_to_course_information, ios::out);
				if (file_to_course_information.is_open())
				{
					for (int i = 0;i < 8;i++) file_to_course_information << course_info[i] << endl;

					file_to_course_information.close();
				}

				if(Course_Old_ID != course_info[0]) // neu ID thay doi
				{
					string link_to_new_course = link_to_course + "\\..\\" + course_info[0];
					// tao thu muc moi
					string new_course_dir = "MD " + link_to_new_course;
					system(new_course_dir.c_str());
					//chuyen du lieu sang thu muc moi
					Copy_File(link_to_course + "\\Information.TXT", link_to_new_course + "\\Information.TXT");
					Copy_File(link_to_course + "\\Students_List.TXT", link_to_new_course + "\\Students_List.TXT");
					Copy_File(link_to_course + "\\Scoreboard.TXT", link_to_new_course + "\\Scoreboard.TXT");
					//xoa thu muc cu
					Delete_Course(link_to_course);
					// Them id vao course_list
					fstream file_to_course_list(link_to_course_list, ios::out | ios::app);
					if (file_to_course_list.is_open())
					{
						file_to_course_list << course_info[0] << endl;
						file_to_course_list.close();
					}
					// cap nhat bien link_to_course
					while (link_to_course[link_to_course.size() - 1] != '\\') 
						link_to_course.erase(link_to_course.end() - 1, link_to_course.end());
					link_to_course += course_info[0];
				}
				Show_Cursor(false);
				return;
			}
			default:
			{
				if (isalphaordigit == false) break;
				if (isalpha(c) || isdigit(c))
				{
					course_info[your_choice] += c;
					Write(course_info[your_choice], x + int(a[your_choice]), y + your_choice);
				}
			}

		}
	}
}

void Show_and_Delete_Students_in_a_Course(Student*& student, int& size, int x, int y, string BG_Color, string Text_Color)
{
	Transition();
	int Max_line = 10;
	int your_choice = 0;

	Draw_Space_Rectangle(x, y, x + 62, Max_line + 4);

	char c = 0;
	int page = 0;

	SetColor(BG_Color, Text_Color);
	Show_student_Info(student[0], x + 1, y + 1);
	ResetColor();

	for (int i = 1; i < Max_line && i < size;i++)
	{
		Show_student_Info(student[i], x + 1, y + i + 1);
	}

	// ve bang
	int arr[6]{ 5,16,27,37,44,53 };
	Draw_Table(x, y - 2, x + 62, Max_line + 4, arr, 6);

	int coor_X[7];
	int coor_Y[7];
	coor_X[0] = x + 1;
	coor_Y[0] = y - 1;
	for (int i = 1;i < 7;i++)
	{
		coor_X[i] = x + arr[i - 1] + 1;
		coor_Y[i] = y - 1;
	}

	string title[7]{ "STT", "Student ID", "First Name", "Last Name", "Gender", "Birthday", "Social ID" };
	Write_Title(coor_X, coor_Y, title, 7);

	while (true)
	{
		c = _getch();
		if (c == -32) c = _getch();

		switch (c)
		{
		case 77: //left
		{
			page++;
			if (page * Max_line >= size)
			{
				page--;
				break;
			}
			your_choice = page * Max_line;
			break;
		}
		case 75: //right
		{
			page--;
			if (page < 0)
			{
				page++;
				break;
			}
			your_choice = page * Max_line;
			break;

		}
		case 72: //up
		{
			if (your_choice > Max_line * page)
			{
				your_choice--;
			}
			break;
		}
		case 80: //down
		{
			if (your_choice < Max_line * (page + 1) - 1 && your_choice < size - 1)
			{
				your_choice++;
			}
			break;
		}
		case 13: //Enter
		{
			if (Draw_Warning_Board("Are you sure?", 25, 5))
			{
				Delete_Student(student, size, your_choice);
			}
			break;
		}
		case 27: //Esc
		{
			return;
		}
		}

		Draw_Space_Rectangle(x, y, x + 62, Max_line + 4);

		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			if (i == your_choice - Max_line * page)
			{
				SetColor(BG_Color, Text_Color);
				Show_student_Info(student[your_choice], x + 1, y + i + 1);
				ResetColor();
			}
			else
			{
				Show_student_Info(student[i + Max_line * page], x + 1, y + i + 1);
			}
		}

		Draw_Table(x, y - 2, x + 62, Max_line + 4, arr, 6);

	}

}

void Delete_Student(Student*& student, int& cnt, int& index)
{

	Student* new_student = new Student[cnt - 1];
	for (int i = 0;i < index;i++)
	{
		new_student[i] = student[i];
	}
	for (int i = index + 1;i < cnt;i++)
	{
		new_student[i - 1] = student[i];
	}
	cnt--;
	if (index == cnt) index--;
	delete[] student;
	student = new_student;
}

void Update_Student_List(string link_to_student_list, Student* student, int size) 
{
	fstream file(link_to_student_list, ios::out | ios::trunc);
	if (file.is_open())
	{
		file << "No,Student ID,First Name,Last Name,Gender,Date of Birth,Social ID\n";
		for (int i = 0;i < size;i++)
		{
			file << i + 1 << ",";
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
}

void Export_Students_List(string current_course)
{
	Transition();
	// ve khung
	Draw_Space_Rectangle(18, 5, 30, 3);
	Draw_Border(18, 5, 30, 3);
	Write("Path: ", 19, 6);
	// Nhap path
	Gotoxy(19 + 6, 6); 
	string path;
	Show_Cursor(true);
	getline(cin, path);
	Show_Cursor(false);
	// chuan hoa path
	for (int i = 0;i < path.size();i++)
	{
		if (path[i] == '\\')
		{
			path.insert(path.begin() + i, '\\');
			i++;
		}
	}
	// tao file
	string students_list_link = current_course + "\\Students_List.TXT";
	fstream file_to_students_list(students_list_link, ios::in); // mo file luu du lieu danh sach hoc sinh
	if (file_to_students_list.is_open())
	{
		// bo dong dau cua file student list 
		string temp;
		getline(file_to_students_list, temp);

		fstream file_export(path, ios::out); // tao file export
		if (file_export.is_open())
		{
			file_export << "No,Student ID,Student Full Name,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
			
			while (getline(file_to_students_list, temp, '\n')) // tach va xu li tung dong
			{
				string attr[4]; // tao mang 4 string tuong trung cho No, ID, First, Last Name
				int index = 0;
				for (int i = 0;i < temp.size() && index < 4;i++) // xu li string temp
				{
					if (temp[i] == ',') 
					{
						index++;
					}
					else attr[index] += temp[i]; 
				}
				// dua vao file No, Student ID, Student Full Name
				file_export << attr[0] << "," << attr[1] << "," << attr[2] << " " << attr[3] << endl;
			}
			file_export.close();
		}
		file_to_students_list.close();
	}
}

void Import_Scoreboard(string current_course)
{
	Transition();
	// ve khung
	Draw_Space_Rectangle(18, 5, 30, 3);
	Draw_Border(18, 5, 30, 3);
	Write("Path: ", 19, 6);
	// Nhap path
	Gotoxy(19 + 6, 6);
	string path;
	Show_Cursor(true);
	getline(cin, path);
	Show_Cursor(false);
	// chuan hoa path
	for (int i = 0;i < path.size();i++)
	{
		if (path[i] == '\\')
		{
			path.insert(path.begin() + i, '\\');
			i++;
		}
	}
	// dua du lieu vao file scoreboard
	string scoreboard = current_course + "\\Scoreboard.TXT";
	Copy_File(path, scoreboard);
}

void Show_Scoreboard(int x, int y,string current_course)
{
	Transition();
	
	string scoreboard_link = current_course + "\\Scoreboard.TXT";
	int size = Number_of_Line(scoreboard_link) - 1;
	
	Student_Result* student = new Student_Result[size];
	
	fstream file(scoreboard_link, ios::in); // dua du lieu vao mang student
	int index = 0;
	if (size == 0)
	{
		Draw_Error_Board("No Data", 27, 7);
		return;
	}
	if (file.is_open())
	{
		//bo dong dau
		string temp;
		getline(file, temp);
		
		while (index < size)
		{
			
			getline(file, temp, ','); student[index].No = atoi(temp);
			getline(file, temp, ','); student[index].Student_ID = temp;
			getline(file, temp, ','); student[index].Full_Name = temp;
			getline(file, temp, ','); student[index].Total_Mark = atod(temp);
			getline(file, temp, ','); student[index].Final_Mark = atod(temp);
			getline(file, temp, ','); student[index].Midterm_Mark = atod(temp);
			getline(file, temp, '\n'); student[index].Other_Mark = atod(temp);
			index++;
		}
		file.close();
	}
	
	int Max_line = 10;

	Draw_Space_Rectangle(x, y - 2, x + 65, Max_line + 4);

	char c = 0;
	int page = 0;
	for (int i = 0; i < Max_line && i < size;i++)
	{
		Show_Student_Result(student[i], x + 1, y + i + 1);
	}
	int arr[6]{ 5,16,34,42,50,58 };
	Draw_Table(x, y - 2, x + 65, Max_line + 4, arr, 6);

	int coor_X[7];
	int coor_Y[7];
	coor_X[0] = x + 1;
	coor_Y[0] = y - 1;
	for (int i = 1;i < 7;i++)
	{
		coor_X[i] = x + arr[i - 1] + 1;
		coor_Y[i] = y - 1;
	}

	string title[7]{ "STT", "Student ID", "    Full Name", " Total", " Final", "Midterm", " Other"};
	Write_Title(coor_X, coor_Y, title, 7);

	while (true)
	{
		c = _getch();
		if (c == -32) c = _getch();

		switch (c)
		{
		case 77: // right
		{
			page++;
			if (page * Max_line >= size)
			{
				page--;
			}
			break;
		}
		case 75: // left
		{
			page--;
			if (page < 0)
			{
				page++;
			}
			break;
		}
		case 27: // Esc
		{
			return;
		}
		}
		Draw_Space_Rectangle(x, y, x + 65, Max_line + 4);
		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			Show_Student_Result(student[i + Max_line * page], x + 1, y + i + 1);
		}
		Draw_Table(x, y - 2, x + 65, Max_line + 4, arr, 6);
	}

}

void Show_Student_Result(Student_Result student, int x, int y)
{
	Gotoxy(x, y);
	printf("%3d  ", student.No);
	printf(" %8s  ", student.Student_ID.c_str());
	printf("%16s  ", student.Full_Name.c_str());
	if ((int)student.Total_Mark == 10) printf(" %.2f  ", student.Total_Mark);
	else printf("  %.2f  ", student.Total_Mark);
	if ((int)student.Final_Mark == 10) printf(" %.2f  ", student.Final_Mark);
	else printf("  %.2f  ", student.Final_Mark);
	if ((int)student.Midterm_Mark == 10) printf(" %.2f  ", student.Midterm_Mark);
	else printf("  %.2f  ", student.Midterm_Mark);
	if ((int)student.Other_Mark == 10) printf(" %.2f", student.Other_Mark);
	else printf("  %.2f", student.Other_Mark);
	return;
}

void Delete_Course(string link_to_current_course)
{
	string temp;
	string Current_Course_ID;
	string link_to_course_information = link_to_current_course + "\\Information.TXT";
	string link_to_student_list = link_to_current_course + "\\Students_List.TXT";
	string link_to_scoreboard = link_to_current_course + "\\Scoreboard.TXT";
	//doc course id
	fstream file_to_student_information(link_to_course_information, ios::in);
	if (file_to_student_information.is_open())
	{
		file_to_student_information >> Current_Course_ID;
		file_to_student_information.close();
	}

	// xoa trong course_list
	int cnt = 0;
	string link_to_course_list = link_to_current_course + "\\..\\Courses_List.TXT";
	fstream file_to_course_list(link_to_course_list, ios::in); // dem so luong khoa hoc
	if (file_to_course_list.is_open())
	{
		while (getline(file_to_course_list, temp)) cnt++;
		file_to_course_list.close();
	}

	string* Courses_ID = new string[cnt - 1];
	file_to_course_list.open(link_to_course_list, ios::in); // luu id cac khoa hoc khac khoa hoc hien tai vao mang
	if (file_to_course_list.is_open())
	{
		for (int i = 0;i < cnt - 1;i++)
		{
			getline(file_to_course_list, temp);
			if (temp != Current_Course_ID)
			{
				Courses_ID[i] = temp;
			}
			else
			{
				i--;
			}
		}
		file_to_course_list.close();
	}
	file_to_course_list.open(link_to_course_list, ios::out | ios::trunc); // luu id cac khoa hoc khac khoa hoc hien tai vao file
	if (file_to_course_list.is_open())
	{
		for (int i = 0;i < cnt - 1;i++)
		{
			file_to_course_list << Courses_ID[i] << "\n";
		}
		file_to_course_list.close();
	}
	delete[] Courses_ID;

	//xoa thu muc khoa hoc
	remove(link_to_course_information.c_str()); 
	remove(link_to_student_list.c_str());
	remove(link_to_scoreboard.c_str());
	temp = "RD " + link_to_current_course;
	system(temp.c_str());
}

void Show_and_Update_Student_Result(int x, int y, string link_to_current_course, string BG_Color, string Text_Color)
{
	Transition();
	// luu du lieu tu file student result
	string scoreboard_link = link_to_current_course + "\\Scoreboard.TXT";
	int size = Number_of_Line(scoreboard_link) - 1;

	if (size == 0)
	{
		Draw_Error_Board("No Data", 27, 7);
		return;
	}

	Student_Result* student = new Student_Result[size];

	fstream file(scoreboard_link, ios::in); // dua du lieu vao mang student
	int index = 0;
	if (file.is_open())
	{
		//bo dong dau
		string temp;
		getline(file, temp);

		while (index < size)
		{

			getline(file, temp, ','); student[index].No = atoi(temp);
			getline(file, temp, ','); student[index].Student_ID = temp;
			getline(file, temp, ','); student[index].Full_Name = temp;
			getline(file, temp, ','); student[index].Total_Mark = atod(temp);
			getline(file, temp, ','); student[index].Final_Mark = atod(temp);
			getline(file, temp, ','); student[index].Midterm_Mark = atod(temp);
			getline(file, temp, '\n'); student[index].Other_Mark = atod(temp);
			index++;
		}
		file.close();
	}
	// hien thi ra man hinh
	int Max_line = 7;
	int your_choice = 0;
	// ve khung
	Draw_Space_Rectangle(x, y - 2, x + 65, Max_line + 4);

	char c = 0;
	int page = 0;

	// hien thi ra trang dau tien
	SetColor(BG_Color, Text_Color);
	Show_Student_Result(student[0], x + 1, y + 1);
	ResetColor();
	for (int i = 1; i < Max_line && i < size;i++)
	{
		Show_Student_Result(student[i], x + 1, y + i + 1);
	}

	int arr[6]{ 5,16,34,42,50,58 };
	Draw_Table(x, y - 2, x + 65, Max_line + 4, arr, 6);

	int coor_X[7];
	int coor_Y[7];
	coor_X[0] = x + 1;
	coor_Y[0] = y - 1;
	for (int i = 1;i < 7;i++)
	{
		coor_X[i] = x + arr[i - 1] + 1;
		coor_Y[i] = y - 1;
	}
	string title[7]{ "STT", "Student ID", "    Full Name", " Total", " Final", "Midterm", " Other" };
	Write_Title(coor_X, coor_Y, title, 7);

	while (true)
	{
		c = _getch();
		if (c == -32) c = _getch();

		switch (c)
		{
		case 77: //left
		{
			page++;
			if (page * Max_line >= size)
			{
				page--;
				break;
			}
			your_choice = page * Max_line;
			break;
		}
		case 75: //right
		{
			page--;
			if (page < 0)
			{
				page++;
				break;
			}
			your_choice = page * Max_line;
			break;

		}
		case 72: //up
		{
			if (your_choice > Max_line * page)
			{
				your_choice--;
			}
			break;
		}
		case 80: //down
		{
			if (your_choice < Max_line * (page + 1) - 1 && your_choice < size - 1)
			{
				your_choice++;
			}
			break;
		}
		case 13: //Enter
		{
			Update_Student_Result(23 ,7, student, size, your_choice);
			Transition();
			Write_Title(coor_X, coor_Y, title, 7);
			break;
		}
		case 27: //Esc
		{
			// dua du lieu da sua vao file scoreboard
			string link_to_scoreboard = link_to_current_course + "\\Scoreboard.TXT";
			fstream Scoreboard_File(link_to_scoreboard, ios::out | ios::trunc);
			if (Scoreboard_File.is_open())
			{
				Scoreboard_File << "No,Student ID,Student Full Name,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
				for (int i = 0;i < size;i++)
				{
					Scoreboard_File << student[i].No << ",";
					Scoreboard_File << student[i].Student_ID << ",";
					Scoreboard_File << student[i].Full_Name << ",";
					Scoreboard_File << student[i].Total_Mark << ",";
					Scoreboard_File << student[i].Final_Mark << ",";
					Scoreboard_File << student[i].Midterm_Mark << ",";
					Scoreboard_File << student[i].Other_Mark << "\n";
				}
				Scoreboard_File.close();
			}
			// thoat
			return;
		}
		}
		Draw_Space_Rectangle(x, y, x + 65, Max_line + 4);
		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			if (i == your_choice - Max_line * page)
			{
				SetColor(BG_Color, Text_Color);
				Show_Student_Result(student[your_choice], x + 1, y + i + 1);
				ResetColor();
			}
			else
			{
				Show_Student_Result(student[i + Max_line * page], x + 1, y + i + 1);
			}
		}
		Draw_Table(x, y - 2, x + 65, Max_line + 4, arr, 6);
	}
}

void Update_Student_Result(int x, int y, Student_Result*& student, int size, int index)
{
	double Mark[4];
	Mark[0] = student[index].Total_Mark;
	Mark[1] = student[index].Final_Mark;
	Mark[2] = student[index].Midterm_Mark;
	Mark[3] = student[index].Other_Mark;

	//Ve khung
	Draw_Space_Rectangle(x, y, 40, 8);
	Draw_Border(x, y, 40, 8);
	//hien thi ra man hinh
	x++; y++;
	Write("ID: " + student[index].Student_ID, x, y);
	Write("Full Name: " + student[index].Full_Name, x, y + 1);
	Write("Total Mark: " + dtoa(student[index].Total_Mark), x, y + 2);
	Write("Final Mark: " + dtoa(student[index].Final_Mark), x, y + 3);
	Write("Midterm Mark: " + dtoa(student[index].Midterm_Mark), x, y + 4);
	Write("Other Mark: " + dtoa(student[index].Other_Mark), x, y + 5);

	int a[4]{12,12,14,12 };

	Gotoxy(int(x + a[0] + dtoa(Mark[0]).size()), y + 2);
	Show_Cursor(true);

	int choice = 0;
	while (true)
	{
		char c = _getch();
		if (c == -32) c = _getch();

		switch (c)
		{
			case 72: // up
			{
				if (choice > 0) choice--;
				break;
			}
			case 80: //down
			{
				if (choice < 4) choice++;
				break;
			}
			case 8: //backspace
			{
				// an du lieu cu
				Draw_Space_Rectangle(int(x + a[choice]), y + 2 + choice, (int)dtoa(Mark[choice]).size(), 1);
				Gotoxy(int(x + a[choice]), y + 2 + choice);
				//nhap du lieu moi
				string temp;
				getline(cin, temp);
				// cap nhat du lieu moi
				Mark[choice] = atod(temp);
				break;
			}
			case 13: //enter
			{
				// cap nhat du lieu va thoat
				student[index].Total_Mark = Mark[0];
				student[index].Final_Mark = Mark[1];
				student[index].Midterm_Mark = Mark[2];
				student[index].Other_Mark = Mark[3];
				Show_Cursor(false);
				return;
			}
		}
		Gotoxy(int(x + a[choice] + dtoa(Mark[choice]).size()), y + 2 + choice);
	}
}