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
			
			char * data_MSG = NULL;

			//190107		
			PACKET PCK_data;
			float  fX, fY, fCX, fCY, fMaxCX, fMaxCY;
			fX = 400;
			fY = 300;
			fCX = 800;
			fCY = 600;
			fMaxCX = 800;
			fMaxCY = 600;
				
			T_Packet tpack(PACKET_PLAYER_CREATE_LOBY); 
			tpack << fX << fY << fCX << fCY << fMaxCX << fMaxCY << 0;
			tpack.m_strPacketBuffer;
			
			PCK_data.pUser = pUser;
			PCK_data.packet.ph.len = *tpack.m_PacketHeader.len;
			PCK_data.packet.ph.type = *tpack.m_PacketHeader.type;

			memcpy(PCK_data.packet.msg , tpack.m_strPacketBuffer + 6, PACKETBUFFERSIZE - 6);
			
			m_PacketPool.AddPacket(PCK_data);
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

bool FSM_Svr::CreateMyMegaman(FSM_User* pUser)
{
	PACKET PCK_data;
	float  fX, fY, fCX, fCY, fMaxCX, fMaxCY;
	pUser->MyMegaman.m_bDirection = false;
	pUser->MyMegaman.m_bCharacter = true;
	pUser->MyMegaman.m_fPositionX = 440;
	pUser->MyMegaman.m_fPositionY = 400;
	//fY = -2000;
	fCX = 260;
	fCY = 260;
	fMaxCX = 4420;
	fMaxCY = 6760;


	T_Packet tpack(PACKET_CREATE_MY_MEGAMAN);
	tpack << pUser->MyMegaman.m_fPositionX << pUser->MyMegaman.m_fPositionY << fCX << fCY << fMaxCX << fMaxCY << pUser->MyMegaman.m_bDirection;
	tpack.m_strPacketBuffer;

	PCK_data.pUser = pUser;
	PCK_data.packet.ph.len = *tpack.m_PacketHeader.len;
	PCK_data.packet.ph.type = *tpack.m_PacketHeader.type;

	memcpy(PCK_data.packet.msg, tpack.m_strPacketBuffer + 6, PACKETBUFFERSIZE - 6);
	m_PacketPool.SendPacket((UPACKET*)&(PCK_data.packet), pUser->m_Socket);
	//m_PacketPool.AddPacket(PCK_data);
	return 0;
}

bool FSM_Svr::CreateOtherMegaman(FSM_User* pUser, SOCKET SendSocket)
{
	PACKET PCK_data;
	float  fX, fY, fCX, fCY, fMaxCX, fMaxCY;
	pUser->MyMegaman.m_bDirection = false;
	pUser->MyMegaman.m_bCharacter = true;
	fX = 440;
	fY = 400;
	//fY = -2000;
	fCX = 260;
	fCY = 260;
	fMaxCX = 4420;
	fMaxCY = 6760;


	T_Packet tpack(PACKET_CREATE_OTHER_MEGAMAN);
	tpack << pUser->MyMegaman.m_fPositionX << pUser->MyMegaman.m_fPositionY << fCX << fCY << fMaxCX << fMaxCY << pUser->MyMegaman.m_bDirection;
	tpack.m_strPacketBuffer;

	PCK_data.pUser = pUser;
	PCK_data.packet.ph.len = *tpack.m_PacketHeader.len;
	PCK_data.packet.ph.type = *tpack.m_PacketHeader.type;

	memcpy(PCK_data.packet.msg, tpack.m_strPacketBuffer + 6, PACKETBUFFERSIZE - 6);


	std::list<FSM_User*>::iterator	iter;
	std::list<FSM_User*>::iterator	delUser;

	int iClientUser = I_Server.m_UserList.size();
	for (iter = I_Server.m_UserList.begin();
		iter != I_Server.m_UserList.end();
		iter++)
	{
		FSM_User* pUser = (FSM_User*)*iter;
		if (pUser->m_Socket != SendSocket)
		{
			if (!m_PacketPool.SendPacket((UPACKET*)&(PCK_data.packet), pUser->m_Socket))
			{
				I_Debug.T_ERROR(false);
				continue;
			}
		}
		printf("CreateOtherMegaman - %s 보냈습니다.\n", pUser->m_szName.c_str());
		//I_Debug.Print("%s%s%s", pUser->m_szName.c_str(), msg, "보냈습니다.");
	}

	return 0;
}

bool FSM_Svr::ActCheckMegaman(FSM_User* pUser)
{

	return 0;
}

bool FSM_Svr::GameProc()
{
	check_Time += g_fSecPerFrame;

	if (check_Time > 3)
	{
		{
			Synchronize sync(this);
			std::list<FSM_User*>::iterator	iter;
			std::list<FSM_User*>::iterator	delUser;

			bool b_ret;

			int iClientUser = I_Server.m_UserList.size();
			for (iter = I_Server.m_UserList.begin();
				iter != I_Server.m_UserList.end();
				iter++)
			{
				FSM_User* pUser = (FSM_User*)*iter;
				
				if (pUser->MyMegaman.i_NOW_Stage == 1)
				{
					if (pUser->MyMegaman.m_bCharacter == false)
					{
						b_ret = CreateMyMegaman( pUser);
						
						b_ret = CreateOtherMegaman(pUser, pUser->m_Socket);
					}
					
					if (pUser->MyMegaman.m_bCharacter == true)
					{
						b_ret = ActCheckMegaman(pUser);
					}

					printf("Time Test - IP = %s, PORT = %d \n", inet_ntoa(pUser->m_UserAddress.sin_addr), ntohs(pUser->m_Socket));

				}
			}
		}
		check_Time = 0;
	}
	return 0;
}


bool FSM_Svr::Init()
{
	printf("Sever Start\n");
	// I_Debug.Print("%s", "서버 시작합니다.");
	Server::Init();
	FSM_Timer::Init();
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
		FSM_Timer::Frame();
		m_PacketPool.ProcessPacket();
		GameProc();
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
