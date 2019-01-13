#pragma once

#include "Server.h"
#include "FSM_PacketPool.h"
#include "FSM_Accept.h"
#include "FSM_User.h"
#include "FSM_Struct.h"
#include "FSM_Timer.h"

class FSM_Svr : public Singleton<FSM_Svr>, public Server , public FSM_Timer
{
private:
	friend class Singleton<FSM_Svr>;

	float check_Time;
public:
	FSM_PacketPool   m_PacketPool;
	FSM_Accept       m_Acceptor;

	//////////////  유저 리스트 ///////////////////
	std::list<FSM_User*>	m_UserList;
	typedef std::list<FSM_User*>::iterator m_ListItor;
	int					m_iUserCount;
public:
	bool	Init();
	bool	Release();
	bool	Run();
	//LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam,	LPARAM lParam);
	void	Print(char* fmt, ...);
	bool	AddUser(SOCKET socket, SOCKADDR_IN address);
	void	DeleteUser(SOCKET socket);
	void	DeleteUser(FSM_User* pUser);
	void	Broadcastting(char* msg, WORD code, SOCKET SendSocket = 0);
	void	Broadcastting(PACKET* pUserData);
	void	Broadcastting(UPACKET* pPacket, SOCKET pSendUser = NULL);
	void	IndividualSend(UPACKET* pPacket, SOCKET SendSocket = NULL);


	bool	GameProc();
	bool	CreateMyMegaman(FSM_User* pUser);
	bool	CreateOtherMegaman(FSM_User* pUser, SOCKET SendSocket);
	bool	ActCheckMegaman(FSM_User* pUser);
	bool	CreateEnemy(FSM_User* pUser);
	
	bool	SEND_MAP_INFO(SOCKET SendSocket, stFSM_Back_Ground InfoData, WORD code);


public:
	FSM_Svr();
	~FSM_Svr();
};

#define I_Server FSM_Svr::GetInstance()
