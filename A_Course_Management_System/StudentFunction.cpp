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
		int your_choice = Choice(list, cnt + 1, 25, 2, "white", "blue");
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
			int your_choice = Choice(list, cnt + 1, 25, 2, "white", "blue");
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
	Transition();

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
	string* list_of_course_student_studies = new string[number_of_course];
	int number_of_course_student_studies = 0;

	for (int i = 0;i < number_of_course; i++)
	{
		//duyet cac hoc sinh trong khoa hoc

		if (Check_If_Student_Is_In_This_Course(link + "\\" + list_of_course[i], student_id))
		{
			list_of_course_student_studies[number_of_course_student_studies] = list_of_course[i]; // luu khoa hoc ma hoc sinh hoc
			number_of_course_student_studies++;
		}
	}
	// chuyen ID thanh Ten cua cac khoa hoc
	for (int i = 0;i < number_of_course_student_studies;i++)
	{
		string link_to_course_info = link + "\\" + list_of_course_student_studies[i] + "\\Information.TXT";
		fstream file_to_course_info(link_to_course_info, ios::in);
		if (file_to_course_info.is_open())
		{
			getline(file_to_course_info, list_of_course_student_studies[i]);
			getline(file_to_course_info, list_of_course_student_studies[i]);
			file_to_course_info.close();
		}
	}

	if (number_of_course_student_studies == 0)
	{
		Draw_Error_Board("No course has been created yet", 27, 7);
	}
	else
	{
		Choice(list_of_course_student_studies, number_of_course_student_studies, 25, 3, "white", "black");
	}

	delete[] list_of_course;
	delete[] list_of_course_student_studies;
	return;
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