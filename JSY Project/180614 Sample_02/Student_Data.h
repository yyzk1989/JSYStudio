#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

enum button
{
	/*
	신규:1,출력:2,검색번호:3,검색이름:4,수정:5, 저장:6,로드:7,
	종료(99)");
	*/
	
	NewData = 1,
	PrintData,
	FindNumber,
	FindData,
	ModiData,
	Save,
	Load,
	Finish = 99
};

typedef struct StudentData
{
	char	m_strName[4];
	int		m_iIndex;
	int		m_iKor;
	int		m_iEng;
	int		m_iMat;
	int		m_iTotal;
	float	m_fAver;
}Student;

Student *g_pStudent = 0;
int g_iTotalNumber = 0;
// 신규
void t_NewData();
// 출력 
void t_PrintData();
// 검색번호
void t_FindNumber();
// 검색이름
void t_FindName();
// 수정
void t_ModiData();
// 저장
void t_SaveData();
// 삭제
void t_LoadData();

void t_NewData( )
{
	printf("새로 등록할 학생 총 인원수를 입력하시오 : ");
	scanf("%d", &g_iTotalNumber);
	
	if (g_pStudent != NULL)
	{
		free(g_pStudent);
		g_pStudent = 0;
	}
	if(g_pStudent == NULL)
	{
		g_pStudent = (Student*)malloc(sizeof(Student)* g_iTotalNumber);
	}

	for (int i = 0; i < g_iTotalNumber; i++)
	{
		g_pStudent[i].m_strName[0] = 65 + rand() % 26;
		g_pStudent[i].m_strName[1] = 65 + rand() % 26;
		g_pStudent[i].m_strName[2] = 65 + rand() % 26;
		g_pStudent[i].m_strName[3] = '\0';

		g_pStudent[i].m_iIndex = i;

		g_pStudent[i].m_iKor = rand() % 101;
		g_pStudent[i].m_iEng = rand() % 101;
		g_pStudent[i].m_iMat = rand() % 101;

		g_pStudent[i].m_iTotal = g_pStudent[i].m_iKor +
			g_pStudent[i].m_iEng +
			g_pStudent[i].m_iMat;
		g_pStudent[i].m_fAver = g_pStudent[i].m_iTotal / 3.0f;
	}
}


void t_PrintData()
{
	if (g_pStudent == 0)
	{
		printf("데이터가 없습니다. 데이터를 확인해주세요");
	}
	system("cls");
	printf("\n=====================================================");
	printf("\n====================성적관리프로그램=================");
	printf("\n=====================================================");
	printf("\n번호\t이름\t국어\t영어\t수학\t총점\t평균");
	printf("\n-----------------------------------------------------");
	for (int i = 0; i < g_iTotalNumber; i++)
	{
		printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
			g_pStudent[i].m_iIndex,
			g_pStudent[i].m_strName,
			g_pStudent[i].m_iKor,
			g_pStudent[i].m_iEng,
			g_pStudent[i].m_iMat,
			g_pStudent[i].m_iTotal,
			g_pStudent[i].m_fAver);
	}
}

void t_FindNumber()
{
	int Serch_Num;
	printf("검색할 번호를 입력하세요 : ");
	scanf("%d", &Serch_Num);

	system("cls");
	printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
		g_pStudent[Serch_Num].m_iIndex,
		g_pStudent[Serch_Num].m_strName,
		g_pStudent[Serch_Num].m_iKor,
		g_pStudent[Serch_Num].m_iEng,
		g_pStudent[Serch_Num].m_iMat,
		g_pStudent[Serch_Num].m_iTotal,
		g_pStudent[Serch_Num].m_fAver);
}

void t_FindName()
{
	char Serch_sName[4] = {0,};
	int  Desert_num = 0;
	printf("검색할 이름을 입력하세요 : ");
	scanf("%s", &Serch_sName);
	system("cls");
	for (int i = 0; i < g_iTotalNumber; i++)
	{
		if (!_stricmp(Serch_sName, g_pStudent[i].m_strName))
		{
			break;
		}
		Desert_num++;
	}
	printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
		g_pStudent[Desert_num].m_iIndex,
		g_pStudent[Desert_num].m_strName,
		g_pStudent[Desert_num].m_iKor,
		g_pStudent[Desert_num].m_iEng,
		g_pStudent[Desert_num].m_iMat,
		g_pStudent[Desert_num].m_iTotal,
		g_pStudent[Desert_num].m_fAver);

}

void t_ModiData()
{
	int Serch_Num;
	system("cls");
	printf("점수를 수정할 번호를 입력하세요 : ");
	scanf("%d", &Serch_Num);

	printf("\n%3d %8s %7d %7d %7d %7d %10.4f \n",
		g_pStudent[Serch_Num].m_iIndex,
		g_pStudent[Serch_Num].m_strName,
		g_pStudent[Serch_Num].m_iKor,
		g_pStudent[Serch_Num].m_iEng,
		g_pStudent[Serch_Num].m_iMat,
		g_pStudent[Serch_Num].m_iTotal,
		g_pStudent[Serch_Num].m_fAver);

	printf("국어 : ");
	scanf("%d", &g_pStudent[Serch_Num].m_iKor);
	printf("영어 : ");
	scanf("%d", &g_pStudent[Serch_Num].m_iEng);
	printf("수학 : ");
	scanf("%d", &g_pStudent[Serch_Num].m_iMat);
}

void t_SaveData()
{
	FILE * fp = fopen("Data.txt", "w");

	fprintf(fp, "%d", g_iTotalNumber);
	for (int i = 0; i < g_iTotalNumber; i++)
	{
		fprintf(fp,"\n%d %s %d %d %d %d %f",
			g_pStudent[i].m_iIndex,
			g_pStudent[i].m_strName,
			g_pStudent[i].m_iKor,
			g_pStudent[i].m_iEng,
			g_pStudent[i].m_iMat,
			g_pStudent[i].m_iTotal,
			g_pStudent[i].m_fAver);
	}
	system("cls");
	printf("저장이 완료 되었습니다. \n");
	fclose(fp);

}

void t_LoadData()
{
	FILE * fp = fopen("Data.txt", "r");

	if (g_pStudent == NULL)
	{
		g_pStudent = (Student*)malloc(sizeof(Student)* g_iTotalNumber);
	}
	
	fscanf(fp, "%d", &g_iTotalNumber);

	for (int i = 0; i < g_iTotalNumber; i++)
	{
		fscanf(fp, "\n%d %s %d %d %d %d %f",
			&g_pStudent[i].m_iIndex,
			g_pStudent[i].m_strName,
			&g_pStudent[i].m_iKor,
			&g_pStudent[i].m_iEng,
			&g_pStudent[i].m_iMat,
			&g_pStudent[i].m_iTotal,
			&g_pStudent[i].m_fAver);
	}
	t_PrintData();

	printf("\n로드가 완료 되었습니다. \n");
	fclose(fp);

}