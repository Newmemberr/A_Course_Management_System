#include"MyLib.h"
//tao thu muc Data
void Create_Data()
{
	string s = "Data";
	const char* my_dir = s.c_str();
	struct stat info;
	if (stat(my_dir, &info) == 0 && (info.st_mode & S_IFDIR) != 0) {
		// Da ton tai cac file can thiet
		return;
	}
	else {
		// chua ton tai cac file can thiet
		// tao cac file can thiet
		system("MD Data\\Student");
		system("MD Data\\Staff_Member");
		system("MD Data\\School_Year");
	}
}


//------------------------------------------------------------------------------
// Viet chu tai vi tri (x,y)
void Write(string s, int x, int y, string BG_Color, string Text_Color)
{
	Gotoxy(x, y);
	SetColor(BG_Color, Text_Color);
	cout << s;
	ResetColor();
	return;
}

//version 1
int Choice1(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	// 175 16 ,272
	string Mark = ">> ";
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << Mark << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < sizeOfs;i++)
	{
		Gotoxy(x, y + i); cout << Mark << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case 72: 
		{
			if (your_choice > 0)
			{
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 80: 
		{
			if (your_choice < sizeOfs - 1)
			{
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 13:
			ResetColor();
			return your_choice;
		}
	}
	ResetColor();
}
// version 2
int Choice(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	// 175 16 ,272
	string Mark = ">> ";
	int Exit_Number = -1;
	int Max_Line = 7;
	int Current_Page = 0;
	int Max_Page = (sizeOfs - 1) / Max_Line;
	int your_choice = 0;

	int Max_SizeOfSentence = 0;
	for (int i = 0;i < sizeOfs;i++)
	{
		if (s[i] == "Go back") Exit_Number = i;
		if (Max_SizeOfSentence < s[i].size()) Max_SizeOfSentence = (int)s[i].size(); // tim do dai lon nhat cua cac string trong s
	}
	Max_SizeOfSentence += (int)Mark.size();

	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << Mark << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < sizeOfs && i < Max_Line;i++)
	{
		Gotoxy(x, y + i); cout << Mark << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case 72: // up
		{
			if (your_choice > Current_Page * Max_Line)
			{
				Write(Mark + s[your_choice], x, y + your_choice - Max_Line * Current_Page, BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(Mark + s[your_choice], x, y + your_choice - Max_Line * Current_Page, BG_Color_1, Text_Color_1);
			}
			else if (Current_Page > 0)
			{
				Draw_Space_Rectangle(x, y, Max_SizeOfSentence, Max_Line); // xoa nhung lua chon cu

				your_choice -= 1;

				//dua ra nhung lua chon moi
				SetColor(BG_Color_1, Text_Color_1);
				Gotoxy(x, y + Max_Line - 1); cout << Mark << s[Max_Line * Current_Page - 1];

				Current_Page -= 1;
				SetColor(BG_Color_2, Text_Color_2);
				for (int i = 0;i + Max_Line * Current_Page < sizeOfs && i < Max_Line - 1;i++)
				{
					Gotoxy(x, y + i); cout << Mark << s[i + Max_Line * Current_Page];
				}
			}
			break;
		}
		case 80: //down
		{
			if (your_choice < sizeOfs - 1 && your_choice < (Current_Page + 1) * Max_Line - 1)
			{
				Write(Mark + s[your_choice], x, y + your_choice - Max_Line * Current_Page, BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(Mark + s[your_choice], x, y + your_choice - Max_Line * Current_Page, BG_Color_1, Text_Color_1);
			}
			else if (your_choice < sizeOfs - 1 && Current_Page < Max_Page)
			{
				Draw_Space_Rectangle(x, y, Max_SizeOfSentence, Max_Line); // xoa nhung lua chon cu

				your_choice += 1;

				Current_Page += 1;

				//dua ra nhung lua chon moi
				SetColor(BG_Color_1, Text_Color_1);
				Gotoxy(x, y); cout << Mark << s[Max_Line * Current_Page];

				SetColor(BG_Color_2, Text_Color_2);
				for (int i = 1;i + your_choice < sizeOfs && i < Max_Line;i++)
				{
					Gotoxy(x, y + i); cout << Mark << s[i + Max_Line * Current_Page];
				}
			}
			break;
		}
		case 27: //Esc
		{
			if (Exit_Number != -1) return Exit_Number;
			else break;
		}
		case 13: // Enter
		{
			ResetColor();
			return your_choice;
		}
		}
	}
	ResetColor();
}

void Draw_Border(int x, int y, int a, int b, string BG_Color, string Text_Color)
{
	// Ve khung bat dau tu (x,y) co chieu ngang a don vi, chieu doc b don vi
	SetColor(BG_Color, Text_Color);
	a--;
	b--;
	Gotoxy(x, y); cout << char(201);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y); cout << char(205);
	}
	Gotoxy(x+a, y); cout << char(187);
	for (int i = 1; i < b; i++)
	{
		Gotoxy(x, y + i); cout << char(186);
		Gotoxy(x+a, y + i); cout << char(186);
	}
	Gotoxy(x, y+b); cout << char(200);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y+b); cout << char(205);
	}
	Gotoxy(x+a, y+b); cout << char(188);
	ResetColor();
}

void Draw_Space_Rectangle(int x, int y, int a, int b, string Color)
{
	SetColor(Color, Color);
	for (int i = 0;i < b;i++)
	{
		Gotoxy(x, y+i);
		for (int j = 0;j < a;j++)
		{
			cout << " ";
		}
	}
	ResetColor();
}

