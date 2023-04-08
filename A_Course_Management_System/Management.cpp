#include"MyLib.h"
int Management()
{
	int num_Page = 0;
	string username;
	string userjob;
	string link;
	string current_school_year;
	int classes_or_semester = 0;
	while (true)
	{
		switch (num_Page)
		{
			case -1:
			{
				return 0;
			}
			case 0:
			{
				num_Page = Main_Page();
				break;
			}
			case 1:
			{

				num_Page = SignIn_Page(username, userjob);
				link = "Data\\" + userjob + "\\" + username + "\\School_Year";
				break;
			}
			case 2:
			{
				num_Page = SignUp_Page(username, userjob);
				link = "Data\\" + userjob + "\\" + username + "\\School_Year";
				break;
			}
			case 3:
			{
				system("pause");
				break;
				//student
			}
			case 4:
			{
				//staff member
				num_Page = School_Years_Page(link, classes_or_semester, current_school_year);
				break;
			}
			case 5:
			{
				//staff member
				bool go_back = false;
				string Class_Name;
				int k = classes_or_semester;
				while (true)
				{
					switch (k)
					{
						case 0:
						{
							//classes
							k = Classes_Page(k, link, current_school_year, Class_Name);
							break;
						}
						case 1:
						{
							//semester
							break;
						}

					}
					if (k == -1)
					{
						num_Page = 4;
						break;
					}
				}
				
			}
		}
	}
}