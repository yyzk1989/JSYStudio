
#include "Student_Data.h"

void main()
{
	srand(time(NULL));
	int select;
	while (1)
	{
		printf("\n///�ű�:1, ���:2, �˻���ȣ:3, �˻��̸�:4, ����:5, ����:6, �ε�:7, ����:99/// : ");
		scanf("%d", &select);

		system("cls");

		if (select == Finish)
		{
			break;
		}

		switch (select)
		{
		case Save:
			t_SaveData();
			break;
		case Load: 
			t_LoadData();
			break;
		case NewData:
			t_NewData();
			break;
		case PrintData:
			t_PrintData();
			break;
		case FindNumber:
			t_FindNumber();
			break;
		case FindData:
			t_FindName();
			break;
		case ModiData:
			t_ModiData();
			break;

		}

	}
	free(g_pStudent);
	_getch();
}