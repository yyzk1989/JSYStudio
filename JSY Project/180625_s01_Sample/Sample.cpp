#include "Child.h"
#include <conio.h>
int main(void)
{
	Child aBoy;
	Parent aFather;
	aBoy.Character();			//Parent에서 상속 받은 함수 호출
	aBoy.Appearance();		//Parent에서 상속 받은 함수 호출
	aBoy.Wealth();			//Parent에서 상속 받은 함수 호출
	aBoy.Humanity();			//Child에서 상속 받은 함수 호출

	aFather.Appearance();
	aFather.Character();
	_getch();
	return 0;
}