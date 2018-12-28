#pragma once
#include "Server.h"
#include "ChatPacketPool.h"
#include "ChatAccept.h"
#include "ChatUser.h"

class ChatSvr : public Singleton<ChatSvr>, public Server
{
private:
	friend class Singleton<ChatSvr>;
public:
	ChatPacketPool   m_PacketPool;
	ChatAccept       m_Acceptor;

	//////////////  유저 리스트 ///////////////////
	std::list<ChatUser*>	m_UserList;
	typedef std::list<ChatUser*>::iterator m_ListItor;
	int					m_iUserCount;
public:
	bool	Init();
	bool	Release();
	bool	Run();
	//LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam,	LPARAM lParam);
	void	Print(char* fmt, ...);
	bool	AddUser(SOCKET socket, SOCKADDR_IN address);
	void	DeleteUser(SOCKET socket);
	void	DeleteUser(ChatUser* pUser);
	void	Broadcastting(char* msg, WORD code, SOCKET SendSocket = 0);
	void	Broadcastting(PACKET* pUserData);
	void	Broadcastting(UPACKET* pPacket, SOCKET pSendUser = NULL);
public:
	ChatSvr();
	~ChatSvr();
};

#define I_Server ChatSvr::GetInstance()
