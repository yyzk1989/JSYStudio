#pragma once
#include "Acceptor.h"
class FSM_Accept : public Acceptor
{

public:
	void AddUser(SOCKET socket, SOCKADDR_IN address);
public:
	FSM_Accept();
	~FSM_Accept();
};

