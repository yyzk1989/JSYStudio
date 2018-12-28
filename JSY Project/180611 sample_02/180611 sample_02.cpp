#include <stdio.h>
#include <stdlib.h>
# include<conio.h>

void main()
{
		char* pCharPoint = 0;
		int iCount = 0;
		pCharPoint = (char*)malloc(sizeof(char) * 100);
		do
		{
			pCharPoint[iCount++] = _getche();
		} while (pCharPoint[iCount - 1] != '\r');

		pCharPoint[iCount + 1] = 0;
		printf("\n0x%08x번지 : %s", pCharPoint, pCharPoint);


		for (int iCnt = 0; iCnt < iCount; iCnt++)
		{
			printf("\n0x%08x번지 : %c", pCharPoint + iCnt, *(pCharPoint + iCnt));
		}
		free(pCharPoint);


		_getche();
	

	/*
	printf("\n=======  이중 포인터 =======\n");
	system("cls");

	int *pPtr;
	int **ppPtr;
	int num = 10;
	pPtr = &num;
	*/
	/*
	포인터의 메모리 주소는 일반 포인트에 저장 불가하며
	반드시 이중포인터에 저장해야 한다.
	*/
	/*
	ppPtr = &pPtr; //pPtr의 주소 저장
	printf("%d\n", **ppPtr);

	__int64**ppPoint = 0;
	ppPoint = (__int64**)malloc(sizeof(__int64) * 5);

	for (int icnt = 0; icnt < 5; icnt++)
	{
		ppPoint[icnt] = (__int64*)malloc(sizeof(__int64) * 10);
	}

	for (int icnt = 0; icnt < 5; icnt++)
	{
		for (int jcnt = 0; jcnt < 10; jcnt++)
		{
			ppPoint[icnt][jcnt] = icnt * 10 + jcnt;
		}
	}

	for (int iCnt = 0; iCnt < 5; iCnt++)
	{
		printf("\n");
		for (int jCnt = 0; jCnt < 10; jCnt++)
		{
			printf("[%d,%d]=%d", iCnt, jCnt, ppPoint[iCnt][jCnt]);
			printf("[%d,%d]=%d", iCnt, jCnt, *(ppPoint[iCnt] + jCnt));
		}
	}

	for (int icnt = 0; icnt < 5; icnt++)
	{
		free(ppPoint[icnt]);
	}

	free(ppPoint);
	_getch();
	*/
}