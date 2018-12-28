#pragma once
#include "Thread.h"
#include "StreamPacket.h"
class PacketPool : public ServerObj
{
public:
	std::list<PACKET> m_PacketList;
	typedef std::list<PACKET>::iterator m_PackItor;
public:
	virtual bool		AddPacket(PACKET& addPacket);
	virtual bool		ProcessPacket();
	virtual void		ProcessWork(PACKET* pUserData);
public:
	PacketPool();
	virtual ~PacketPool();
};

