#pragma once
#include "Thread.h"
class WorkThread : public Thread
{
public:
	HANDLE		m_hIOCP;
	bool		Run();
	void		Set(HANDLE hIOCP) {
		m_hIOCP = hIOCP;
	};
public:
	WorkThread();
	virtual ~WorkThread();
};

