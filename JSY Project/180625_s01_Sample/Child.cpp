#include "Child.h"



Child::Child()
{
}


Child::~Child()
{
}
void Child::Humanity(void)
{
	cout << "��ġ�� �ΰ���" << endl;
}

void Child::Character(void)
{
	cout << "�� ���� ��ǰ" << endl;
}

void Child::Appearance(void)
{
	Parent::Appearance();			//��� Ŭ�������� ������ ���
	cout << "��ĥ�� Ű" << endl;		//�Ļ� Ŭ�������� Ȯ��� ���
}