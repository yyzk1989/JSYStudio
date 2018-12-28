#include "LinkedList.h"

void LinkedList::AddList(Node* NextList, int insert)
{
	Node * NewList = new Node;
	NewList->pNext = NextList->pNext;
	NewList->value = insert;

}

LinkedList::LinkedList()
{
}


LinkedList::~LinkedList()
{
}
