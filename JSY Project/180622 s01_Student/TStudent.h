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
	TStudent operator + (TStudent & data);		// 연산자 재정의 
	TStudent& operator += (TStudent & data);	// 연산자 재정의 
	int operator ++(int value);					// 후위 연산 재정의
	int operator ++();							// 전위 연산 재정의
	//인덱싱 지원
	int operator[] (int index);
	void SetSubject(int kor, int eng, int mat);
	void Show();

	int GetTotal();
	
	
};

