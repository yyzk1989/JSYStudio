#pragma once

#include <windows.h>
#include "Protocol.h"

#define PACKETBUFFERSIZE   8192

class Packet
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
	int				m_iReceivedSize;
	int				GetDataSize();
	void			ReadData(void* buffer, int iSize);
	void			WriteData(void* buffer, int iSize);

	Packet&		SetID(unsigned short ID);
	// 패킷을 생성할 때 
	Packet&     operator << (int arg);
	// 패킷에서 데이터를 추출할 때
	Packet&     operator >> (int& arg);

	Packet&     operator << (DWORD arg);
	Packet&     operator >> (DWORD& arg);

	Packet&     operator << (bool arg);
	Packet&     operator >> (bool& arg);

	Packet&     operator << (unsigned short arg);
	Packet&     operator >> (unsigned short& arg);

	Packet&     operator << (float arg);
	Packet&     operator >> (float& arg);

	Packet&     operator << (char* arg);
	Packet&     operator >> (char* arg);
	Packet&     operator << (Packet& arg);
	Packet&     operator >> (Packet& arg);

	char*			GetData();
	void   Clear();
public:
	Packet();
	Packet(unsigned short type);
	virtual ~Packet();
};

