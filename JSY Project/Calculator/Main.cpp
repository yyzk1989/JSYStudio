#include "Calculator.h"

void main()
{
	Calculator cal;
	
	cout << "3.2 + 3.4 = " << cal.Add(3.2, 3.4) << endl;
	cout << "10.0 / 3.4 = " << cal.Dive(10.0, 3.4) << endl;
	cout << "3.2 - 3.4 = " << cal.Min(3.2, 3.4) << endl;
	cout << "3.2 * 3.4 = " << cal.Mul(3.2, 3.4) << endl;
	cal.ShowOpCal();
	
	return;
}