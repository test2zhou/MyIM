// D:\GitHub\MyIM\server\CS_ServerMng.cpp : 实现文件
//

#include "stdafx.h"
#include "CS_ServerMng.h"
#include "CS_PacketHelper.h"
#include "CS_Protocol.h"
#include "../EIM02Dlg.h"

// CServerMng

IMPLEMENT_DYNCREATE(CServerMng, CWinThread)

CServerMng::CServerMng()
:m_bLoginFlag(FALSE),
m_bConnectFlag(FALSE),
m_nFD(-1)
{
}

CServerMng::~CServerMng()
{
}

BOOL CServerMng::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CServerMng::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServerMng, CWinThread)
END_MESSAGE_MAP()


// CServerMng 消息处理程序

bool CServerMng::tryConnect(std::string ip, int port) {
	if (m_bConnectFlag)
		return TRUE;

	m_nFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_nFD) {
		AfxMessageBox("create socket failed.");
		return FALSE;
	}

	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	int ret = connect(m_nFD, (PSOCKADDR)&sin, sizeof(sin));
	if (ret == SOCKET_ERROR) {
		shutdown(m_nFD, SD_BOTH);
		closesocket(m_nFD);
		AfxMessageBox("connect server failed.");
		return FALSE;
	}
	m_bConnectFlag = true;
	return TRUE;
}

bool CServerMng::tryLogin(std::string strAccount, std::string strPasswd) {
	if (!m_bConnectFlag) {
		CEIM02Dlg* m_pMainTop = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;
		std::string &ip = m_pMainTop->m_config.m_strIP;
		if (!tryConnect(ip, m_pMainTop->m_config.m_nPort))
			return FALSE;
	}
	
	CPacket *p = CS_PacketHelper::createLogin(strAccount, strPasswd);
	
	return TRUE;
}

bool CServerMng::sendMessage(const char* msg, size_t len, int type) {
	
	return FALSE;
}

void CServerMng::requestInterest() {

}

void CServerMng::stop() {
	if (m_bConnectFlag) {
		m_bConnectFlag = FALSE;
		shutdown(m_nFD, SD_BOTH);
		closesocket(m_nFD);
	}
}