#include "Thread.h"

unsigned int WINAPI Thread::HandleRunner(LPVOID parameter)
{
	Thread* pThread = (Thread*)parameter;
	if (pThread)	pThread->Run();
	return 0;
}
bool Thread::Run()
{
	return true;
}
void Thread::CreateThread()
{
	if (m_bStarted == true) return;
	m_hThread = _beginthreadex(NULL, 0,
		HandleRunner, // 시작함수
		(LPVOID)this, // 인자값
		0,
		&m_iThreadID);
	m_bStarted = true;
}


Thread::Thread()
{
	m_bStarted = false;
}


Thread::~Thread()
{
	CloseHandle((HANDLE)m_hThread);
}
