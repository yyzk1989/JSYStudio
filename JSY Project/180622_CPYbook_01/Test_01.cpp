#pragma once
#include "Test_01.h"
#include <iostream>

using namespace std;

Test_01::Test_01(void)
{
	x = y = 0;
}

Test_01::Test_01(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Test_01::Show(void)
{
	cout << "(" << x << "," << y << ")" << endl;
}

Test_01 Test_01::operator++(void)	// 전위형
{
	++x, ++y;
	return *this;
}

Test_01 Test_01::operator++(int)	// 후위형
{
	Test_01 temp = *this;
	++x, ++y;
	return temp;
}

Test_01 Test_01::operator+(Test_01 pt)
{
	Test_01 temp;
	temp.x = x + pt.x;
	temp.y = y + pt.y;
	
	return temp;
}
