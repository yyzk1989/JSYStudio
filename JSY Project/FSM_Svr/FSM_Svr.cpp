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
		// ���� ���� ü��.
		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		// I_Debug.Print("IP=%s, PORT=%d",	inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		printf("AddUser - IP = %s, PORT = %d \n", inet_ntoa(address.sin_addr), ntohs(socket));
		//printf("\nŬ���̾�Ʈ ���� : IP:%s, PORT:%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientSocket));

		if (pUser)
		{			
			m_UserList.push_back(pUser);
			char * data_MSG = NULL;
			/*
			
			stFSM_Back_Ground stLOBY;
			
			stLOBY.fX=400;
			stLOBY.fY=300;

			stLOBY.fCX=800;
			stLOBY.fCY=600;
			
			stLOBY.fMaxCX=800;
			stLOBY.fMaxCY=600;
			*/
			//I_Server.SendProtocol(pUser->m_Socket, PACKET_PLAYER_CREATE_LOBY);
		
			//190104
			
			PACKET PCK_data;
			float  fX, fY, fCX, fCY, fMaxCX, fMaxCY;
			fX = 400;
			fY = 300;
			fCX = 800;
			fCY = 600;
			fMaxCX = 800;
			fMaxCY = 600;
			//tpack.SetID(PACKET_PLAYER_CREATE_LOBY);
			//tpack << fX << fY << fCX << fCY << fMaxCX << fMaxCY;
			
			
			T_Packet tpack(PACKET_PLAYER_CREATE_LOBY); 
			tpack << fX << fY << fCX << fCY << fMaxCX << fMaxCY;
			//tpack.SetID(2000) << fX << fY << fCX << fCY << fMaxCX << fMaxCY;
			tpack.m_strPacketBuffer;
			PCK_data.pUser = pUser;
			/*
			PCK_data.packet.ph.len = tpack.m_iReceivedSize + PACKET_HEADER_SIZE;
			PCK_data.packet.ph.type = PACKET_PLAYER_CREATE_LOBY;
			*/
			PCK_data.packet.ph.len = *tpack.m_PacketHeader.len;
			PCK_data.packet.ph.type = *tpack.m_PacketHeader.type;

			memcpy(PCK_data.packet.msg , tpack.m_strPacketBuffer + 6, PACKETBUFFERSIZE - 6);
			
			m_PacketPool.AddPacket(PCK_data);
				
			//memcpy(data_MSG, (char*)&stLOBY,sizeof(stLOBY));
			//I_Server.SEND_MAP_INFO(pUser->m_Socket, stLOBY, PACKET_PLAYER_CREATE_LOBY);
			// I_Server.SendMsg(pUser->m_Socket, data_MSG, PACKET_PLAYER_CREATE_LOBY);
			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (ULONG_PTR)pUser);
			pUser->Create();
		}
	}
	return true;
}

bool FSM_Svr::SEND_MAP_INFO(SOCKET SendSocket, stFSM_Back_Ground InfoData, WORD code)
{
	stFSM_Back_Ground send_data;
	ZeroMemory(&send_data, sizeof(send_data));
	//memcpy(send_data, InfoData);
	InfoData.type = code;
	InfoData.len = sizeof(InfoData);
	int iRet = send(SendSocket, (char*)&InfoData, sizeof(InfoData), 0);
	if (iRet <= 0)
	{
		return false;
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
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "���� �����̽��ϴ�.");
				printf("Deslete User - %s���� �����̽��ϴ�.\n", buffer);
				//I_Debug.Print("%s%s", pUser->m_szName.c_str(), "���� �����̽��ϴ�.");
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
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "���� �����̽��ϴ�.");
				//I_Debug.Print("%s%s", pUser->m_szName.c_str(), "���� �����̽��ϴ�.");
				printf("Deslete User - %s���� �����̽��ϴ�.\n", buffer);
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
			printf("IndividualSend - %s���� %s ���½��ϴ�.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s���� %s ���½��ϴ�.", pUser->m_szName.c_str(), pPacket->msg);
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
			printf("Broadcastting - %s���� %s ���½��ϴ�.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s���� %s ���½��ϴ�.", pUser->m_szName.c_str(), pPacket->msg);
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
			printf("Broadcastting - %s���� %s ���½��ϴ�.\n", pUser->m_szName.c_str(), pPacket->msg);
			//I_Debug.Print("%s���� %s���� %s ���½��ϴ�.", pUser->m_szName.c_str(), pUserData->pUser->m_szName.c_str(),	pUserData->packet.msg);
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
			printf("Broadcastting - %s = %s ���½��ϴ�.\n", pUser->m_szName.c_str(), msg);
			//I_Debug.Print("%s%s%s", pUser->m_szName.c_str(), msg, "���½��ϴ�.");
		}
	}
};
bool FSM_Svr::Init()
{
	printf("Sever Start\n");
	// I_Debug.Print("%s", "���� �����մϴ�.");
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
