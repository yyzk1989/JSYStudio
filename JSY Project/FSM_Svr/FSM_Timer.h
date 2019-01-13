#pragma once
#include "ServerStd.h"
#include <windows.h>
class FSM_Timer
{
public:
	DWORD m_dwFrameCount;
	DWORD m_dwFPS;
	DWORD m_dwBeforeTick;
	float m_fSecPerFrame;
	float m_fGameTimer;
	float m_fTimer;
		
public:
	bool	Init();
	bool	Frame();
public:
	FSM_Timer();
	virtual ~FSM_Timer();
};

