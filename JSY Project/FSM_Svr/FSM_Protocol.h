#pragma once
#include "Protocol.h"

#define PACKET_CHAR_NAME_REQ 1000
#define PACKET_CHAR_NAME_ACK 1001
#define PACKET_CHAR_MSG      1002

#pragma  pack( push, 1 )
/// �ʿ��� �������� ����
typedef struct {
	WORD  user_idx; // �ɸ����� ������ �ε���
	WORD  posX;     // ��ǥ
	WORD  posY;
	WORD  direction; // ���� ( 0~7 ) 8����
}TPACKET_USER_POSITION;
#define PACKET_USER_POSITION   3000

#pragma pack(pop)