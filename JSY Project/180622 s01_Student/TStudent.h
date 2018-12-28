#pragma once
#include <iostream>
#include <conio.h>

class TStudent
{

private:
	int m_iKor;			//0
	int m_iEng;			//1
	int m_iMat;			//2
	int m_iTotal;		//3

public:
	TStudent operator + (TStudent & data);		// ������ ������ 
	TStudent& operator += (TStudent & data);	// ������ ������ 
	int operator ++(int value);					// ���� ���� ������
	int operator ++();							// ���� ���� ������
	//�ε��� ����
	int operator[] (int index);
	void SetSubject(int kor, int eng, int mat);
	void Show();

	int GetTotal();
	
	
};

