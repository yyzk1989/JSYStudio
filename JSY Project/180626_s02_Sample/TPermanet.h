#pragma once
#include "TEmployee.h"
class TPermanent : public TEmployee
{
private:
	int salary;  // �⺻�޿�
public:
	int GetPay();
public:
	TPermanent(char* _name, int sal);
	~TPermanent();
};

