#include "FSM_Accept.h"
#include "FSM_Svr.h"

void FSM_Accept::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	I_Server.AddUser(socket, address);
}


FSM_Accept::FSM_Accept()
{
}


FSM_Accept::~FSM_Accept()
{
}
