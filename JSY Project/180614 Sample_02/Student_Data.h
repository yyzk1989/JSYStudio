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
	�ű�:1,���:2,�˻���ȣ:3,�˻��̸�:4,����:5, ����:6,�ε�:7,
	����(99)");
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
// �ű�
void t_NewData();
// ��� 
void t_PrintData();
// �˻���ȣ
void t_FindNumber();
// �˻��̸�
void t_FindName();
// ����
void t_ModiData();
// ����
void t_SaveData();
// ����
void t_LoadData();

void t_NewData( )
{
	printf("���� ����� �л� �� �ο����� �Է��Ͻÿ� : ");
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
		printf("�����Ͱ� �����ϴ�. �����͸� Ȯ�����ּ���");
	}
	system("cls");
	printf("\n=====================================================");
	printf("\n====================�����������α׷�=================");
	printf("\n=====================================================");
	printf("\n��ȣ\t�̸�\t����\t����\t����\t����\t���");
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
	printf("�˻��� ��ȣ�� �Է��ϼ��� : ");
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
	printf("�˻��� �̸��� �Է��ϼ��� : ");
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
	printf("������ ������ ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &Serch_Num);

	printf("\n%3d %8s %7d %7d %7d %7d %10.4f \n",
		g_pStudent[Serch_Num].m_iIndex,
		g_pStudent[Serch_Num].m_strName,
		g_pStudent[Serch_Num].m_iKor,
		g_pStudent[Serch_Num].m_iEng,
		g_pStudent[Serch_Num].m_iMat,
		g_pStudent[Serch_Num].m_iTotal,
		g_pStudent[Serch_Num].m_fAver);

	printf("���� : ");
	scanf("%d", &g_pStudent[Serch_Num].m_iKor);
	printf("���� : ");
	scanf("%d", &g_pStudent[Serch_Num].m_iEng);
	printf("���� : ");
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
	printf("������ �Ϸ� �Ǿ����ϴ�. \n");
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

	printf("\n�ε尡 �Ϸ� �Ǿ����ϴ�. \n");
	fclose(fp);

}