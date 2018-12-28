#include "Employee.h"
#include <stdlib.h>
#include <string.h>

Employee::Employee(const char* _name, int _jobLev, int _saltype)
{
	this->Name = (char*)malloc(strlen(_name));
	strcpy(Name, _name);
	this->JobLev = _jobLev;
	this->saltype = _saltype;
}
char* Employee::GetName()
{
	return this->Name;
}
const char* Employee::GetJobLev()
{
	const char *  title[] = { "���", "�븮", "����","����", "�ӿ�" };
	return title[JobLev];
}
const char* Employee::GetSalType()
{
	const char * PayType[] = { "�ñ���","������","������" };
	return PayType [saltype];
}


Employee::~Employee()
{
}
