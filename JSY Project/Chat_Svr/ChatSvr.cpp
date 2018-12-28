#include "ChatSvr.h"
#include "Server.h"
#include "ServerIOCP.h"
#include "DebugString.h"

bool ChatSvr::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	{
		Synchronize sync(this);
		ChatUser* pUser = NULL;
		SAFE_NEW(pUser, ChatUser);
		// 유저 정보 체움.
		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		// I_Debug.Print("IP=%s, PORT=%d",	inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		printf("AddUser - IP = %s, PORT = %d \n",   inet_ntoa(address.sin_addr), ntohs(socket));
		//printf("\n클라이언트 접속 : IP:%s, PORT:%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientSocket));

		if (pUser)
		{
			I_Server.SendProtocol(pUser->m_Socket, PACKET_CREATE_LOBI);
			// I_Server.SendMsg(pUser->m_Socket, "환영! 대화명 입력하시오\n", 	PACKET_CHAR_NAME_REQ);
			m_UserList.push_back(pUser);

			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (ULONG_PTR)pUser);
			pUser->Create();
		}
	}
	return true;
}
void ChatSvr::DeleteUser(SOCKET socket)
{
	{
		Synchronize sync(this);
		std::list<ChatUser*>::iterator	iter;
		std::list<ChatUser*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			ChatUser* pUser = (ChatUser*)*iter;
			if (pUser->m_Socket == socket)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				printf("Deslete User - %s님이 나가셨습니다.\n", buffer);
				//I_Debug.Print("%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				I_Server.Broadcastting(buffer, PACKET_CHAR_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				delUser = iter;
				SAFE_DEL(pUser);
				break;
			}
		}
		I_Server.m_UserList.erase(delUser);
	}
};
//TChatUser* pUser
void ChatSvr::DeleteUser(ChatUser* pDeleteUser)
{
	{
		Synchronize sync(this);
		std::list<ChatUser*>::iterator	iter;
		std::list<ChatUser*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			ChatUser* pUser = (ChatUser*)*iter;
			if (pUser == pDeleteUser)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				//I_Debug.Print("%s%s", pUser->m_szName.c_str(), "님이 나가셨습니다.");
				printf("Deslete User - %s님이 나가셨습니다.\n", buffer);
				I_Server.Broadcastting(buffer, PACKET_CHAR_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				delUser = iter;
				SAFE_DEL(pUser);
				break;
			}
		}
		I_Server.m_UserList.erase(delUser);
	}
};
void ChatSvr::Broadcastting(UPACKET* pPacket, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		std::list<ChatUser*>::iterator	iter;
		std::list<ChatUser*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			ChatUser* pUser = (ChatUser*)*iter;
			//if( 0==SendSocket /*|| pUser->m_Socket != SendSocket*/ )
			{
				int iRet = send(pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			printf("Broadcastting - %s에게 %s 보냈습니다.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s에게 %s 보냈습니다.", pUser->m_szName.c_str(), pPacket->msg);
		}
	}
}
void ChatSvr::Broadcastting(PACKET* pUserData)
{
	{
		Synchronize sync(this);
		std::list<ChatUser*>::iterator	iter;
		std::list<ChatUser*>::iterator	delUser;

		UPACKET* pPacket = &pUserData->packet;
		DWORD dwSendByte;
		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			ChatUser* pUser = (ChatUser*)*iter;
			if (pUser->m_Socket != pUserData->pUser->m_Socket)
			{
				/*pUser->m_szWsaBuf.buf = (CHAR *)pPacket;
				pUser->m_szWsaBuf.len = pPacket.ph.len;
				pUser->m_ov.iFlag = OVERLAPPEDEX::MODE_SEND;

				T_PACKET* P = (T_PACKET*)pUser->m_szWsaBuf.buf;

				int iRet = WSASend(pUser->m_Socket,
				&(pUser->m_szWsaBuf),
				1,
				&dwSendByte,
				0,
				(LPOVERLAPPED)&pUser->m_ov,
				NULL);*/

				int iRet = send(pUser->m_Socket, (char*)&pUserData->packet, pUserData->packet.ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			printf("Broadcastting - %s에게 %s 보냈습니다.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s에게 %s님의 %s 보냈습니다.", pUser->m_szName.c_str(), pUserData->pUser->m_szName.c_str(),	pUserData->packet.msg);
		}
	}
};
void ChatSvr::Broadcastting(char* msg, WORD code, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		std::list<ChatUser*>::iterator	iter;
		std::list<ChatUser*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			ChatUser* pUser = (ChatUser*)*iter;
			if (0 == SendSocket || pUser->m_Socket != SendSocket)
			{
				if (!SendMsg(pUser->m_Socket, msg, code))
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			printf("Broadcastting - %s = %s 보냈습니다.\n", pUser->m_szName.c_str(), msg);
			//I_Debug.Print("%s%s%s", pUser->m_szName.c_str(), msg, "보냈습니다.");
		}
	}
};
bool ChatSvr::Init()
{
	printf("Sever Start\n");
	// I_Debug.Print("%s", "서버 시작합니다.");
	Server::Init();
	m_Acceptor.Set(10000, NULL);
	return true;
}
bool ChatSvr::Release()
{
	return Server::Release();
}
bool ChatSvr::Run()
{
	while (m_bStarted)
	{
		m_PacketPool.ProcessPacket();
		Sleep(10);
	}
	return true;
}

ChatSvr::ChatSvr()
{
}


ChatSvr::~ChatSvr()
{
}
