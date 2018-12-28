#pragma once
#include "PacketPool.h"
#include "ProtocolChat.h"
class ChatPacketPool : public PacketPool
{
public:
	void		ProcessWork(PACKET* pUserData);

public:
	ChatPacketPool();
	~ChatPacketPool();
};

