#ifndef __CS_PACKETHELPER_H__
#define __CS_PACKETHELPER_H__

class CPacket;
class CS_PacketHelper
{
public:
	CS_PacketHelper(void);
	~CS_PacketHelper();

	static CPacket* createLogin(std::string&, std::string&);


};

#endif//__CS_PACKETHELPER_H__