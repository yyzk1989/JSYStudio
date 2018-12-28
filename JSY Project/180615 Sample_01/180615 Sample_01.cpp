#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
//#define _CRT_SECURE_NO_WARNINGS
#define Project


#ifdef Project
void DrawText()
{
	FILE* fp = fopen("180615 Sample_01.cpp", "r");
	char buffer[255] = { 0, };
	
	while (1)
	{
		if (feof(fp))
		{
			break;
		}
		fgets(buffer, sizeof(char) * 255, fp);
		printf("\n%s", buffer);
	}

	fclose(fp);
}

void DrawBuffer()
{
	FILE* freadp = fopen("180615 Sample_01.cpp", "r");
	FILE* fwritep = fopen("cpy.cpp", "w");
	fseek(freadp, 0, SEEK_END);
	int iTotalsize = ftell(freadp);
	// char* buffer = (char*)calloc(iTotalsize, sizeof(int));
	char* buffer = (char*)malloc(iTotalsize* sizeof(int));
	memset(buffer, 0, sizeof(char) * iTotalsize);

	// fseek 커서 위치 설정
	fseek(freadp, 0, SEEK_SET);
	fread(buffer, 1 , sizeof(char)* iTotalsize, freadp);
	fwrite(buffer, 1, sizeof(char)* iTotalsize, fwritep);

	fclose(freadp);
	fclose(fwritep);

}


void main()
{

	// DrawText();
	DrawBuffer();
	_getch();
}

#else
void main()
{
	FILE *fp = NULL;
	fp = fopen("demo.txt", "w");
	fprintf(fp, "%d %s", 100, "KGCA");
	
	fclose(fp);

	FILE *fStream = NULL;
	fStream = fopen("demo.txt", "r");
	int iValue;
	char cbuffer[5] = { 0, };
	fscanf(fStream, "%d %s", &iValue, cbuffer);
	printf("%d %s", iValue, cbuffer);
	fclose(fStream);
	

	_getch();
}


#endif