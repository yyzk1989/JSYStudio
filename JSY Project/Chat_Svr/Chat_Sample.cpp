#include "Chat_Sample.h"
#include "ChatSvr.h"
#include "ServerIOCP.h"
#include "DebugString.h"
bool   Chat_Sample::Init()
{
	I_ServerIOCP.Init();
	I_Server.Init();
	//m_Sock.Init();
	CreateThread();
	return true;
}

int main()
{
	Chat_Sample server;

	server.Init();
	server.Run();
	

	return 0;
}
Chat_Sample::Chat_Sample()
{
}


Chat_Sample::~Chat_Sample()
{
}
