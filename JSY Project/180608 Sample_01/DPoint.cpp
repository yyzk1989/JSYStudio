#include <stdio.h>

void main()
{
	int array[3][3] =
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
	};

	printf("%d___%d___%d",**array,*(*(array)+1), **array+1);

	getchar();
	

	
}