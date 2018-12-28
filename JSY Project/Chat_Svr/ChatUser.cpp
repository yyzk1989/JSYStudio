#include "ChatUser.h"
#include "ChatSvr.h"

void ChatUser::Movement(UPACKET* pPacket)
{
	TPACKET_USER_POSITION user;
	memcpy(&user, pPacket->msg, sizeof(char)*
		pPacket->ph.len - 4);
	m_iIndex = user.user_idx;
	m_PositionX = user.posX;
	m_PositionY = user.posY;
	m_iDirection = user.direction;
};
void ChatUser::AddPacket(PACKET& addPacket)
{
	I_Server.m_PacketPool.AddPacket(addPacket);
}
void ChatUser::DeleteUser(SOCKET socket)
{
	I_Server.DeleteUser(socket);
};
void ChatUser::DeleteUser()
{
	I_Server.DeleteUser(this);
}
void ChatUser::Dispatch(DWORD dwByteSize,
	LPOVERLAPPED ov)
{
	OVERLAPPEDEX* pOV = (OVERLAPPEDEX*)ov;
	if (dwByteSize == 0) return;
	if (pOV->iFlags == OVERLAPPEDEX::MODE_RECV)
	{
		m_StreamPacket.Put(
			m_szRecvBuffer.buf,
			// this->m_strBuffer,
			dwByteSize,
			this);
	}
	if (pOV->iFlags == OVERLAPPEDEX::MODE_SEND)
	{
	}
	WaitForPacketReceive();
};
ChatUser::ChatUser()
{
}


ChatUser::~ChatUser()
{
}
