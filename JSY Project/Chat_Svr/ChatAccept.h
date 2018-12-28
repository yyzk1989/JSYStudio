#pragma once
#include "Acceptor.h"

class ChatAccept : public Acceptor
{
public:
	void AddUser(SOCKET socket, SOCKADDR_IN address);
public:
	ChatAccept();
	~ChatAccept();
};

