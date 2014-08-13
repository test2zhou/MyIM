#include "StdAfx.h"
#include "EIM02Dlg.h"
#include "thirdpartclass/INI.h"
#include "freeeim_config.h"
#include "em/EM_UserInfo.h"

#define CONFIG_INI "freeeim.ini"

FreeEIM_Config::FreeEIM_Config()
{
	m_strDisplayName = "";
	m_strGroup = "";
	m_strIP = "10.121.9.10";
	m_nPort = 8888;

	m_pUserInfo = NULL;
	ReadConfig();
}


FreeEIM_Config::~FreeEIM_Config()
{
	if (NULL != m_pUserInfo)
	{
		delete m_pUserInfo;
		m_pUserInfo = NULL;
	}
}


EM_UserInfo *FreeEIM_Config::GetUserInfo()
{
	m_pUserInfo = new EM_UserInfo((LPSTR)(LPCTSTR)m_strDisplayName, "male", (LPSTR)(LPCTSTR)m_strGroup);
	
	return m_pUserInfo;
}


void FreeEIM_Config::ReadConfig()
{
	// m_pMainTop = (CEIM02Dlg*)AfxGetMainWnd();
	m_pMainTop = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;
	// ����û������ļ�
/**/char szFileName[_MAX_PATH];
/**/m_pMainTop->GetProgramDirectory(szFileName);
/**/strcat(szFileName, CONFIG_INI);

	CIniReader iniReader(szFileName);

	if (iniReader.sectionExists("freeeim"))
	{
		// ��ǰ�û���
		m_strDisplayName = iniReader.getKeyValue("display", "freeeim");

		// ��ǰ����
		m_strGroup = iniReader.getKeyValue("group", "freeeim");

		m_strAccount = iniReader.getKeyValue("account", "freeeim");
		m_strPassWD = iniReader.getKeyValue("passwd", "freeeim");
		
		m_strIP = iniReader.getKeyValue("host", "freeeim");
		std::string strPort = iniReader.getKeyValue("port", "freeeim");
		m_nPort = strtoul(strPort.c_str(), NULL, 10);

	}	
	else // ���û�������ļ����½�һ��������ʹ��Ĭ����Ϣ
	{
		m_strDisplayName = GetComputerName();
		m_strGroup = FreeEIM_Default_Group;

		iniReader.setKey((LPCTSTR)m_strDisplayName, "display", "freeeim");
		iniReader.setKey((LPCTSTR)m_strGroup, "group", "freeeim");
	}
}


void FreeEIM_Config::SaveConfig()
{
	// m_pMainTop = (CEIM02Dlg*)AfxGetMainWnd();
	m_pMainTop = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;
	// ����û������ļ�
/**/char szFileName[_MAX_PATH];
/**/m_pMainTop->GetProgramDirectory(szFileName);
/**/strcat(szFileName, CONFIG_INI);

	CIniReader iniReader(szFileName);

	if (iniReader.sectionExists("freeeim"))
	{
		iniReader.setKey((LPCTSTR)m_strDisplayName, "display", "freeeim");
		iniReader.setKey((LPCTSTR)m_strGroup, "group", "freeeim");

		iniReader.setKey((LPCTSTR)m_strAccount, "account", "freeeim");
		iniReader.setKey((LPCTSTR)m_strPassWD, "passwd", "freeeim");
	}
}


CString FreeEIM_Config::GetDisplayName()
{
	return m_strDisplayName;
}


CString FreeEIM_Config::GetGroup()
{
	return m_strGroup;
}


CString FreeEIM_Config::GetComputerName()
{
	// m_pMainTop = (CEIM02Dlg*)AfxGetMainWnd();
	m_pMainTop = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;

	// ��ȡ�����������
	return m_pMainTop->GetComputerName();
}
