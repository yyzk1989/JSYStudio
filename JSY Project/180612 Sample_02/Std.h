#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define test01

#define Data 200
#define PRI(x) printf("\n%s",x);

#define Start void main(){
#define Finish }


void P(const char * pBuffer)
{
	printf("%s\n", pBuffer);
}

void P(int pBuffer)
{
	printf("%d\n", pBuffer);
	printf("%d\n", Data);
}
