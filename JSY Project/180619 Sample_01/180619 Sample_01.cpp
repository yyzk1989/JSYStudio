#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<memory.h>
#define _CRT_SECURE_NO_WARNINGS
//#define SAMPLE01
//#define SAMPLE02
#define SAMPLE03


#ifdef SAMPLE01

void main()
{
	time_t now = time(NULL);

	struct tm *lt = localtime(&now);

	printf("������ %d�� %d�� %d�� �Դϴ�. \n",
		lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday);

	printf("����ð��� %d�� %d�� �Դϴ�. \n",
		lt->tm_hour+1, lt->tm_min+1);

	_getch();
}

#endif
#ifdef SAMPLE02

void main()
{
	time_t now = time(NULL);
	time_t worldcup;

	struct tm worldcupDay = { 0,0,0,15,5,118,0,0,0 };
	double diff;
	worldcup = mktime(&worldcupDay);
	diff = difftime(worldcup, now);
	// diff = difftime(now, worldcup);

	printf("2018�� �����ű��� ������ %d�� ���ҽ��ϴ�. \n",
		(int)diff / 60 / 60 / 24);

	_getch();
}
#endif
#ifdef SAMPLE03
void main()
{
	struct tm *today, theday;
	time_t now = time(NULL);
	today = localtime(&now);
	memcpy(&theday, today, sizeof(theday));

	theday.tm_mday += 20;
	mktime(&theday);

	printf("������ %d�� %d�� %d�� �Դϴ�.\n",
			today->tm_year+1900, today->tm_mon+1, today->tm_mday);

	
	printf("20�� ���Ŀ��� %d�� %d�� %d�� �Դϴ�.\n", 
		theday.tm_year+1900, theday.tm_mon+1, theday.tm_mday);

	_getch();
}
#endif
