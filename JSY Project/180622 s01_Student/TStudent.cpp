#include "TStudent.h"

int TStudent ::operator[] (int index)
{
	if (index > 3) return-1;
	if (index == 0) return m_iKor;
	if (index == 1) return m_iEng;
	if (index == 2) return m_iMat;
	if (index == 3) return m_iTotal;

}


TStudent& TStudent::operator+= (TStudent & data)
{
	TStudent ret;

	m_iKor += data.m_iKor;
	m_iEng += data.m_iEng;
	m_iMat += data.m_iMat;

	return *this;

}

TStudent TStudent::operator+ (TStudent & data)
{
	TStudent ret;

	ret.SetSubject(m_iKor + data.m_iKor, m_iEng + data.m_iEng, m_iMat+ data.m_iMat);

	return ret;

}

void TStudent::Show()
{
	std::cout	<< "국어" << m_iKor
				<< "영어" << m_iEng
				<< "수학" << m_iMat
				<< "총점" << m_iTotal << std::endl;

}

void TStudent::SetSubject(int kor, int eng, int mat)
{
	m_iKor = kor;
	m_iEng = eng;
	m_iMat = mat;
}

int TStudent::GetTotal()
{
	return m_iTotal = m_iKor + m_iEng + m_iMat;
}

