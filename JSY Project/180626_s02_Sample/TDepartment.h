#pragma once
#include "TPermanet.h"
#include "TTemporary.h"

class TDepartment
{
private:
	TEmployee * empList[10];
	int index;
public:
	TDepartment() : index(0) { };
	void AddEmployee(TEmployee* emp);
	void ShowList(); // �޿� ����Ʈ ���.
};

