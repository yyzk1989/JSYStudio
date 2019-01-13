#include "FSM_Timer.h"


float g_fSecPerFrame = 0.0f;
bool	FSM_Timer::Init()
{
	m_dwBeforeTick = timeGetTime(); // 1/1000
	return true;
}
bool	FSM_Timer::Frame()
{ 	 
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = dwElapseTick / 1000.0f;
	g_fSecPerFrame = m_fSecPerFrame;
	m_fGameTimer += m_fSecPerFrame;

	m_fTimer += m_fSecPerFrame;
	if (m_fTimer >= 1.0f)
	{
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fTimer -= 1.0f;
		printf(	"FPS:%d TIME:%10.4f SPF:%10.4f\n", m_dwFPS, m_fGameTimer, m_fSecPerFrame);
	}
	m_dwFrameCount++;

	m_dwBeforeTick = dwCurrentTick;
	return true;
}


FSM_Timer::FSM_Timer()
{

}


FSM_Timer::~FSM_Timer()
{
}
