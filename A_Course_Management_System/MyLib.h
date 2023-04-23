#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#include<conio.h>
#include<cstring>
#include<Windows.h> 
#define Default_BG_Color "white"
#define Default_Text_Color "black"
using namespace std;

//-------------------------Struct-----------------------------------------------------

struct Student
{
	int No;
	string Student_ID;
	string First_Name;
	string Last_Name;
	string Gender;
	string Date_Of_Birth;
	string Social_ID;
};
struct Course
{
	string ID;
	string Name;
	string Class;
	string Teacher;
	string Number_Of_Credits;
	string Maximum_Student; // default 50
	string Day_Of_Week;
	string Session;
};
//------------------------ConsoleFnction.cpp-----------------------------------------------------
void Show_Cursor(bool k);

void Gotoxy(short x, short y);

void SetColor(string BG_Color, string Text_Color);
void ResetColor();

void Change_Text_Size(int a, int b);

//------------------------SupportFunction.cpp------------------------------------------------------
void Write(string s, int x, int y, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

//   di chuyen con tro chon theo phuong thang dung
int Choice(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

//   ve khung
void Draw_Border(int x, int y, int a, int b, string BG_Color = Default_BG_Color, string Text_Color = Default_Text_Color);

void Draw_Space_Rectangle(int x, int y, int a, int b, string Color = Default_BG_Color);

bool Draw_Warning_Board(string Sentence, int x, int y, string Color = "red");

void Draw_Error_Board(string Error, int x, int y, string Color = "red");

void Transition(); 

bool Check_If_String_Is_Existed(string link, string s); // ktra xem 1 string co ton  tai trong 1 file hay khong
bool Check_If_String_Is_Existed(fstream& file, string s);
bool Check_If_String_Is_Existed(string* list, int cnt, string s);

void Sort_File(string link); // sap xep du lieu trong file theo chieu tang dan

void Copy_File(string link1, string link2); // copy du lieu tu link1 sang link2

int View_Board(string* s, int sizeOfs, int x, int y, string BG_Color, string Text_Color);

int atoi(string s);

string itoa(int num);

//------------------------Management.cpp------------------------------------------------------ 
int Management();

//------------------------LoginFunction.cpp------------------------------------------------------
int Main_Page(); // No.00

int SignIn_Page(string& username, string& userjob); //P.01

int SignUp_Page(string& username, string& userjob); //P.02

//-------------------------StaffMemberFunction.cpp-----------------------------------------------------
int School_Years_Page(string link, int& classes_or_courses, string& current_school_year); // P.04

void Create_New_School_Year(string link);

int Classes_Or_Semester();

int Classes_Page(string link, string Current_School_Year); //P.05.0

void Create_New_Class(string link_to_class);

int Add_Old_Class_Into_New_School_Year(string link, string current_school_year);

int Add_Or_View_Student();

void View_Student(string link_to_current_class);

int Read_Student_Info(fstream& file, Student& a);

void Show_student_Info(Student& student, int x, int y);

void Show_Students_in_a_Class(Student* student, int size, int x, int y);

void Add_a_Student(string link_to_current_class, int x, int y);

void Add_a_List_of_Student(string link_to_current_class, int x, int y);

int Semesters_Page(string link, string current_school_year); //P.05.1

void Create_New_Semester(string link_to_Semester);

void Courses_Page(string link_to_current_Semester);

void Create_New_Course(string link_to_current_Semester);

void Work_With_Course(string link_to_current_course);

void Update_Course_Info(string& link_to_course);

void Show_and_Delete_Students_in_a_Course(Student*& student, int& size, int x, int y, string BG_Color = "white", string Text_Color = "black");

void Delete_Student(Student*& student, int& cnt, int& index);

void Update_Student_List(string link_to_student_list, Student* student, int size); // Luu student list vao lai file

void Delete_Course(string link_to_current_course);