bool Draw_Warning_Board(string Sentence, int x, int y, string Color)
{
	Sentence += " (Y/N)";
	int a = (int)Sentence.size();
	a += 2;
	int b = 4;

	Draw_Space_Rectangle(x, y, a, b);
	Draw_Border(x, y, a, b);
	Write(Sentence, x + 1, y + 1, "white", Color);
	while (true)
	{
		char c = _getch();
		if (toupper(c) == 'Y') return true;
		else if (toupper(c) == 'N') return false;
	}
}

void Draw_Error_Board(string Error, int x, int y, string Color)
{
	int a = (int)Error.size();
	if (a < 25) a = 25;
	a += 2;
	int b = 4;

	Draw_Space_Rectangle(x, y, a, b);
	Draw_Border(x, y, a, b);
	Write(Error, x + 1, y + 1, "white", Color);
	Write("Press any key to continue", x + 1, y + 2, "white", Color);
	_getch();
}

void Transition() 
{
	Draw_Border(0, 0, 71, 19, Default_BG_Color, Default_Text_Color);
	Draw_Space_Rectangle(1, 1, 69, 17,"white");
}

bool Check_If_String_Is_Existed(string link, string s)
{
	fstream file(link, ios::in);
	if (file.is_open())
	{
		string temp;
		while (getline(file, temp))
		{
			if (temp == s)
			{
				file.close();
				return true;
			}
		}
		file.close();
	}
	return false;
}

bool Check_If_String_Is_Existed(fstream& file, string s)
{
	string temp;
	while (getline(file, temp))
	{
		if (temp == s)
		{
			file.close();
			return true;
		}
	}
	return false;
}
bool Check_If_String_Is_Existed(string* list, int cnt, string s)
{
	string temp;
	for (int i = 0;i < cnt;i++)
	{
		if (list[i] == s)
			return true;
	}
	return false;
}

void Sort_File(string link)
{
	
	string temp;
	int cnt = Number_of_Line(link);//dem so luong dong

	fstream file(link, ios::in);
	string* list = new string[cnt];
	for (int i = 0; i<cnt;i++) // dua du lieu tu file -> list
	{
		getline(file, list[i]);
	}
	for (int i = 0;i < cnt;i++) // sap xep tang dan
	{
		for (int j = i + 1;j < cnt;j++)
		{
			if (strcmp(list[i].c_str(), list[j].c_str()) > 0)
			{
				temp = list[i]; list[i] = list[j]; list[j] = temp;
			}
		}
	}
	file.close();
	file.open(link, ios::out, ios::trunc);
	for (int i = 0;i < cnt;i++)
	{
		file << (list[i] + '\n');
	}
	file.close();
	delete[] list;
	return;
}

void Copy_File(string link1, string link2) 
{
	fstream file1(link1, ios::in);
	if (!file1.is_open()) return;
	fstream file2(link2, ios::out);
	if (!file2.is_open()) return;
	string temp;
	while (getline(file1, temp))
	{
		file2 << temp << endl;
	}
	file1.close();
	file2.close();
}

int Number_of_Line(string link)
{
	// dem so hoc sinh hien tai
	int cnt = 0;
	fstream file(link, ios::in);
	if (file.is_open())
	{
		string temp;
		while (getline(file, temp))
		{
			cnt++;                          // dem so luong hoc sinh
		}
		file.close();
	}
	return cnt;
}

int View_Board(string* s, int sizeOfs, int x, int y, string BG_Color, string Text_Color)
{
	char c = 0;
	int page = 0;
	for (int i = 0; i < 7 && i < sizeOfs;i++)
	{
		Write(s[i + page], x, y + i + page);
	}

	while (true)
	{
		c = _getch();
		if (c == -32)c = _getch();
		
		switch (c)
		{
			case 1:
			{
				page++;
				if (page * 7 >= sizeOfs) page--;

				for (int i = 0; i < 7 && i < sizeOfs;i++)
				{
					Write(s[i + page], x, y + i + page);
				}
				break;
			}

		}

	}

}

int atoi(string s)
{
	while (s[0] == '0') s.erase(s.begin(), s.begin() + 1);
	int ans = 0;
	for (int i = 0;i < s.size();i++)
	{
		ans *= 10;
		ans += int(s[i]) - 48;
	}
	return ans;
}
string itoa(int num)
{
	string ans;
	while (num > 0)
	{
		ans = char(num % 10 + 48) + ans;
		num /= 10;
	}
	return ans;
}
double atod(string s)
{
	while (s[0] == '0') s.erase(s.begin(), s.begin() + 1);
	double ans = 0;
	int index = 0;
	for (;index < s.size() && s[index] != '.';index++)
	{
		ans *= 10;
		ans += int(s[index]) - 48;
	}
	index++;
	double a = 0;
	int size = 0;
	for (;index < s.size();index++)
	{
		a *= 10;
		size++;
		a += int(s[index]) - 48;
	}
	for (int i = 0;i < size;i++)
		a /= 10;
	ans += a;
	return ans;
}
string dtoa(double num)
{
	num *= 1000;
	int size = 3;
	while ((int)num % 10 == 0) 
	{
		num /= 10;
		size--;
	}
	int a1 = (int)num % (int)pow(10, size);
	int a2 = (int)num / (int)pow(10, size);
	string ans;
	if (size == 0)
	{
		ans = itoa(a2) + ".000";
	}
	else
	{
		ans = itoa(a2) + "." + itoa(a1);
	}
		
	return ans;
}
