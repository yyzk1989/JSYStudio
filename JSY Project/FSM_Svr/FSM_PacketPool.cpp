#include "FSM_PacketPool.h"
#include "FSM_User.h"
#include "DebugString.h"
#include "FSM_Svr.h"
#include "FSM_User.h"

bool FSM_PacketPool::AddPacket(PACKET& addPacket)
{
	{
		Synchronize sync(this);
		m_PacketList.push_back(addPacket);
	}
	return true;
}


bool FSM_PacketPool::SendPacket(UPACKET* pPacket, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		send(SendSocket, (char*)pPacket, pPacket->ph.len, 0);

				
	}
	return true;
}

void FSM_PacketPool::ProcessWork(PACKET* pUserData)
{ 
	UPACKET* pPacket = &(pUserData->packet);
	FSM_User*   pUser = (FSM_User*)pUserData->pUser;
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
		sprintf_s(buffer, "[%s]%s", pUser->m_szName.c_str(), "님이 입장하였습니다.");
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
	case PACKET_PLAYER_CREATE_LOBY:
	{
		char buffer[256] = { 0, };
		I_Server.IndividualSend(pPacket, pUser->m_Socket);
		break;
	}

	case cl_PACKET_PLAYER_SEND_STARTBTN_1:
	{
		char buffer[256] = { 0 };
		T_Packet tmp_packet;
		WORD type, len;
		
		tmp_packet.WriteData(pPacket, pPacket->ph.len);

		tmp_packet >> len;
		tmp_packet >> type;
		tmp_packet >> pUser->MyMegaman.i_NOW_Stage;
		
		sprintf_s(buffer, "%s님 %d", pUser->m_szName.c_str(), pUser->MyMegaman.i_NOW_Stage, "스테이지 입장");
		printf("%s\n", buffer);

		break;
	}

	}
}


FSM_PacketPool::FSM_PacketPool()
{
}


FSM_PacketPool::~FSM_PacketPool()
{
}
