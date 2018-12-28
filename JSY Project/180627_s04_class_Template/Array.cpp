#include "Array.h"

template<typename T>
Array<T>::Array(int size)
{
	maxsize = size;
	pData = new T[maxsize];
}

template<typename T>
Array<T>::~Array(void)
{
	delete[] pData;
}

template<typename T>
bool Array<T>::SetData(int pos, T data)
{
	if (pos < 0 || pos >= maxsize)
		return false;
	pData[pos] = data;
	return true;
}

template<typename T>
bool Array<T>::GetData(int pos, T &data)
{
	if (pos < 0 || pos >= maxsize)
		return false;
	data = pData[pos];
	return true;
}

