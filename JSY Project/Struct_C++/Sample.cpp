#include <iostream>
#include <conio.h>
#include "Point.h"

void main()
{
	Point p1, p2;

	p1.SetPosition(10, 10);
	p2.SetPosition(30, 30);
	p1.Move(10, 10);
	p1.Show();

	p2.Move(10, 10);
	p2.Show();
	_getch();
}

void Point::SetPosition(int i, int j)
{
	x = i;
	y = j;
}

void Point::Move(int i, int j)
{
	x += i;
	y += j;
}
void Point::Show()
{
	std::cout << x << "   " << y << std::endl;
}
