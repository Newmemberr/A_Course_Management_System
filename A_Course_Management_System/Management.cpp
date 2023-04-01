#include"MyLib.h"
int Management()
{
	List History;
	Create_List(History);
	int num_Page = 0;
	string username;
	string userjob;
	string link;
	string current_school_year;
	int classes_or_semester = 0;
	while (true)
	{
		Push(History, num_Page);
		switch (History.Node_Head->Data)
		{
			case -2:
			{
				return 0;
			}
			case -1:
			{
				Pop(History); 
				Pop(History);
				num_Page = History.Node_Head->Data;
				Pop(History);
				break;
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
						num_Page = -1;
						break;
					}
				}
				
			}
		}
	}
}