#include "TDepartment.h"
void TDepartment::AddEmployee(TEmployee* emp)
{
	empList[index++] = emp;
}
void TDepartment::ShowList() // �޿� ����Ʈ ���.
{
	for (int i = 0; i<index; i++)
	{
		cout << "name: " << empList[i]->GetName() << endl;
		cout << "salary: " << empList[i]->GetPay() << endl;
		cout << endl;
	}
}
