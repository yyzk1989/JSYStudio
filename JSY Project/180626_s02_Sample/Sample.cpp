#include "TDepartment.h"
int main()
{
	//직원을 관리하는 CONTROL 클래스
	TDepartment department;
	
	char name[4] = {'K','I','M'};
	char sname[4] = { 'L','E','E' };
	char tname[4] = { 'H','A','N' };
	char fname[5] = { 'J','A','N','G' };
	
	//직원 등록.	
	department.AddEmployee(new TPermanent(const_cast<char*>("KIM"), 1000));
	department.AddEmployee(new TPermanent(const_cast<char*>("LEE"), 1500));
	department.AddEmployee(new TTemporary(const_cast<char*>("HAN"), 10, 200));
	department.AddEmployee(new TTemporary(const_cast<char*>("JANG"), 12, 300));
	
	department.AddEmployee(new TPermanent(name, 1000));
	department.AddEmployee(new TPermanent(sname, 1500));
	department.AddEmployee(new TTemporary(tname, 10, 200));
	department.AddEmployee(new TTemporary(fname, 12, 300));
	//최종적으로 이번달에 지불해야할 급여는?
	department.ShowList();
	return 0;
}