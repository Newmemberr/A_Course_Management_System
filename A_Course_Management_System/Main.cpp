#include"MyLib.h"
int main()
{
	Invisible_Cursor();
	Change_Text_Size(40, 40);
	system("color 70");
	
	int k=Main_Page();
	Gotoxy(0, 0);
	cout << k;
	
	return 0;
}