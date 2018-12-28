#include "TFigure.h"


void Move(int x, int y)
{
	m_ix += x;
	m_iy += y;
}
void Resize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}
void Draw()
{
}


TFigure::TFigure()
{
}


TFigure::~TFigure()
{
}
