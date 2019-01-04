#include "Server.h"

bool Server::SendMsg(SOCKET socket, const char* msg, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	//sprintf( sendmsg.msg, "%s", msg );
	sprintf_s(sendmsg.msg, "%s", msg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) +
		strlen(sendmsg.msg);
	int iRet = send(socket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		return false;
	}
	return true;
}
bool Server::SendMsg(SOCKET socket, char* msg, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	//sprintf( sendmsg.msg, "%s", msg );
	sprintf_s(sendmsg.msg, "%s", msg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + strlen(sendmsg.msg);
	int iRet = send(socket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		return false;
	}
	return true;
}

bool Server::SendProtocol(SOCKET socket, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER);
	int iRet = send(socket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		return false;
	}
	return true;
}
bool Server::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	return true;
}
bool Server::Init()
{
	// 쓰레드 생성 
	CreateThread();
	return true;
}

bool Server::Run()
{
	return true;
}
bool Server::Release()
{
	return true;
}


Server::Server()
{
}


Server::~Server()
{
}
