
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "Register.h"
#include "Teacher.h"
#include "ADOConn.h"
#include "Academy.h"
#include "Textbook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
	, m_login_type(0)
	, m_user(_T(""))
	, m_password(_T(""))
	, m_Login_Notice(_T(""))
	, tag(0)
	, m_Notice_Time(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_login_interface);
	//  DDX_Control(pDX, IDC_Login_Interface_EDIT_Password, m_password);
	//  DDX_Control(pDX, IDC_Login_Interface_EDIT_Number, m_user);
	DDX_Text(pDX, IDC_Login_Interface_EDIT_Number, m_user);
	DDX_Text(pDX, IDC_Login_Interface_EDIT_Password, m_password);
	DDX_Text(pDX, IDC_Login_Notice, m_Login_Notice);
	DDX_Text(pDX, IDC_Notice_Time, m_Notice_Time);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Login_Interface_Register, &CMFCApplication2Dlg::OnBnClickedLoginInterfaceRegister)
	ON_BN_CLICKED(IDC_Login_Interface_Login, &CMFCApplication2Dlg::OnBnClickedLoginInterfaceLogin)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication2Dlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_Login_Interface_EDIT_Number, &CMFCApplication2Dlg::OnEnChangeLoginInterfaceEditNumber)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	CString str[3] = { _T("教师用户"), _T("学院用户"), _T("教材库用户") };//初始化组合框
	int nIndex;
	for (int i = 0; i<3; i++)
	{
		nIndex = m_login_interface.AddString(str[i]);
		m_login_interface.SetItemData(nIndex, i);
	}
	m_login_interface.SetCurSel(1);
	m_login_type = 0;

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from notice order by id desc"));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	if (NULL == CDBO.m_pRecordset)
	{
		tag++;
		MessageBox(_T("查询数据出现错误"));
	}
	else
	{
		_variant_t word, time;
		if (!CDBO.m_pRecordset->adoEOF)
		{
			CDBO.m_pRecordset->MoveFirst(); //记录集指针移动到查询结果集的前面
			word = CDBO.m_pRecordset->GetCollect(_variant_t("mainword"));
			time = CDBO.m_pRecordset->GetCollect(_variant_t("NOTICE_DATE"));
			//CDBO.m_pRecordset->MoveNext();
		}
		m_Login_Notice = (CString)word;
		m_Notice_Time = (CString)time;
		UpdateData(false);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedLoginInterfaceRegister()
{
	// TODO:  在此添加控件通知处理程序代码
	CMFCApplication2Dlg::OnOK();
	CRegister dlg;
	dlg.DoModal();
}


void CMFCApplication2Dlg::OnBnClickedLoginInterfaceLogin()
{
	// TODO:  在此添加控件通知处理程序代码

	if (tag == 0)     //加载公告失败，不能登陆
	{
		if (m_login_type == 0)    //教师登陆
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("连接出错"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from teacher where id='%s' and password='%s'"), c_user, c_password);

			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("用户名或密码不能为空"), _T("用户登录信息"));
				return;
			}
			else if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("用户名或密码有误!"), _T("错误"));
				m_user = "";
				m_password = "";
				UpdateData(false);
			}
			else
			{
				temp = c_user;
				CMFCApplication2Dlg::OnOK();
				//CDBO.m_pRecordset->Close();
				CTeacher dlg;
				dlg.DoModal();
			}

		}
		else if (m_login_type == 1)   //学院用户登录
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("连接出错"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from my_user where type='2' and id='%s' and password='%s'"), c_user, c_password);

			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("用户名或密码不能为空"), _T("用户登录信息"));
				return;
			}
			if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("用户名或密码有误!"), _T("错误"));
				m_user = "";
				m_password = "";
				UpdateData(false);
			}
			else
			{
				temp = c_user;
				//CDBO.m_pRecordset->Close();
				CMFCApplication2Dlg::OnOK();
				CAcademy dlg;
				dlg.DoModal();
			}

		}
		else if (m_login_type == 2)   //教材库用户
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("连接出错"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from my_user where type='3' and id='%s' and password='%s' "), c_user, c_password);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("用户名或密码不能为空"), _T("用户登录信息"));
				return;
			}
			if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("用户名或密码有误!"), _T("错误"));
				m_user = "";
				m_password = "";
				UpdateData(false);
			}
			else
			{
				temp = c_user;
				//CDBO.m_pRecordset->Close();
				CMFCApplication2Dlg::OnOK();
				CTextbook dlg;
				dlg.DoModal();
			}
		}
	}
}


void CMFCApplication2Dlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	int nIndex = m_login_interface.GetCurSel();
	if (nIndex != CB_ERR)
	{
		m_login_type = m_login_interface.GetItemData(nIndex);
	}
}


void CMFCApplication2Dlg::OnEnChangeLoginInterfaceEditNumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
