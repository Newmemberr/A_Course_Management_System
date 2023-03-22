#include"MyLib.h"
int main()
{
	Invisible_Cursor();
	Pair ans;
	while (true)
	{
		ans = Show_Mouse_Pos();
		if (ans.y == 0 && ans.x>=0 && ans.x<6)
		{
			SetColor("black", "blue");
		}
		else
		{
			ResetColor();
		}
		Gotoxy(0, 0);
		cout << "Hello";
	}
	return 0;
}