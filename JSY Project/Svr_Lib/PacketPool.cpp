#include "PacketPool.h"

bool PacketPool::AddPacket(PACKET& addPacket)
{
	{
		Synchronize sync(this);
		m_PacketList.push_back(addPacket);
	}
	return true;
}
bool PacketPool::ProcessPacket()
{
	{
		Synchronize sync(this);
		std::list<PACKET>::iterator iter;
		for (iter = m_PacketList.begin();
			iter != m_PacketList.end();
			iter++)
		{
			PACKET* pUserData = (PACKET*)&(*iter);
			ProcessWork(pUserData);
		}
		m_PacketList.clear();
	}
	return true;
}
void PacketPool::ProcessWork(PACKET* pUserData)
{
}

PacketPool::PacketPool()
{
}


PacketPool::~PacketPool()
{
}
