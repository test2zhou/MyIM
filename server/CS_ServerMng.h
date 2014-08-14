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
class CServerMng 
{
	CServerMng();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CServerMng();

public:

	static CServerMng* getInstance();

	bool TryLogin(std::string strAccount, std::string strPasswd);
	void SendPacket(CPacket*);

	static DWORD WINAPI NetWork(LPVOID lParam);

	std::list<CPacket *> *m_plistSend;
	std::list<CPacket *> *m_plistRecv;

private:

	bool m_bLoginFlag;

	CRITICAL_SECTION m_sendLock;
	CRITICAL_SECTION m_recvLock;
	
	HANDLE m_hThread;
	DWORD m_tid;
};






#endif// __CS_SERVERMNG_H__