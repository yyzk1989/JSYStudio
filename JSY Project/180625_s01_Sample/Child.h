#pragma once
#include "Parent.h"

class Child:public Parent
{
public :
	Child();
	~Child();
	void Humanity(void);	//�߰��� ��� �Լ�
	void Character(void);	//������ ��� �Լ�
	void Appearance(void);  //Ȯ��� ��� �Լ�
};


