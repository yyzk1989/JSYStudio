#pragma once

#include <windows.h>
#define PACKET_HEADER_SIZE 4
#pragma  pack( push, 1 )

typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;

typedef struct UPACKET {

	UPACKET()
	{
		ZeroMemory(msg, 2048);
	}
	UPACKET& operator = (const UPACKET& rhs)
	{
		CopyMemory(this, &rhs, sizeof(UPACKET));
		return *this;
	}
	PACKET_HEADER ph;
	char     msg[2048];
}UPACKET, *P_UPACKET;

#pragma pack(pop)
