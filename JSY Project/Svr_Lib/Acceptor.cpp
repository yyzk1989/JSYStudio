#include "Acceptor.h"
#include "User.h"
#include "Server.h"
#include "stdio.h"
#include "ServerIOCP.h"
#include "DebugString.h"

bool Acceptor::Release()
{
	return true;
}
bool Acceptor::Run()
{
	SOCKET clientSocket;
	SOCKADDR_IN clientaddr;
	int   addrlen;
	while (m_bStarted)
	{
		addrlen = sizeof(clientaddr);
		clientSocket = accept(m_ListenSock,
			(SOCKADDR*)&clientaddr, &addrlen);
		if (clientSocket == INVALID_SOCKET)
		{
			continue;
		}
		AddUser(clientSocket, clientaddr);
		Sleep(10);
	}
	return true;
}
void Acceptor::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	char buf[255] = { 0, };
	InetNtopA(AF_INET,
		&address.sin_addr,
		buf, sizeof(char) * 255);
}
bool Acceptor::Set(int iPort,
	const char* strAddress)
{
	int iRet;
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);
	/////////////////////////////////
	//
	/////////////////////////////////
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSock == INVALID_SOCKET)
	{
		return false;
	}
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	if (strAddress == NULL)
	{
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		serveraddr.sin_addr.s_addr =
			inet_addr(strAddress);
	}
	serveraddr.sin_port = htons(iPort);
	iRet = ::bind(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(SOCKADDR));
	if (iRet == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSAEADDRINUSE:
		case WSAEACCES:
			I_Debug.T_ERROR();
			break;
		}
		return false;
	}

	iRet = listen(m_ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;

	char cFlag = 1;
	if (SOCKET_ERROR == setsockopt(m_ListenSock, IPPROTO_TCP, TCP_NODELAY, &cFlag, sizeof(char)))
	{
		return FALSE;
	}

	int optvalexe = 1;
	iRet = setsockopt(m_ListenSock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
		(char *)&optvalexe, sizeof(optvalexe));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.T_ERROR();
	}


	linger optval2;
	int iSize = sizeof(optval2);
	optval2.l_linger = 1000;
	optval2.l_onoff = 1;
	getsockopt(m_ListenSock, SOL_SOCKET,
		SO_LINGER, (char*)&optval2,
		&iSize);
	setsockopt(m_ListenSock, SOL_SOCKET,
		SO_LINGER, (char*)&optval2,
		iSize);
	int socketType1;
	int typeLen1 = sizeof(socketType1);
	getsockopt(m_ListenSock, SOL_SOCKET,
		SO_TYPE, (char*)&socketType1,
		&typeLen1);
	//if( socketType1 == SOCK_STREAM )

	if (getsockopt(m_ListenSock, SOL_SOCKET,
		SO_SNDBUF, (char*)&socketType1,
		&typeLen1)< 0)
	{
		I_Debug.T_ERROR();
	}
	if (getsockopt(m_ListenSock, SOL_SOCKET,
		SO_RCVBUF, (char*)&socketType1,
		&typeLen1)< 0)
	{
		I_Debug.T_ERROR();
	}

	int sdnBufferSize = 10000;
	int sndBufferSizeLen = sizeof(sndBufferSizeLen);
	if (setsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF,
		(char*)&sdnBufferSize, sndBufferSizeLen) < 0)
	{
		I_Debug.T_ERROR();
	}

	int rcvBufferSizeLen = sizeof(int);
	int rcvBufferSize = 10000;
	if (setsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF,
		(char*)&rcvBufferSize, rcvBufferSizeLen)< 0)
	{
		I_Debug.T_ERROR();
	}

	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType1,
		&typeLen1) == SOCKET_ERROR)
	{
		I_Debug.T_ERROR();
	}
	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType1,
		&typeLen1) == SOCKET_ERROR)
	{
		I_Debug.T_ERROR();
	}

	// 쓰레드 생성 
	CreateThread();
	return true;
}

Acceptor::Acceptor()
{
}


Acceptor::~Acceptor()
{
}
