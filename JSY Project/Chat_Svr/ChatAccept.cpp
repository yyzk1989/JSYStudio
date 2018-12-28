#include "ChatAccept.h"
#include "ChatSvr.h"

void ChatAccept::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	I_Server.AddUser(socket, address);
}

ChatAccept::ChatAccept()
{
}


ChatAccept::~ChatAccept()
{
}
