#include "Car.h"

void Car::Accel()
{
	icurSpeed += 50;
}

void Car::_Break()
{
	icurSpeed -= 50;
}

void Car::ShowCarState()
{
	std::cout << "�� �̸� : " << this->name << std::endl;
	std::cout << "���� �ӵ� : " << this->icurSpeed << std::endl;
}

Car::Car(char*name, int ioil, int DriveSpeed)
{
	this->name = name;
	this->ioil = ioil;
	this->icurSpeed = DriveSpeed;
}


Car::~Car()
{
}
