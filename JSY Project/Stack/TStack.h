#pragma once
#include <iostream>
stack int G_iMaxStack = 10;
class TStack
{
	
public:
	int	m_iStackArray[G_iMaxStack];
	int m_iTop;

	int Push(int iData);
	int Pop();
	int Show();


	TStack();
	~TStack();
};

