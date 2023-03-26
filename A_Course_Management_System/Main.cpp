#include"MyLib.h"
int main()
{
	Invisible_Cursor(FALSE);
	Change_Text_Size(40, 40);
	system("color 70");
	
	SignIn_Page();
	Gotoxy(50, 20);
	system("pause");
	return 0;
}