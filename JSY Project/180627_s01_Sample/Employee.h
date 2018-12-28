#pragma once
class Employee
{
public:
	Employee(const char* _name, int _jobLev, int _saltype);
	~Employee();

	char* GetName();
	const char* GetJobLev();
	const char* GetSalType();


private:
	char * Name;
	int JobLev;
	int saltype;
};

