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
	const char *  title[] = { "사원", "대리", "과장","부장", "임원" };
	return title[JobLev];
}
const char* Employee::GetSalType()
{
	const char * PayType[] = { "시급제","월급제","연봉제" };
	return PayType [saltype];
}


Employee::~Employee()
{
}
