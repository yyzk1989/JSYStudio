#include <stdio.h>

void main()
{
	int cnt,temp;
	int i = 0;
	int j;

	// cnt = getchar();
	cnt = 5;
	temp = cnt -1 ;
	for (i = cnt; 0<i; i--)
	{
		j = temp--;
		for (; j < cnt; j++)
		{
			printf("*");
		}
		printf("\n");
	}

	getchar();

}