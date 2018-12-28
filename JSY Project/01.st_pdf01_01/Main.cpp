
#include "Car.h"

int main(void)
{
	//Car run99(name, 100, 0);
	Car run99(const_cast<char*>("run99"), 100, 0 );

	for (int i = 0; i < 3; i++)
	{
		run99.Accel();
	}
	run99.ShowCarState();
	run99._Break();
	run99.ShowCarState();

	return 0;


}