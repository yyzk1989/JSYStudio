#pragma once
class LinkedList
{
private:
	struct Node
	{
		int value;
		Node * pNext;
	};
	Node* head = new Node;

public:

	void AddList( int insert);
	void DelList();
	LinkedList();
	~LinkedList();
};

