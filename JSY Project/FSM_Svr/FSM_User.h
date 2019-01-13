#pragma once
#include "User.h"
#include "FSM_Megaman_Info.h"
class FSM_User : public User
{
public:
	FSM_Megaman_Info MyMegaman;
	std::list<FSM_Megaman_Info*> OhterMegaman;
public:
	void Movement(UPACKET* pPacket);
	void AddPacket(PACKET& addPacket);
	int SendPacket(PACKET& addPacket, UPACKET* pPacket);
	void DeleteUser(SOCKET socket);
	void DeleteUser();
	void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);
public:
	FSM_User();
	~FSM_User();
};

