#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


void HanoiTower(int n, char from, char temp, char to)
{
	if (n == 1)
	{
		printf("%d", n);
	}
	else
	{
		HanoiTower(n - 1, from, temp, to);
		printf("%d", n, from, to);
		HanoiTower(n - 1, from, temp, to);
	}

}

int Factorial(int iData)
{
	if (iData == 1)
	{
		return 1;
	}
	else
	{
		int iReturn = Factorial(iData - 1);
		return iData * iReturn;
	}

	return 0;
}

void main()
{
	int n = 3;
	HanoiTower(n, 'A', 'B', 'C');

	_getch();
}