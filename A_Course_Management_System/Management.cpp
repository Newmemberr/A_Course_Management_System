#include"MyLib.h"
int Management()
{
	int k = 0;
	string username;
	string userjob;
	string link;
	string current_school_year;
	int classes_or_courses;
	while (true)
	{
		switch (k)
		{
			case -1:
			{
				return 0;
			}
			case 0:
			{
				k = Main_Page();
				break;
			}
			case 1:
			{
				k = SignIn_Page(k, username, userjob);
				link = "Data\\" + userjob + "\\" + username + "\\School_Year";
				break;
			}
			case 2:
			{
				k = SignUp_Page(k, username, userjob);
				link = "Data\\" + userjob + "\\" + username + "\\School_Year";
				break;
			}
			case 3:
			{
				k = Begining_Of_A_School_Year_Page(k, link, classes_or_courses, current_school_year);
				break;
			}
		}
	}
}