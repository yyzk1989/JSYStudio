#include "StreamPacket.h"
#include "Server.h"


void   StreamPacket::Put(char* recvBuffer, int iRecvSize, User* pUser)
{
	{
		Synchronize sync(this);
		// 받는 버퍼의 용량이 부족하면
		if (m_iWritePos + iRecvSize >= MAX_RECV_SIZE)
		{
			char strTemp[MAX_RECV_SIZE] = { 0, };
			memcpy(strTemp, &m_RecvBuffer[m_iStartPos], m_iReadPos);
			ZeroMemory(&m_RecvBuffer, sizeof(char)* MAX_RECV_SIZE);
			memcpy(&m_RecvBuffer, &strTemp, m_iReadPos);
			m_pPacket = (P_UPACKET)m_RecvBuffer;
			m_iStartPos = 0;
			m_iWritePos = m_iReadPos;
		}

		memcpy(&m_RecvBuffer[m_iWritePos], recvBuffer, iRecvSize);
		m_iWritePos += iRecvSize;
		m_iReadPos += iRecvSize;

		if (m_iReadPos < PACKET_HEADER_SIZE) return;

		// 패킷의 시작
		m_pPacket = (P_UPACKET)&m_RecvBuffer[m_iStartPos];
		// 1개의 패킷 사이즈만큼 받았다면
		if (m_iReadPos >= m_pPacket->ph.len)
		{
			do {
				PACKET    add;
				ZeroMemory(&add, sizeof(add));
				memcpy(&add.packet, &m_RecvBuffer[m_iStartPos], m_pPacket->ph.len);
				add.pUser = pUser;

				if (pUser != NULL)
				{
					pUser->AddPacket(add);
				}

				// 1개의 패킷을 처리하고 남은 잔여량 크기
				m_iReadPos -= m_pPacket->ph.len;
				// 패킷의 시작 위치
				m_iStartPos += m_pPacket->ph.len;

				// 잔여량이 패킷 헤더모다 작을 경우
				if (m_iReadPos < PACKET_HEADER_SIZE) break;

				m_pPacket = (P_UPACKET)&m_RecvBuffer[m_iStartPos];
			} while (m_iReadPos >= m_pPacket->ph.len);
		}
	}
};

StreamPacket::StreamPacket()
{
	ZeroMemory(m_RecvBuffer, sizeof(char) * MAX_RECV_SIZE);
	m_iStartPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
	m_pPacket = NULL;
}


StreamPacket::~StreamPacket()
{
}
