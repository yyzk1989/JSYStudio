#include "FSM_Sample.h"
#include "FSM_Svr.h"
#include "ServerIOCP.h"
#include "DebugString.h"

bool   FSM_Sample::Init()
{
	I_ServerIOCP.Init();
	I_Server.Init();
	CreateThread();
	return true;
}

int main()
{
	FSM_Sample server;

	server.Init();	
	server.Run();


	return 0;
}


FSM_Sample::FSM_Sample()
{
}


FSM_Sample::~FSM_Sample()
{
}
