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

	printf("오늘은 %d년 %d월 %d일 입니다. \n",
		lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday);

	printf("현재시각은 %d시 %d분 입니다. \n",
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

	printf("2018년 월드컵까지 앞으로 %d일 남았습니다. \n",
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

	printf("오늘은 %d년 %d월 %d일 입니다.\n",
			today->tm_year+1900, today->tm_mon+1, today->tm_mday);

	
	printf("20일 이후에는 %d년 %d월 %d일 입니다.\n", 
		theday.tm_year+1900, theday.tm_mon+1, theday.tm_mday);

	_getch();
}
#endif
