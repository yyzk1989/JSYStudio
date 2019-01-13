#pragma once

#include "PacketPool.h"
typedef struct _OVERLAPPEDEX : OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND = 1 };
	int iFlags;
	_OVERLAPPEDEX() {
		iFlags = MODE_RECV;
	}
}OVERLAPPEDEX;

class User : public ServerObj
{
	// 캐릭터 정보
public:
	/*
	int				m_iIndex;
	float			m_fPositionX;
	float			m_fPositionY;
	bool			m_bDirection;

	int				i_HP = 15;
	int				i_Attack = 1; //charge는 4

	int				i_NOW_Stage = 0;
	bool			m_bCharacter = false;
	*/
public:
	StreamPacket	m_StreamPacket;
	SOCKET			m_Socket;
	C_STR			m_szName;
	SOCKADDR_IN		m_UserAddress;
	WSABUF			m_szRecvBuffer;
	WSABUF			m_szWsaBuf;
	char			m_strBuffer[4096];
	OVERLAPPEDEX	m_ov;
public:
	bool Create();
	bool Run();
	virtual void AddPacket(PACKET& addPacket);
	virtual void DeleteUser(SOCKET socket);
	virtual void DeleteUser();
	virtual void WaitForPacketReceive();
	virtual void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);

public:
	User();
	~User();
};

