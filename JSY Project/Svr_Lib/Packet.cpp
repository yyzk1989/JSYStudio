#include "Packet.h"

// TPacket packet;
// int id, ps, money;
// char email[30], address[30];
// packet.SetID(1002) << id << ps;
// packet.SetID(1002) << id << ps << email << addree << money;
// packet.SetID(1002) >> id >> ps >> email >> addree >> money;

// TPacket packet(1002);
// packet << id << ps;
// packet >> id >> ps;
WORD T_Packet::GetID()
{
	return *m_PacketHeader.type;
}
WORD T_Packet::GetSize()
{
	return *m_PacketHeader.len;
}

char* T_Packet::GetData()
{
	return m_strPacketBuffer;
}
int T_Packet::GetDataSize()
{
	return m_iReceivedSize;
}
void T_Packet::ReadData(char* buffer, int iSize)
{
	::CopyMemory(buffer, m_pstrReadPosition, iSize);
	m_pstrReadPosition += iSize;
};
void T_Packet::WriteData(void* buffer, int iSize)
//void T_Packet::WriteData(char* buffer, int iSize)
{
	if (m_iReceivedSize >= PACKETBUFFERSIZE - 4)
	{
		int k = 0;// 오류
	}
	*m_PacketHeader.len += iSize;
	CopyMemory(m_pstrWritePosition, buffer, iSize);
	// 1차원 배열의 주소가 이동
	m_pstrWritePosition += iSize;
	// 실제 데이터의 바이트 용량
	m_iReceivedSize += iSize;
};
T_Packet& T_Packet::SetID(unsigned short ID)
{
	*m_PacketHeader.type = ID;
	return *this;
};
// 패킷을 생성할 때 sum = a.v + b.v + c.v + d.v + e.v;
T_Packet& T_Packet::operator << (int arg)
{
	WriteData(reinterpret_cast<char *>(&arg), sizeof(int));
	return *this;
};
// 패킷에서 데이터를 추출할 때
T_Packet&  T_Packet::operator >> (int& arg)
{
	ReadData(reinterpret_cast<char *>(&arg), sizeof(int));
	return *this;
};

T_Packet&     T_Packet::operator << (DWORD arg) {
	WriteData(reinterpret_cast<char *>(&arg), sizeof(DWORD));
	return *this;
};
T_Packet&     T_Packet::operator >> (DWORD& arg) {
	ReadData(reinterpret_cast<char *>(&arg), sizeof(DWORD));
	return *this;
};

T_Packet&     T_Packet::operator << (bool arg) {
	WriteData(reinterpret_cast<char *>(&arg), sizeof(bool));
	return *this;
};
T_Packet&     T_Packet::operator >> (bool& arg) {
	ReadData(reinterpret_cast<char *>(&arg), sizeof(bool));
	return *this;
};

T_Packet&     T_Packet::operator << (unsigned short arg) {
	WriteData(reinterpret_cast<char *>(&arg), sizeof(unsigned short));
	return *this;
};
T_Packet&     T_Packet::operator >> (unsigned short& arg) {
	ReadData(reinterpret_cast<char *>(&arg), sizeof(unsigned short));
	return *this;
};

T_Packet&     T_Packet::operator << (float arg) {
	WriteData(reinterpret_cast<char *>(&arg), sizeof(float));
	return *this;
};
T_Packet&     T_Packet::operator >> (float& arg) {
	ReadData(reinterpret_cast<char *>(&arg), sizeof(float));
	return *this;
};

T_Packet&     T_Packet::operator << (char* arg)
{
	int iLen = sizeof(char)*strlen(arg);
	WriteData(reinterpret_cast<char *>(&arg), iLen);
	return *this;
};
T_Packet&     T_Packet::operator >> (char* arg)
{
	int iLen = sizeof(char)*strlen(this->m_pstrReadPosition);
	ReadData(reinterpret_cast<char *>(&arg), sizeof(char)*iLen);
	return *this;
};
T_Packet&     T_Packet::operator << (T_Packet& arg)
{
	unsigned short type = arg.GetID();
	unsigned short size = arg.GetSize();

	WriteData(reinterpret_cast<char *>(&type), sizeof(unsigned short));
	WriteData(reinterpret_cast<char *>(&size), sizeof(unsigned short));
	WriteData(reinterpret_cast<char *>(&arg.m_pstrWritePosition), size - 4);
	return *this;
};
T_Packet&     T_Packet::operator >> (T_Packet& arg)
{
	int type, size;
	char buffer[4096] = { 0, };
	ReadData(reinterpret_cast<char *>(&type), sizeof(unsigned short));
	ReadData(reinterpret_cast<char *>(&size), sizeof(unsigned short));
	ReadData(reinterpret_cast<char *>(&arg.m_pstrWritePosition), size - 4);

	arg.SetID(type);
	arg.WriteData(buffer, size - 4);
	return *this;
};
void T_Packet::Clear()
{
	ZeroMemory(m_strPacketBuffer, PACKETBUFFERSIZE);
	m_PacketHeader.len = (WORD*)m_strPacketBuffer + 0;
	m_PacketHeader.type = (WORD*)m_strPacketBuffer + 2;
	//m_pstrWritePosition = &m_strPacketBuffer[4];
	//m_pstrReadPosition = &m_strPacketBuffer[4];
	m_pstrWritePosition = &m_strPacketBuffer[6];
	m_pstrReadPosition = &m_strPacketBuffer[6];
	m_iReceivedSize = 0;
	*m_PacketHeader.len = 4;
}
T_Packet::T_Packet(void)
{
	Clear();
	SetID(0);
	/*
	m_uPacket.ph.type = 0;
	m_uPacket.ph.len = 0;
	m_pstrWritePosition = m_uPacket.msg;
	*/
};
T_Packet::T_Packet(unsigned short type)
{
	Clear();
	SetID(type);
	/*
	m_uPacket.ph.type = type;
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_pstrWritePosition = m_uPacket.msg;
	*/
};
T_Packet::~T_Packet(void)
{
}


