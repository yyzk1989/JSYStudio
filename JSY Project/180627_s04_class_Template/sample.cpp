#include<iostream>
#include"Array.cpp"
using namespace std;

int main(void)
{
	Array <double>data(10);
	int i;
	double val;
	for (i = 0; i < 10; i++)
	{
		if (!data.SetData(i, i / 10.0))
			cout << "Fail to set data" << endl;
		if (!data.GetData(i, val))
			cout << "Fail to get data" << endl;
		else
			cout << "Data = " << val << endl;
	}
	return 0;
}