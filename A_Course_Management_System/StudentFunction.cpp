#include"MyLib.h"
int View_School_Year(string link, string student_id)
{
	Transition();

	string link_to_school_year_list = link + "\\School_Year_List.TXT";
	int cnt = Number_of_Line(link_to_school_year_list);

	string* list = new string[cnt + 1];

	fstream file_to_school_year_list(link_to_school_year_list, ios::in);
	if (file_to_school_year_list.is_open())
	{
		for (int i = 0; i < cnt + 1 && getline(file_to_school_year_list, list[i]);i++);

		file_to_school_year_list.close();
	}
	list[cnt] = "Go back";

	while (true)
	{
		int your_choice = Choice(list, cnt + 1, 25, 4, "white", "blue");
		if (your_choice == cnt) break;
		else
		{
			View_Semester(link + "\\" + list[your_choice] + "\\Semester", student_id);
			Transition();
		}
	}

	delete[] list;
	return 6;
}

void View_Semester(string link, string student_id)
{
	Transition();

	int cnt = 0;

	string link_to_semester_list = link + "\\Semesters_List.TXT";
	fstream file_to_semester_list(link_to_semester_list, ios::in);
	if (file_to_semester_list.is_open())
	{
		file_to_semester_list >> cnt;
		file_to_semester_list.close();
	}

	if (cnt == 0)
	{
		Draw_Error_Board("No semesters have been created yet",27 ,7);
		return;
	}
	else
	{
		string* list = new string[cnt + 1];
		for (int i = 0;i < cnt; i++)
		{
			list[i] = "Semester_" + itoa(i + 1);
		}
		list[cnt] = "Go back";
		while (true)
		{
			int your_choice = Choice(list, cnt + 1, 25, 4, "white", "blue");
			if (your_choice == cnt)
			{
				break;
			}
			else
			{
				View_Course(link + "\\" + list[your_choice], student_id);
				Transition();
			}
		}
		delete[] list;
	}
}

void View_Course(string link, string student_id)
{

	string link_to_course_list = link + "\\Courses_List.TXT";
	int number_of_course = Number_of_Line(link_to_course_list);
	string* list_of_course = new string[number_of_course];

	// luu toan bo cac khoa hoc trong hoc ky
	fstream file_to_course_list(link_to_course_list, ios::in);
	if (file_to_course_list.is_open())
	{
		for (int i = 0;i < number_of_course; i++)
		{
			getline(file_to_course_list, list_of_course[i]);
		}
		file_to_course_list.close();
	}
	// duyet cac khoa hoc
	string* list_of_course_student_studies_ID = new string[number_of_course];
	string* list_of_course_student_studies_Name = new string[number_of_course];
	int number_of_course_student_studies = 0;

	for (int i = 0;i < number_of_course; i++)
	{
		//duyet cac hoc sinh trong khoa hoc

		if (Check_If_Student_Is_In_This_Course(link + "\\" + list_of_course[i], student_id))
		{
			list_of_course_student_studies_ID[number_of_course_student_studies] = list_of_course[i]; // luu khoa hoc ma hoc sinh hoc
			number_of_course_student_studies++;
		}
	}
	// chuyen ID thanh Ten cua cac khoa hoc
	for (int i = 0;i < number_of_course_student_studies;i++)
	{
		string link_to_course_info = link + "\\" + list_of_course_student_studies_ID[i] + "\\Information.TXT";
		fstream file_to_course_info(link_to_course_info, ios::in);
		if (file_to_course_info.is_open())
		{
			getline(file_to_course_info, list_of_course_student_studies_Name[i]);
			getline(file_to_course_info, list_of_course_student_studies_Name[i]);
			file_to_course_info.close();
		}
	}

	if (number_of_course_student_studies == 0)
	{
		Draw_Error_Board("You don't have any course in this semester", 27, 7);
	}
	else
	{
		int k = View_Course_List_or_View_Scoredboard();
		if (k == 0) View_List_Of_Course(list_of_course_student_studies_Name, number_of_course_student_studies, 25, 3);
		else if (k == 1) View_Scoreboard(link , list_of_course_student_studies_ID, list_of_course_student_studies_Name, student_id, number_of_course_student_studies, 4, 3);
	}

	delete[] list_of_course;
	delete[] list_of_course_student_studies_Name;
	delete[] list_of_course_student_studies_ID;
	return;
}

