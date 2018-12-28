#pragma once

#include "StreamPacket.h"
#include "Thread.h"
#include "Acceptor.h"
#include "User.h"

class Server : public Thread
{
public:
	Acceptor   m_Acceptor;
public:
	bool Init();
	bool Release();
	bool Run();
	virtual bool AddUser(SOCKET socket, SOCKADDR_IN address);
	bool SendMsg(SOCKET socket,	char* msg, WORD code);
	bool SendMsg(SOCKET socket, const char* msg, WORD code);
	bool SendProtocol(SOCKET socket, WORD code);

public:
	Server();
	virtual ~Server();
};

