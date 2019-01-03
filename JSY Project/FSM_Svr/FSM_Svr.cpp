#include "FSM_Svr.h"
#include "Server.h"
#include "ServerIOCP.h"
#include "DebugString.h"

bool FSM_Svr::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	{
		Synchronize sync(this);
		FSM_User* pUser = NULL;
		SAFE_NEW(pUser, FSM_User);
		// 유저 정보 체움.
		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		// I_Debug.Print("IP=%s, PORT=%d",	inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		printf("AddUser - IP = %s, PORT = %d \n", inet_ntoa(address.sin_addr), ntohs(socket));
		//printf("\n클라이언트 접속 : IP:%s, PORT:%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientSocket));

		if (pUser)
		{
			m_UserList.push_back(pUser);

			T_Packet tpack;
			PACKET PCK_data;
			float  fX, fY, fCX, fCY, fMaxCX, fMaxCY;
			fX = 400;
			fY = 300;
			fCX = 800;
			fCY = 600;
			fMaxCX = 800;
			fMaxCY = 600;
			tpack.SetID(PACKET_PLAYER_CREATE_LOBY) << fX << fY << fCX << fCY << fMaxCX << fMaxCY;

			PCK_data.pUser = pUser;
			PCK_data.packet.ph.type = PACKET_PLAYER_CREATE_LOBY;
			PCK_data.packet.ph.len = sizeof(tpack);
			memcpy(PCK_data.packet.msg, tpack.m_pstrWritePosition,tpack.m_iReceivedSize);
			
			m_PacketPool.AddPacket(PCK_data);
			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (ULONG_PTR)pUser);
			pUser->Create();
		}
	}
	return true;
}
void FSM_Svr::DeleteUser(SOCKET socket)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
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
void FSM_Svr::DeleteUser(FSM_User* pDeleteUser)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
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
void FSM_Svr::IndividualSend(UPACKET* pPacket, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
			if( pUser->m_Socket == SendSocket )
			{
				int iRet = send(pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			printf("IndividualSend - %s에게 %s 보냈습니다.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s에게 %s 보냈습니다.", pUser->m_szName.c_str(), pPacket->msg);
		}
	}
}
void FSM_Svr::Broadcastting(UPACKET* pPacket, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
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
void FSM_Svr::Broadcastting(PACKET* pUserData)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		UPACKET* pPacket = &pUserData->packet;
		DWORD dwSendByte;
		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
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
void FSM_Svr::Broadcastting(char* msg, WORD code, SOCKET SendSocket)
{
	{
		Synchronize sync(this);
		std::list<FSM_User*>::iterator	iter;
		std::list<FSM_User*>::iterator	delUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			FSM_User* pUser = (FSM_User*)*iter;
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
bool FSM_Svr::Init()
{
	printf("Sever Start\n");
	// I_Debug.Print("%s", "서버 시작합니다.");
	Server::Init();
	m_Acceptor.Set(10000, NULL);
	return true;
}
bool FSM_Svr::Release()
{
	return Server::Release();
}
bool FSM_Svr::Run()
{
	while (m_bStarted)
	{
		m_PacketPool.ProcessPacket();
		Sleep(10);
	}
	return true;
}


FSM_Svr::FSM_Svr()
{
}


FSM_Svr::~FSM_Svr()
{
}
