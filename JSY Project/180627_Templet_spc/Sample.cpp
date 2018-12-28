#include <iostream>
using namespace std;

template <typename T>
int DataSize(T data)
{
	return sizeof(data);
}

template<>// char * 형은 아래 함수로 받아 들여라
int DataSize(char * data)
{
	return strlen(data);
}

int main(void)
{
	int num = 0;
	double real = 0.0;
	const char * str = "Good morning!";
	cout << DataSize(num) << endl;
	cout << DataSize(real) << endl;
	cout << DataSize(str) << endl;
}
/* 특화된 함수 정의 방법
1.
template<>
int DataSize<char*> (char *data)
{
	return strlen(data);
}
2.
template<>
int DataSize<>(char *data)
{
return strlen(data);
}
3.
template<>
int DataSize(char *data)
{
return strlen(data);
}

*/
