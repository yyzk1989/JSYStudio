#pragma once
#include "Main.h"
#include "Linked_List.h"
class FileClas : public Linked_List
{	
public:
	//int SaveFile(int cnt);
	void SaveFile(Linked_List );
	int LoadFile(Linked_List);

	FileClas();
	~FileClas();
};

