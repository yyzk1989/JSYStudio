#include "ChatPacketPool.h"
#include "ChatUser.h"
#include "DebugString.h"
#include "ChatSvr.h"
#include "ChatUser.h"


void ChatPacketPool::ProcessWork(PACKET* pUserData)
{
	UPACKET* pPacket = &(pUserData->packet);
	ChatUser*   pUser = (ChatUser*)pUserData->pUser;
	switch (pPacket->ph.type)
	{
	case PACKET_USER_POSITION:
	{
		pUser->Movement(pPacket);
		I_Server.Broadcastting(pPacket, pUser->m_Socket);
	}break;
	case PACKET_CHAR_NAME_ACK:
	{
		pUser->m_szName = pPacket->msg;
		char buffer[256] = { 0, };
		sprintf_s(buffer, "[%s]%s", pUser->m_szName.c_str(), "���� �����Ͽ����ϴ�.");
		ZeroMemory(pPacket->msg, 2048);
		sprintf_s(pPacket->msg, "%s", buffer);
		pPacket->ph.len = sizeof(PACKET_HEADER) + strlen(buffer);
		pPacket->ph.type = PACKET_CHAR_MSG;

		I_Server.Broadcastting(pPacket, pUser->m_Socket);

	}break;
	case PACKET_CHAR_MSG:
	{
		char buffer[256] = { 0, };
		sprintf_s(buffer, "[%s]%s", pUser->m_szName.c_str(), pPacket->msg);
		ZeroMemory(pPacket->msg, 2048);
		sprintf_s(pPacket->msg, "%s", buffer);
		pPacket->ph.len = sizeof(PACKET_HEADER) + strlen(buffer);
		pPacket->ph.type = PACKET_CHAR_MSG;
		I_Server.Broadcastting(pPacket, pUser->m_Socket);
	}break;
	}
}

ChatPacketPool::ChatPacketPool()
{
}


ChatPacketPool::~ChatPacketPool()
{
}
