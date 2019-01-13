#pragma once

#include <windows.h>
#include "Protocol.h"

//#define PACKETBUFFERSIZE   8192
#define PACKETBUFFERSIZE   2048

class T_Packet
{
public:
	typedef struct {
		WORD* len;
		WORD* type;
	}PACKETHEADER;
public:
	PACKETHEADER	m_PacketHeader;
	char			m_strPacketBuffer[PACKETBUFFERSIZE];
	char*			m_pstrWritePosition;
	char*			m_pstrReadPosition;

	WORD			GetID();
	WORD			GetSize();
	UPACKET			getPacket();
	int				m_iReceivedSize;
	int				GetDataSize();
	//void			ReadData(void* buffer, int iSize);
	void			ReadData(char* buffer, int iSize);
	void			WriteData(void* buffer, int iSize);
	//void			WriteData(char* buffer, int iSize);

	T_Packet&		SetID(unsigned short ID);
	// 패킷을 생성할 때 
	T_Packet&     operator << (int arg);
	// 패킷에서 데이터를 추출할 때
	T_Packet&     operator >> (int& arg);
	
	T_Packet&     operator << (DWORD arg);
	T_Packet&     operator >> (DWORD& arg);

	T_Packet&     operator << (bool arg);
	T_Packet&     operator >> (bool& arg);

	T_Packet&     operator << (unsigned short arg);
	T_Packet&     operator >> (unsigned short& arg);

	T_Packet&     operator << (float arg);
	T_Packet&     operator >> (float& arg);

	T_Packet&     operator << (char* arg);
	T_Packet&     operator >> (char* arg);
	T_Packet&     operator << (T_Packet& arg);
	T_Packet&     operator >> (T_Packet& arg);

	char*			GetData();
	void   Clear();
public:
	T_Packet();
	T_Packet(unsigned short type);
	virtual ~T_Packet();
};

