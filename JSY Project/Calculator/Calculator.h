#pragma once
#include <iostream>
using namespace std;
class Calculator
{
private:
	int AddCnt=0, MinCnt=0, MulCnt=0, DiveCnt=0;

public:
	float Add(float D1, float D2);
	float Dive(float D1, float D2);
	float Min(float D1, float D2);
	float Mul(float D1, float D2);
	void ShowOpCal();

	Calculator();
	~Calculator();
};

