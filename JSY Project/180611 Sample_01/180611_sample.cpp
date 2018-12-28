# include<stdio.h>
# include<stdlib.h>
# include<conio.h>

void main()
{

	printf("\n===========\n");
	int * pPoint = (int*)malloc(sizeof(int));
	*pPoint = 100;
	printf("%0x번지 : %d\n", pPoint + 0, *(pPoint + 0));
	free(pPoint);
	printf("\n===========\n");

	int * pPointArray = (int*)malloc(sizeof(int) * 10);
	for (int icnt = 0; icnt < 10; icnt++)
	{
		pPointArray[icnt] = icnt * 10;
		printf("\n0x%08x번지 : %d", pPointArray[icnt], *(pPointArray + icnt));
	}
	free(pPointArray);
	printf("\n===========\n");

	char * pCharPoint = 0;
	int iCount = 0;
	pCharPoint = (char *)malloc(sizeof(char) * 100);
	
	printf("값 입력 : ");
	do {
		pCharPoint[iCount++] = _getche();
	} while (pCharPoint[iCount - 1] != '\r');

	pCharPoint[iCount + 1] = 0;
	printf("\n0x%08x번지 : %s", pCharPoint, pCharPoint);
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		printf("\n0x%08X번지 : %c", pCharPoint + iCnt, *(pCharPoint + iCnt));
	}
	free(pCharPoint);
	printf("\n===========\n");

	int *lpPoint[10];
	for (int icnt = 0; icnt < 10; icnt++)
	{
		lpPoint[icnt] = (int*)malloc(sizeof(int));
		*lpPoint[icnt] = icnt * 10;
		printf("\n0x%08X번지 : %d", lpPoint + icnt, *lpPoint[icnt]);
	}
	for (int icnt = 0; icnt < 10; icnt++)
	{
		free(lpPoint[icnt]);
	}

	printf("\n===========\n");
	int iValue[3][2] = { { 10,20 },{ 30,40 },{ 50,60 } };
	for (int iCnt = 0; iCnt < 3; iCnt++)
	{
		printf("\n*(iValue+%d): %p", iCnt, *(iValue + iCnt));
		printf("\t\tiValue[%d]: %p", iCnt, iValue[iCnt]);
	}
	printf("\n");
	for (int iCnt = 0; iCnt < 3; iCnt++)
	{
		for (int jCnt = 0; jCnt < 2; jCnt++)
		{
			printf("\n*(*(iValue+%d)+%d)  : %d", iCnt, jCnt, *(*(iValue + iCnt) + jCnt));
			printf("\t\t *(iValue[%d]+%d) : %d", iCnt, jCnt, *(iValue[iCnt] + jCnt));
		}
	}
	printf("\n===========\n");;


	printf("\n=======  이중 포인터 =======\n");
	system("cls");

	int *pPtr;
	int **ppPtr;
	int num = 10;
	pPtr = &num;

	/*
		포인터의 메모리 주소는 일반 포인트에 저장 불가하며
		반드시 이중포인터에 저장해야 한다.
	*/
	ppPtr = &pPtr; //pPtr의 주소 저장
	printf("%d\n", **ppPtr);

	__int64**ppPoint = 0;
	ppPoint = (__int64**)malloc(sizeof(__int64) * 10);

	for (int icnt = 0; icnt < 10; icnt++)
	{
		ppPoint[icnt] = (__int64*)malloc(sizeof(__int64) * 10);
	}

	for (int icnt = 0; icnt < 10; icnt++)
	{
		for (int jcnt = 0; jcnt < 10; jcnt++)
		{
			ppPoint[icnt][jcnt] = icnt * 10 + jcnt;
		}
	}

	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		printf("\n");
		for (int jCnt = 0; jCnt < 10; jCnt++)
		{
			printf("[%d,%d]=%d", iCnt, jCnt, ppPoint[iCnt][jCnt]);
			printf("[%d,%d]=%d", iCnt, jCnt, *(ppPoint[iCnt] + jCnt));
		}
	}

	for (int icnt = 0; icnt < 10; icnt++)
	{
		free(ppPoint[icnt]);
	}

	free(ppPoint);

	printf("\n====== 포인터 배열=========\n");
	system("cls");

	char *pArray[6];

	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		pArray[iCnt] = (char*)malloc(sizeof(char) * 4);
	}

	for (int icnt = 0; icnt < 6; icnt++)
	{
		for (int jcnt = 0; jcnt < 3; jcnt++)
		{
			pArray[icnt][jcnt] = 65 + icnt * 3 + jcnt;
		}
		pArray[icnt][3] = 0;
	}
	
	for (int icnt = 0; icnt < 6; icnt++)
	{
		printf("\n");
		printf("[%d]= %s", icnt, pArray[icnt]);
	}

	for (int icnt = 0; icnt < 6; icnt++)
	{
		free(pArray[icnt]);
	}
	_getch();


}