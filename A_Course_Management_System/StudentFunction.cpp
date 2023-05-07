#include"MyLib.h"
int View_School_Year(string link)
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
			View_Semester(link + "\\" + list[your_choice] + "\\Semester");
			Transition();
		}
	}

	delete[] list;
	return 6;
}

void View_Semester(string link)
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
				//View_Course(link + "\\" + list[your_choice]);
				Transition();
			}
		}
		delete[] list;
	}
}
