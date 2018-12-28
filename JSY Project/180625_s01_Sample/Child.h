#pragma once
#include "Parent.h"

class Child:public Parent
{
public :
	Child();
	~Child();
	void Humanity(void);	//추가된 멤버 함수
	void Character(void);	//수정된 멤버 함수
	void Appearance(void);  //확장된 멤버 함수
};


