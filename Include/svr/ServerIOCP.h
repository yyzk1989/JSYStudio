#pragma once

#include "WorkThread.h"
#include "User.h"
#define WORKDER_THREAD_COUNT 3

class ServerIOCP : public Singleton<ServerIOCP>, public ServerObj
{
private:
	friend class Singleton<ServerIOCP>;
public:
	HANDLE			m_hIOCP;
	WorkThread		m_WorkerThread[WORKDER_THREAD_COUNT];
public:
	bool			Init();
	bool			Release();
	void			AddHandleToIOCP(HANDLE hClientSocket, ULONG_PTR dwReturnKey);
public:
	ServerIOCP();
	~ServerIOCP();
};
#define I_ServerIOCP ServerIOCP::GetInstance()
