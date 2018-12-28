#include "Test_01.h"
#include <iostream>
#include <conio.h>
int main(void)
{
	Test_01 p1(0, 0), p2, p3;
	p2 = ++p1;	// 전위형. operator++() 호출
	p1.Show();
	p2.Show();

	p3 = p1++;	// 후위형. operator++(int) 호출
	p1.Show();
	p3.Show();

	//////////////////////////////////////////
	//이항 연산자 호출
	Test_01 T1(10, 20), T2(5, 7), T3;

	T3 = T1 + T2;
	T3.Show();

	_getch();

	return 0;
}