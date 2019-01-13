#pragma once
#include "Protocol.h"

#define PACKET_CHAR_NAME_REQ 1000
#define PACKET_CHAR_NAME_ACK 1001
#define PACKET_CHAR_MSG      1002

#define PACKET_PLAYER_CREATE_LOBY 2000
#define cl_PACKET_PLAYER_SEND_STARTBTN_1 2001
#define PACKET_PLAYER_SEND_EXITBTN_2 2002

#define PACKET_CREATE_MY_MEGAMAN 3000
#define PACKET_CREATE_OTHER_MEGAMAN 3001

#pragma  pack( push, 1 )
/// �ʿ��� �������� ����

typedef struct {
	WORD     user_idx;
	DWORD	dwSessionID;

	DWORD	dwAction;
	BOOL	bDirection;

	short	shX;
	short	shY;

	char	chHP;
}TPACKET_USER_POSITION;
/*
typedef struct {
	WORD  user_idx; // �ɸ����� ������ �ε���
	WORD  posX;     // ��ǥ
	WORD  posY;
	WORD  direction; // ���� ( 0~7 ) 8����
}TPACKET_USER_POSITION;
*/
#define PACKET_USER_POSITION   3000

#pragma pack(pop)