#include <iostream>

using namespace std;
// #define TEST01
#define TEST02

#ifdef TEST01
template<typename T> void Swap(T &a, T &b);
/*
template<typename T>
void Swap(T &a, T &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
*/
int main()
{
	/*
	int a = 10;
	int b = 20;
	*/
	float a = 10;
	float b = 20;
	Swap(a, b);
	cout << "a = " << a << " " << "b = " << b;

	return 0;
}
template<typename T>
void Swap(T &a, T &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
#endif
#ifdef TEST02
template<typename T>
void Swap(T &a, T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int main()
{
	/*
	int a = 10;
	int b = 20;
	*/
	float a = 10;
	float b = 20;
	Swap(a, b);
	cout << "a = " << a << " " << "b = " << b;

	return 0;
}

#endif