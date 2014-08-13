// UserSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EIM02.h"
#include "UserLoginDlg.h"
#include "em/EM_UserInfo.h"
#include "em/EM_UserLogin.h"
#include "em/EM_GroupInfo.h"
#include "EIM02Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserSettingDlg dialog


ZXY_UserLoginDlg::ZXY_UserLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ZXY_UserLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserSettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDI_USER_SETTING);

	m_pMainTop = NULL;
}

void ZXY_UserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserSettingDlg)
	//DDX_Control(pDX, IDC_COMBO1, m_cbGroup);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZXY_UserLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CUserSettingDlg)
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
	//ON_CBN_SELCHANGE(IDC_COMBO1, &ZXY_UserLoginDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &ZXY_UserLoginDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT7, &ZXY_UserLoginDlg::OnEnChangeEdit7)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserSettingDlg message handlers

BOOL ZXY_UserLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here

	// m_pMainTop = (CEIM02Dlg*)AfxGetMainWnd();
	m_pMainTop = (CEIM02Dlg*)AfxGetApp()->m_pMainWnd;

	SetDlgItemText(IDC_EDIT1, m_pMainTop->m_config.m_strDisplayName);
	// m_cbGroup.SetWindowText(m_pMainTop->m_config.m_strGroup);

	// 把现有的分组填写到下拉菜单中
	HTREEITEM hNextItem;
	HTREEITEM hChildItem = m_pMainTop->m_treeCtrlList.GetChildItem(TVI_ROOT);
	CString strItemText;

	for(;hChildItem != NULL; hChildItem = hNextItem)
	{
		strItemText = m_pMainTop->m_treeCtrlList.GetItemText(hChildItem);
		// m_cbGroup.AddString(strItemText);
		hNextItem = m_pMainTop->m_treeCtrlList.GetNextSiblingItem(hChildItem);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZXY_UserLoginDlg::OnOK()
{
	CString strName;
	CString strPassWd;

	GetDlgItemText(IDC_EDIT1, strName);
	GetDlgItemText(IDC_EDIT7, strPassWd);
	// m_cbGroup.GetWindowText(strGroup);

	if (strName.IsEmpty())
	{
		// 姓名不能为空
		MessageBox(_T("姓名不能为空"), _T("提示"), MB_OK);
		SetDlgItemText(IDC_EDIT1, m_pMainTop->m_config.m_strDisplayName);
		return;
	}

	if (strPassWd.IsEmpty())
	{
		// 姓名不能为空
		MessageBox(_T("请输入密码"), _T("提示"), MB_OK);
		SetDlgItemText(IDC_EDIT1, m_pMainTop->m_config.m_strDisplayName);
		return;
	}

	//if (strGroup.IsEmpty())
	//{
		// 分组不能为空
		// m_cbGroup.SetWindowText(m_pMainTop->m_config.m_strGroup);
		//MessageBox(_T("分组不能为空"), _T("提示"), MB_OK);
		//return;
	//}

	m_pMainTop->EM_LoginServer(strName, strPassWd);
	m_pMainTop->EM_ShowLoading();

	CDialog::OnOK();
}


// void ZXY_UserLoginDlg::OnCbnSelchangeCombo1()
// {
	// TODO: 在此添加控件通知处理程序代码
// }


void ZXY_UserLoginDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
}


void ZXY_UserLoginDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
}
