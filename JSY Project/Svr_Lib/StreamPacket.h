#pragma once
#include "ServerObj.h"
#include "Protocol.h"
#define MAX_RECV_SIZE 10000

class User;
typedef struct {
	UPACKET packet;
	User*  pUser;
}PACKET, *P_PACKET;


class StreamPacket : public ServerObj
{
public:
	std::list<PACKET> m_PacketList;
	typedef std::list<PACKET>::iterator m_PackItor;
public:
	UPACKET * m_pPacket;
	char				m_RecvBuffer[MAX_RECV_SIZE];
	int					m_iStartPos;
	int					m_iWritePos;
	int					m_iReadPos;
public:
	void    Put(char* redvBuffer, int iSize, User* = NULL);
public:
	StreamPacket();
	virtual ~StreamPacket();
};

