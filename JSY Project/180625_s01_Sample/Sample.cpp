#include "Child.h"
#include <conio.h>
int main(void)
{
	Child aBoy;
	Parent aFather;
	aBoy.Character();			//Parent���� ��� ���� �Լ� ȣ��
	aBoy.Appearance();		//Parent���� ��� ���� �Լ� ȣ��
	aBoy.Wealth();			//Parent���� ��� ���� �Լ� ȣ��
	aBoy.Humanity();			//Child���� ��� ���� �Լ� ȣ��

	aFather.Appearance();
	aFather.Character();
	_getch();
	return 0;
}