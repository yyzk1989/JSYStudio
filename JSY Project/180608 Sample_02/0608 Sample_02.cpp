#include <stdio.h>
#include <stdlib.h>

void main()
{

	int **pArray = 0;
	pArray = (int**)malloc(sizeof(int) * 5);
	for (int i = 0; i < 3; i++)
	{
		pArray[i] = (int*)malloc(sizeof(int) * 5);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pArray[i][j] = i*10+j;
		}
	}

	getchar();
	free(pArray);


}