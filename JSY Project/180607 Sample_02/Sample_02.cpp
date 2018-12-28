#include <stdio.h>

void main()
{
	int cnt =11;
	int curfinal = 0;
	int starfinal = 0;
	int dia;
	int curser = 0;
	int star_cur = 0;
	int temp = 0;

	curfinal = temp = cnt / 2;
	
	
	for (int i = 0; i <= curfinal; i++)
	{
		curser = i;
		starfinal = i;
		for (; curser <= curfinal; curser++)
		{
			printf("-");
		}

		for (star_cur = 0; star_cur < (starfinal*2)+1; star_cur++)
		{
			printf("*");
		}		
		
		printf("\n");

	}
	
	for (int i = 0; i < curfinal; i++)
	{
		curser = temp+i;
		starfinal = temp-i;

		for (; curser >= curfinal-1; curser--)
		{
			printf("-");
		}

		for (star_cur = 2; star_cur<(starfinal * 2) + 1; star_cur++)
		{
			printf("*");
		}

		printf("\n");

	}


	getchar();


}