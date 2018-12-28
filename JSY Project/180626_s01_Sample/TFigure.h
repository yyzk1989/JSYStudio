#pragma once
#include <iostream>
class TFigure
{
protected:
	int m_ix;
	int m_iy;
	int m_iWidth;
	int m_iHeight;
public:
	void Move(int x, int y);
	void Resize(int w, int h);
	void Draw();
public:
	TFigure();
	virtual ~TFigure();
};

