#include "stdafx.h"
#include "CS_PacketHelper.h"
#include "CS_Packet.h"
#include "CS_Protocol.h"

CS_PacketHelper::CS_PacketHelper(void) {

}

CS_PacketHelper::~CS_PacketHelper() {

}

CPacket* CS_PacketHelper::createLogin(std::string& acc, std::string& pass) {
	CPacket *p = new CPacket(PT_LOGIN);
	p->writeString(acc);
	p->writeString(pass);
	return p;
}
	



