#include "TStack.h"

int TStack::Push(int iData)
{
	if (m_iTop == G_iMaxStack - 1)
	{
		std::cout << "Stack Overflow" << std::endl;
	}


	m_iStackArray[m_iTop++] = iData;
	return iData;
}

TStack::TStack()
{
}


TStack::~TStack()
{
}
