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
	cout << "차분한 성품" << endl;
}

void Parent::Appearance(void)
{
	cout << "잘생긴 외모" << endl;
}

void Parent::Wealth(void)
{
	cout << "재산 : " << money << "원" << endl;
}
