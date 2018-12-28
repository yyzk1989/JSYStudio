#pragma once

class Linked_List
{
protected:
	struct Node
	{
		char Name[4];
		int Kor;
		int Eng;
		int Math;
		int Total;
		float Aver;
		Node * Next;
	};

	
public:
	Node * Head;
	int g_cnt;
	void AddList(char* Name, int Kor, int Eng, int Math );
	void DelList(char* Name);
	void ShowList();

	Linked_List();

};