int View_Course_List_or_View_Scoredboard()
{
	int x = 27, y = 5;
	string s1[2]{ "View list of courses", "View scoreboard" };

	Draw_Space_Rectangle(x, y, 25, 4);
	Draw_Border(x, y, 25, 4);

	x++; y++;
	return Choice(s1, 2, x, y, "white", "blue");
}

void View_Scoreboard(string link, string* id_course, string* name_course, string student_id, int size, int x, int y)
{
	Transition();
	if (size == 0)
	{
		Draw_Error_Board("No Data", 25, 7);
		return;
	}
	//Ve bang
	Draw_Space_Rectangle(x, y, x + 59, size + 3);
	int arr[4]{ 14,25,36,49 };
	Draw_Table(x, y - 2, x + 59, size + 3, arr, 4);

	int coor_X[5];
	int coor_Y[5];
	coor_X[0] = x + 1;
	coor_Y[0] = y - 1;
	for (int i = 1;i < 5;i++)
	{
		coor_X[i] = x + arr[i - 1] + 1;
		coor_Y[i] = y - 1;
	}

	string title[5]{ "Course's Name", "Total Mark", "Final Mark", "Midterm Mark", " Other Mark"};
	Write_Title(coor_X, coor_Y, title, 5);

	x++; y++;
	// duyet tung khoa hoc
	for (int i = 0;i < size; i++)
	{
		string link_to_scoreboard = link + "\\" + id_course[i] + "\\Scoreboard.TXT";
		string temp;
		fstream file_to_scoreboard(link_to_scoreboard, ios::in);
		if (file_to_scoreboard.is_open())
		{
			while (file_to_scoreboard.eof() == false)
			{
				getline(file_to_scoreboard, temp, ','); // bo qua du lieu khong can thiet
				getline(file_to_scoreboard, temp, ',');
				if (temp == student_id)
				{
					Write(name_course[i], x + (arr[0] - (int)name_course[i].size()) / 2, y + i); // ten khoa hoc

					getline(file_to_scoreboard, temp, ',');  // bo qua du lieu khong can thiet
					for (int j = 0;j < 4;j++)
					{
						getline(file_to_scoreboard, temp, ','); // lay total mark, final mark, midterm mark, other mark
						Write(temp, x + arr[j] + 4, y + i);
					}
				}
				else
				{
					getline(file_to_scoreboard, temp); // bo qua du lieu khong can thiet
				}
			}
			
			file_to_scoreboard.close();
		}
	}
	while (true)
	{
		char k = _getch();
		if (k == 27) return;
	}
}

bool Check_If_Student_Is_In_This_Course(string link, string student_id)
{
	string link_to_student_list = link + "\\Students_List.TXT";
	fstream file(link_to_student_list, ios::in);

	int number_of_student = Number_of_Line(link_to_student_list) - 1;
	if (file.is_open())
	{
		string temp;
		getline(file, temp); // bo dong dau tien
		for (int i = 0; i < number_of_student;i++)
		{
			getline(file, temp, ','); // bo qua du lieu khong can thiet
			getline(file, temp, ',');
			if (temp == student_id) return true;
			else
			{
				getline(file, temp); // bo qua du lieu khong can thiet
			}
		}
		file.close();
	}
	return false;
}

void View_List_Of_Course(string* list, int size, int x, int y)
{
	Transition();
	int Max_line = 7;

	Draw_Space_Rectangle(x, y, 20, Max_line + 2);

	char c = 0;
	int page = 0;
	for (int i = 0; i < Max_line && i < size;i++)
	{
		Write("-" + list[i], x + 1, y + i + 1);
	}

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

			Draw_Space_Rectangle(x, y, 20, Max_line + 2);
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

			Draw_Space_Rectangle(x, y, 20, Max_line + 2);
			break;

		}
		case 27: //Esc
		{
			return;
		}
		}

		for (int i = 0; i < Max_line && i + Max_line * page < size; i++)
		{
			Write("-" + list[i + Max_line * page], x + 1, y + i + 1);
		}

	}

}