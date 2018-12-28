#pragma once

#include "Thread.h"
#include "Packet.h"

class Acceptor :  public Thread
{
public:
	SOCKET		m_ListenSock;
public:
	bool  Run();
	bool  Release();
	bool  Set(int iPort, const char* strAddress = 0);
	virtual void	AddUser(SOCKET socket, SOCKADDR_IN address);
public:
	Acceptor();
	virtual ~Acceptor();
};

