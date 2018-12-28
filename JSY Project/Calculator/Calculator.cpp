#include "Calculator.h"



float Calculator::Add(float D1, float D2)
{
	AddCnt++;
	return D1+D2;
}

float Calculator::Dive(float D1, float D2)
{
	DiveCnt++;
	return D1 /D2;
}

float Calculator::Min(float D1, float D2)
{
	MinCnt++;
	return D1- D2;
}

float Calculator::Mul(float D1, float D2)
{
	MulCnt++;
	return D1 * D2;
}

void Calculator::ShowOpCal()
{
	cout << "ADD : " << AddCnt << " Min : " << MinCnt << " Mul : " << MulCnt << " Dive : " << DiveCnt;

}

Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}
