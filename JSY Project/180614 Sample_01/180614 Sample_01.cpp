#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct Student
{
	int Grade;
	int Class;
	int Number;

};

void main()
{

	struct Student student = {1,2,3};

	printf("Grade = %d\n", student.Grade);
	printf("Class = %d\n", student.Class);
	printf("Number = %d\n", student.Number);
	_getch();
}