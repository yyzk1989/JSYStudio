#pragma once

class Test_01
{
public:
	
	Test_01(void);
	Test_01(int x, int y);
	void Show(void);

	Test_01 operator++();
	Test_01 operator++(int);

	Test_01 operator+(Test_01 pt);

private:
	int x, y;

};


