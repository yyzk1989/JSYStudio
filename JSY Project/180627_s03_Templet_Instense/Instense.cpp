#include <iostream>
using namespace std;

template<typename T>
void Swap(T &a, T & b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int main()
{
	int a = 1, b = 2;
	Swap(a, b);
	cout << a << ", " << b << endl;
	double c = 0.1, d = 0.2;

	Swap(c, d);
	cout << c << ", " << d << endl;


	return 0;
}