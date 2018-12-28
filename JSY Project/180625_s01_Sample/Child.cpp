#include "Child.h"



Child::Child()
{
}


Child::~Child()
{
}
void Child::Humanity(void)
{
	cout << "넘치는 인간미" << endl;
}

void Child::Character(void)
{
	cout << "불 같은 성품" << endl;
}

void Child::Appearance(void)
{
	Parent::Appearance();			//기반 클래스에서 정의한 기능
	cout << "훤칠한 키" << endl;		//파생 클래스에서 확장된 기능
}