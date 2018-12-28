#pragma once
#include <iostream>
class Car
{
private:
	char * name;
	int ioil;
	int icurSpeed;

public:

	void Accel();
	void ShowCarState();
	void _Break();
	Car(char*name, int ioil, int DriveSpeed);
	~Car();
};

