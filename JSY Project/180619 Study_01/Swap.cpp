#include<stdio.h>
#include<conio.h>

void swap(int *pa, int *pb)
{
	int temp=0;

	temp = *pa;
	*pa = *pb;
	*pb = temp;

}

void main()
{
	int a = 3;
	int b = 4;

	printf("before\t a = %d b = %d\n", a, b);
	swap(&a, &b);

	printf("after\t a = %d b = %d", a, b);

	_getch();

}