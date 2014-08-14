// D:\GitHub\MyIM\server\CS_ServerMng.cpp : 实现文件
//

#include "stdafx.h"
#include "CS_ServerMng.h"
#include "CS_PacketHelper.h"
#include "CS_Protocol.h"
#include "CS_Packet.h"
#include "../EIM02Dlg.h"
#include <assert.h>

// CServerMng

static bool g_bKeepAlive = false;
static CServerMng* g_pInstance = nullptr;
using namespace std;

CServerMng* CServerMng::getInstance() {
	if (g_pInstance)
		return g_pInstance;

	g_pInstance = new CServerMng;
	return g_pInstance;
}

CServerMng::CServerMng()
:m_plistSend(nullptr),
m_plistRecv(nullptr),
m_hThread(nullptr)
{
	::InitializeCriticalSection(&m_sendLock);
	::InitializeCriticalSection(&m_recvLock);
}

CServerMng::~CServerMng()
{
	::DeleteCriticalSection(&m_sendLock);
	::DeleteCriticalSection(&m_recvLock);

}

bool CServerMng::TryLogin(std::string strAccount, std::string strPasswd) {
	if (!m_hThread) {
		m_hThread = CreateThread(NULL, 0, NetWork, this, 0, &m_tid);
		if (m_hThread == nullptr) {
			::EM_Error(_T("send Thread creating failed."), 0);
			return FALSE;
		}
	}
	
	CPacket *p = CS_PacketHelper::createLogin(strAccount, strPasswd);
	if (!p)
		return FALSE;

	SendPacket(p);
	return TRUE;
}

DWORD WINAPI CServerMng::NetWork(LPVOID lParam) {
	g_bKeepAlive = true;
	CEIM02Dlg *pDlg = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;
	CServerMng * pMng = (CServerMng*)lParam;
	std::string &ip = pDlg->m_config.m_strIP;
	int port = pDlg->m_config.m_nPort;

	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fd) {
		fprintf(stderr, "create socket failed.");
		return FALSE;
	}

	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	int ret = connect(fd, (PSOCKADDR)&sin, sizeof(sin));
	if (ret == SOCKET_ERROR) {
		shutdown(fd, SD_BOTH);
		closesocket(fd);
		fprintf(stderr, "connect server failed.");
		return FALSE;
	}

	while(g_bKeepAlive) {
		list<CPacket*> *listPacket;
		::EnterCriticalSection(&pMng->m_sendLock);
		listPacket = pMng->m_plistSend;
		pMng->m_plistSend = nullptr;
		::LeaveCriticalSection(&pMng->m_sendLock);
		CPacket *p;
		if (listPacket) {
			for (auto it = listPacket->begin(); it != listPacket->end(); it++) {
				p = *it;
				int n = send(fd, p->getBuffer(), p->getLength(), 0);
				if (n < 0) {
					if (errno == EAGAIN|| errno == EINTR) {
						n = 0;
					} else {
						AfxMessageBox("send data to server failed.");
						shutdown(fd, SD_BOTH);
						closesocket(fd);
						return FALSE;
					}
				}
				if (n == p->getLength()) {
					SAFE_DELETE(p);
				} else {
					// : TODO
					assert(false);
				}
			}
		}

		int len = 0;
		char h[2] = {0};
		char *b;
		while(1) {
			memset(h, 0, 2);
			int n = recv(fd, h, len, 0);
			if (n < 0) {
				if (errno == EAGAIN || errno == EINTR) {
					break;
				} else {
					shutdown(fd, SD_BOTH);
					closesocket(fd);
					return FALSE;
				}
			} else if (n == 0) {
				break;
			}
			len = h[0] << 8 | h[1];
			b = (char*)malloc(len);
			n = recv(fd, b, len, 0);
			if (n < 0) {
				if (errno == EAGAIN || errno == EINTR) {
					assert(false);
				} else {
					shutdown(fd, SD_BOTH);
					closesocket(fd);
					return FALSE;
				}
			} else if (n == 0) {
				break;
			}
			p = CPacket::Create(b, (UINT32)len);
			::EnterCriticalSection(&pMng->m_recvLock);
			pDlg->SendMessage(WM_CSMSG, (WPARAM)p, (LPARAM)nullptr);
			::LeaveCriticalSection(&pMng->m_recvLock);
		}		
	}
	return FALSE;
}

void CServerMng::SendPacket(CPacket* p) {
	::EnterCriticalSection(&m_sendLock);
	if (!m_plistSend)
		m_plistSend = new list<CPacket*>();

	m_plistSend->push_back(p);
	::LeaveCriticalSection(&m_sendLock);
}
