#include "Parent.h"

Parent::Parent()
{
	money = 10000000;
}

Parent::~Parent()
{
}

void Parent::Character(void)
{
	cout << "������ ��ǰ" << endl;
}

void Parent::Appearance(void)
{
	cout << "�߻��� �ܸ�" << endl;
}

void Parent::Wealth(void)
{
	cout << "��� : " << money << "��" << endl;
}
