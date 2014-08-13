#ifndef __CS_SERVERMNG_H__
#define __CS_SERVERMNG_H__

#include <string>
#include <list>

enum _emMsgType { 
	_emGroupMessage,
	_emPersonMessage,

};


// CServerMng

class CPacket;
class CServerMng : public CWinThread
{
	DECLARE_DYNCREATE(CServerMng)

protected:
	CServerMng();           // 动态创建所使用的受保护的构造函数
	virtual ~CServerMng();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	bool tryConnect(std::string ip, int port);
	bool tryLogin(std::string strAccount, std::string strPasswd);
	bool sendMessage(const char* msg, size_t len, int type);
	void requestInterest();
	void stop();

protected:
	DECLARE_MESSAGE_MAP()

private:

	bool m_bLoginFlag;
	bool m_bConnectFlag;
	int m_nFD;

	
	std::list<CPacket *> m_listSend;
	std::list<CPacket *> m_listRecv;
};






#endif// __CS_SERVERMNG_H__