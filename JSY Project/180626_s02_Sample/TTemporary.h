#pragma once
#include "TEmployee.h"
class TTemporary : public TEmployee
{
private:
	int time; //���ѽð�
	int pay; //�ð��� �޿�.
public:
	TTemporary(char* _name, int _time, int _pay);
	int GetPay();
};

