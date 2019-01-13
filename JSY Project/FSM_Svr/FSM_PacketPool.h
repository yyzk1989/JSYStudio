#pragma once

#include "PacketPool.h"
#include "FSM_Protocol.h"

class FSM_PacketPool : public PacketPool
{
public:
	bool		AddPacket(PACKET& addPacket);
	bool		SendPacket(UPACKET* SendPacket, SOCKET SendSocket);
	void		ProcessWork(PACKET* pUserData);
public:
	FSM_PacketPool();
	~FSM_PacketPool();
};

