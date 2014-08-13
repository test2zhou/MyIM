#include "stdafx.h"
#include "CS_Packet.h"
#include "CS_Protocol.h"


CPacket::CPacket(UINT16 protocol, UINT32 len)
:m_sProtocol(protocol)
{
	m_pBuff = (char *)calloc(1, len);
	m_pCurr = m_pBuff;
	m_nLen = len;
	m_cVersion = CS_VERSION;

	writeUInt(m_sProtocol);
	writeUInt(m_cVersion);
}


CPacket::~CPacket(void)
{
	if (m_pBuff) {
		free(m_pBuff);
		m_pBuff = nullptr;
	}
}


void CPacket::writeString(std::string& data) {
	UINT16 len = data.length();
	writeUInt(len);
	writeData((void *)data.c_str(), len);
}

void CPacket::readString(std::string& str) {
	UINT16 len = 0;
	readUInt(len);
	if (len == 0)
		str = "";
	else {
		char* p = (char *)calloc(1, len);
		readData(p, len);
		str.append(p, len);
		free(p);
	}
}

void CPacket::writeData(void* data, size_t s) {
	if (m_pCurr + s > m_pBuff + m_nLen) {
		if (!expand(s))
			return;
	}
	memcpy(m_pCurr, data, s);
	m_pCurr += s;
}

void CPacket::readData(void* data, size_t s) {
	if (m_pCurr + s > m_pBuff + m_nLen) {
		return;
	}

	memcpy(data, m_pCurr, s);
	m_pCurr += s;
}

bool CPacket::expand(size_t sz) {
	UINT32 ns = (sz + m_nLen) * 2;
	char* p = (char *)calloc(1, ns);
	if (p == nullptr)
		return FALSE;

	UINT32 l =  m_pCurr - m_pBuff;
	memcpy(p, m_pBuff, l);
	free(m_pBuff);

	m_pBuff = p;
	m_pCurr = m_pBuff + l;
	m_nLen = ns;
	return TRUE;
}