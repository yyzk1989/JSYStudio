#include "Test_01.h"
#include <iostream>
#include <conio.h>
int main(void)
{
	Test_01 p1(0, 0), p2, p3;
	p2 = ++p1;	// ������. operator++() ȣ��
	p1.Show();
	p2.Show();

	p3 = p1++;	// ������. operator++(int) ȣ��
	p1.Show();
	p3.Show();

	//////////////////////////////////////////
	//���� ������ ȣ��
	Test_01 T1(10, 20), T2(5, 7), T3;

	T3 = T1 + T2;
	T3.Show();

	_getch();

	return 0;
}