#pragma once

#include "Synchronize.h"

class Thread : public ServerObj
{
public:
	unsigned int   m_hThread;
	unsigned int   m_iThreadID;
	bool		   m_bStarted;
public:
	void	CreateThread();
	virtual bool Run();
	static unsigned int WINAPI HandleRunner(LPVOID parameter);
public:
	Thread();
	virtual ~Thread();
};

