#include "FileClas.h"



void FileClas::SaveFile(Linked_List StudManger)
{
	FILE * fp = fopen("StdManager.txt", "w");
	Node* ftemp = StudManger.Head;
	fprintf(fp, "%d\n", StudManger.g_cnt);

	for (int i = 0; i < StudManger.g_cnt; i++)
	{
		ftemp = ftemp->Next;
		fprintf(fp, "%s %d %d %d %d %f\n", ftemp->Name, ftemp->Kor, ftemp->Eng, ftemp->Math, ftemp->Total, ftemp->Aver);

	}
	printf("저장이 완료되었습니다\n");
	fclose(fp);

}

int FileClas::LoadFile(Linked_List StudManger)
{
	FILE * fp = fopen("StdManager.txt", "r");
	Node* ftemp = StudManger.Head;
	int count;
	char filechar[4];
	int f_kor,f_Eng,f_Mat,f_Tot;
	float f_Aver;

	fscanf(fp, "%d\n", &count);


	for (int i = 0; i < count; i++)
	{
	
		fscanf(fp, "%s %d %d %d %d %f\n", filechar, &f_kor, &f_Eng, &f_Mat, &f_Tot, &f_Aver);
		StudManger.AddList(filechar, f_kor, f_Eng, f_Mat);
		ftemp = ftemp->Next;
	}
	printf("\n로드가 완료 되었습니다. \n");
	fclose(fp);
	return count;
}

FileClas::FileClas()
{
}


FileClas::~FileClas()
{
}
