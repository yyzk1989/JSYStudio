#include "TDepartment.h"
int main()
{
	//������ �����ϴ� CONTROL Ŭ����
	TDepartment department;
	
	char name[4] = {'K','I','M'};
	char sname[4] = { 'L','E','E' };
	char tname[4] = { 'H','A','N' };
	char fname[5] = { 'J','A','N','G' };
	
	//���� ���.	
	department.AddEmployee(new TPermanent(const_cast<char*>("KIM"), 1000));
	department.AddEmployee(new TPermanent(const_cast<char*>("LEE"), 1500));
	department.AddEmployee(new TTemporary(const_cast<char*>("HAN"), 10, 200));
	department.AddEmployee(new TTemporary(const_cast<char*>("JANG"), 12, 300));
	
	department.AddEmployee(new TPermanent(name, 1000));
	department.AddEmployee(new TPermanent(sname, 1500));
	department.AddEmployee(new TTemporary(tname, 10, 200));
	department.AddEmployee(new TTemporary(fname, 12, 300));
	//���������� �̹��޿� �����ؾ��� �޿���?
	department.ShowList();
	return 0;
}