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
WORD Packet::GetID()
{
	return *m_PacketHeader.type;
}
WORD Packet::GetSize()
{
	return *m_PacketHeader.len;
}
char* Packet::GetData()
{
	return m_strPacketBuffer;
}
int Packet::GetDataSize()
{
	return m_iReceivedSize;
}
void Packet::ReadData(void* buffer, int iSize)
{
	::CopyMemory(buffer, m_pstrReadPosition, iSize);
	m_pstrReadPosition += iSize;
};
void Packet::WriteData(void* buffer, int iSize)
{
	if (m_iReceivedSize >= PACKETBUFFERSIZE - 4)
	{
		// ����
	}
	*m_PacketHeader.len += iSize;
	CopyMemory(m_pstrWritePosition, buffer, iSize);
	// 1���� �迭�� �ּҰ� �̵�
	m_pstrWritePosition += iSize;
	// ���� �������� ����Ʈ �뷮
	m_iReceivedSize += iSize;
};
Packet& Packet::SetID(unsigned short ID)
{
	*m_PacketHeader.type = ID;
	return *this;
};
// ��Ŷ�� ������ �� sum = a.v + b.v + c.v + d.v + e.v;
Packet& Packet::operator << (int arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
};
// ��Ŷ���� �����͸� ������ ��
Packet&  Packet::operator >> (int& arg)
{
	ReadData(&arg, sizeof(int));
	return *this;
};

Packet&     Packet::operator << (DWORD arg) {
	WriteData(&arg, sizeof(DWORD));
	return *this;
};
Packet&     Packet::operator >> (DWORD& arg) {
	ReadData(&arg, sizeof(DWORD));
	return *this;
};

Packet&     Packet::operator << (bool arg) {
	WriteData(&arg, sizeof(bool));
	return *this;
};
Packet&     Packet::operator >> (bool& arg) {
	ReadData(&arg, sizeof(bool));
	return *this;
};

Packet&     Packet::operator << (unsigned short arg) {
	WriteData(&arg, sizeof(unsigned short));
	return *this;
};
Packet&     Packet::operator >> (unsigned short& arg) {
	ReadData(&arg, sizeof(unsigned short));
	return *this;
};

Packet&     Packet::operator << (float arg) {
	WriteData(&arg, sizeof(float));
	return *this;
};
Packet&     Packet::operator >> (float& arg) {
	ReadData(&arg, sizeof(float));
	return *this;
};

Packet&     Packet::operator << (char* arg)
{
	int iLen = sizeof(char)*strlen(arg);
	WriteData(&arg, iLen);
	return *this;
};
Packet&     Packet::operator >> (char* arg)
{
	int iLen = sizeof(char)*strlen(this->m_pstrReadPosition);
	ReadData(&arg, sizeof(char)*iLen);
	return *this;
};
Packet&     Packet::operator << (Packet& arg)
{
	unsigned short type = arg.GetID();
	unsigned short size = arg.GetSize();

	WriteData(&type, sizeof(unsigned short));
	WriteData(&size, sizeof(unsigned short));
	WriteData(&arg.m_pstrWritePosition, size - 4);
	return *this;
};
Packet&     Packet::operator >> (Packet& arg)
{
	int type, size;
	char buffer[4096] = { 0, };
	ReadData(&type, sizeof(unsigned short));
	ReadData(&size, sizeof(unsigned short));
	ReadData(&buffer, size - 4);

	arg.SetID(type);
	arg.WriteData(buffer, size - 4);
	return *this;
};
void Packet::Clear()
{
	ZeroMemory(m_strPacketBuffer, PACKETBUFFERSIZE);
	m_PacketHeader.len = (WORD*)m_strPacketBuffer + 0;
	m_PacketHeader.type = (WORD*)m_strPacketBuffer + 2;
	m_pstrWritePosition = &m_strPacketBuffer[4];
	m_pstrReadPosition = &m_strPacketBuffer[4];
	m_iReceivedSize = 0;
	*m_PacketHeader.len = 4;
}
Packet::Packet(void)
{
	Clear();
	SetID(0);
};
Packet::Packet(unsigned short type)
{
	Clear();
	SetID(type);
};
Packet::~Packet(void)
{
}


