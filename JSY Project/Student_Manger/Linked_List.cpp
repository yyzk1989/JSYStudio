#include "Linked_List.h"
#include "Main.h"

void Linked_List::AddList(char* _Name, int _Kor, int _Eng, int _Math)
{
	
	Node * NewList = new Node;
	Node * Temp = Head;
	//scanf()
	strcpy(NewList->Name, _Name);
	NewList->Kor = _Kor;
	NewList->Eng = _Eng;
	NewList->Math = _Math;
	NewList->Total = NewList->Kor + NewList->Eng + NewList->Math;
	NewList->Aver = NewList->Total / 3;
	NewList->Next = NULL;

	while (Temp->Next != NULL)
	{
		Temp = Temp->Next;
	}

	Temp->Next = NewList;
}

void Linked_List::DelList(char* Name)
{
	Node * remove = Head;
	Node * Temp = Head;
	if (remove->Next == NULL)
	{
		cout << "�����Ͱ� ��� �ֽ��ϴ� Ȯ���� �ּ���" << endl;
		return;
	}
	while (remove->Next != NULL)
	{
		remove = remove->Next;
		if (!strcmp(remove->Name, Name))
		{
			break;
		}
		Temp = Temp->Next;
	}
	Temp->Next = remove->Next;
	delete remove;
	this->g_cnt--;

}

void Linked_List::ShowList()
{
	Node * Temp = Head;
	if (Temp->Next == NULL)
	{
		cout << "�����Ͱ� ��� �ֽ��ϴ� Ȯ���� �ּ���" << endl;
		return;
	}
	printf("�̸� \t ���� \t	���� \t ���� \t ���� \t ��� \n");
	while (Temp->Next != NULL)
	{
		Temp = Temp->Next;
		
		printf("%s \t %d \t	%d \t %d \t %d \t %10.4f \n", Temp->Name, Temp->Kor, Temp->Eng, Temp->Math, Temp->Total, Temp->Aver);		
	}

}

Linked_List::Linked_List()
{
	Head = new Node;
	Head->Next = NULL;
	g_cnt = 0;
}


