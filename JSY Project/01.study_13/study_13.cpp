#include<stdio.h>
void func(void);

void main()
{
	int count;
	for (count = 0; count < 10; count++)
	{
		printf("At iteration 5d : ", count);
		func();
	}

	getchar();

}

void func(void)
{
	static int x = 0;
	int y = 0;
	printf("x = %d, y = %d\n", x++, y++);

}
