#pragma once
template <typename T>
class Array
{
public:
	Array(int size = 100);
	~Array(void);
	bool SetData(int pos, T data);
	bool GetData(int pos, T &data);

private:
	T * pData;
	int maxsize;

};

