#include"MyLib.h"

int main()
{
	Show_Cursor(FALSE);
	Change_Text_Size(40, 40);
	system("color 70");
	//Management();
	string link = "Data\\Staff_Member\\Ngocdang1234\\School_Year";
	int classes_or_courses; string current_school_year;
	Begining_Of_A_School_Year_Page(0, link,classes_or_courses, current_school_year);
	return 0;
}