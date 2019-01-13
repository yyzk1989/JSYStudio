#include "FSM_User.h"
#include "FSM_Svr.h"

void FSM_User::Movement(UPACKET* pPacket)
{
	TPACKET_USER_POSITION user;
	memcpy(&user, pPacket->msg, sizeof(char)* pPacket->ph.len - 4);
	MyMegaman.m_iIndex = user.user_idx;
	MyMegaman.m_fPositionX = user.shX;
	MyMegaman.m_fPositionY = user.shY;
	MyMegaman.m_bDirection = user.bDirection;

};
void FSM_User::AddPacket(PACKET& addPacket)
{
	I_Server.m_PacketPool.AddPacket(addPacket);
}
int FSM_User::SendPacket(PACKET& addPacket, UPACKET* pPacket)
{
	
	int iRet = send(addPacket.pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
	if (iRet == SOCKET_ERROR)
	{
		printf("SendPacket()");
		return 1;
	}
	return 0;
}

void FSM_User::DeleteUser(SOCKET socket)
{
	I_Server.DeleteUser(socket);
};
void FSM_User::DeleteUser()
{
	I_Server.DeleteUser(this);
}
void FSM_User::Dispatch(DWORD dwByteSize,
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


FSM_User::FSM_User()
{
}


FSM_User::~FSM_User()
{
}
