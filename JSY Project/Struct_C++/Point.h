#pragma once

class Point
{
private:
	int x;
	int y;
public:
	void SetPosition(int i, int j);
	void Move(int i, int j);
	void Show();
};