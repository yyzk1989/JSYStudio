#include "User.h"


void User::Dispatch(DWORD dwByteSize,
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
void User::AddPacket(PACKET& addPacket)
{
	{
		Synchronize sync(this);
		m_StreamPacket.m_PacketList.push_back(addPacket);
	}
	return;
}
bool User::Create()
{
	ZeroMemory(&m_ov, sizeof(m_ov));
	WaitForPacketReceive();
	return true;
}
void User::WaitForPacketReceive()
{
	DWORD cbTransferred, flags = 0;
	m_szRecvBuffer.buf = m_strBuffer;
	m_szRecvBuffer.len = 4096;
	int iRet = WSARecv(m_Socket, &m_szRecvBuffer, 1,
		&cbTransferred, &flags,
		(LPOVERLAPPED)&m_ov, NULL);

	if (iRet == SOCKET_ERROR)
	{
		int dwError = WSAGetLastError();
		if (dwError != WSA_IO_PENDING)
		{
			int kkkk = 0;
		}
	}
}
bool User::Run()
{
	char szMsgBuffer[2048] = { 0, };
	int strlen = 0;
	while (1)
	{
		strlen = recv(m_Socket,
			szMsgBuffer, sizeof(szMsgBuffer), 0);
		if (strlen <= 0) break;
		szMsgBuffer[strlen] = 0;
		m_StreamPacket.Put(szMsgBuffer, strlen, this);
		Sleep(10);
	}
	DeleteUser(m_Socket);
	return true;
}
void User::DeleteUser(SOCKET socket)
{
}
void User::DeleteUser()
{
}
User::User(void)
{
	m_Socket = 0;
}


User::~User(void)
{
	closesocket(m_Socket);
}

