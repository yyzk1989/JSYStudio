# include"TStudent.h"

void main()
{
	TStudent a[3];
	TStudent d;
	a[0].SetSubject(rand() % 101, rand() % 101, rand() % 101);
	a[0].GetTotal();
	a[0].Show();

	// ¿Œµ¶ΩÃ
	std::cout << a[0][0] << " " << a[0][1] << " " << a[0][2];

	for (int i = 0; i < 3; i++)
	{
		d += a[0];
	}

	_getch();
}