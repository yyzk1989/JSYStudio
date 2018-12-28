#pragma once
#include "User.h"
class FSM_User : public User
{
public:
	int			m_iIndex;
	int			m_PositionX;
	int			m_PositionY;
	int			m_iDirection;
public:
	void Movement(UPACKET* pPacket);
	void AddPacket(PACKET& addPacket);
	void DeleteUser(SOCKET socket);
	void DeleteUser();
	void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);
public:
	FSM_User();
	~FSM_User();
};

