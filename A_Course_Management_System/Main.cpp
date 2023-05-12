#include"MyLib.h"

int main()
{
	Create_Data();
	Set_Full_Screen();
	Show_Cursor(FALSE);
	Change_Text_Size(40, 40);
	system("color 70");
	Management();
	return 0;
}