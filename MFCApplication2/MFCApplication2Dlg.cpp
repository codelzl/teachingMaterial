
// MFCApplication2Dlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication2Dlg �Ի���



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


// CMFCApplication2Dlg ��Ϣ�������

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	CString str[3] = { _T("��ʦ�û�"), _T("ѧԺ�û�"), _T("�̲Ŀ��û�") };//��ʼ����Ͽ�
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
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		_variant_t word, time;
		if (!CDBO.m_pRecordset->adoEOF)
		{
			CDBO.m_pRecordset->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			word = CDBO.m_pRecordset->GetCollect(_variant_t("mainword"));
			time = CDBO.m_pRecordset->GetCollect(_variant_t("NOTICE_DATE"));
			//CDBO.m_pRecordset->MoveNext();
		}
		m_Login_Notice = (CString)word;
		m_Notice_Time = (CString)time;
		UpdateData(false);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedLoginInterfaceRegister()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMFCApplication2Dlg::OnOK();
	CRegister dlg;
	dlg.DoModal();
}


void CMFCApplication2Dlg::OnBnClickedLoginInterfaceLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (tag == 0)     //���ع���ʧ�ܣ����ܵ�½
	{
		if (m_login_type == 0)    //��ʦ��½
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("���ӳ���"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from teacher where id='%s' and password='%s'"), c_user, c_password);

			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("�û��������벻��Ϊ��"), _T("�û���¼��Ϣ"));
				return;
			}
			else if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("�û�������������!"), _T("����"));
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
		else if (m_login_type == 1)   //ѧԺ�û���¼
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("���ӳ���"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from my_user where type='2' and id='%s' and password='%s'"), c_user, c_password);

			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("�û��������벻��Ϊ��"), _T("�û���¼��Ϣ"));
				return;
			}
			if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("�û�������������!"), _T("����"));
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
		else if (m_login_type == 2)   //�̲Ŀ��û�
		{
			UpdateData();
			CString c_user, c_password;
			c_user = m_user;
			c_password = m_password;
			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			if (con == false)
			{
				MessageBox(_T("���ӳ���"));
				return;
			}

			CString strSql;
			strSql.Format(_T("select * from my_user where type='3' and id='%s' and password='%s' "), c_user, c_password);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			if (m_user.IsEmpty() || m_password.IsEmpty())
			{
				MessageBox(_T("�û��������벻��Ϊ��"), _T("�û���¼��Ϣ"));
				return;
			}
			if (CDBO.m_pRecordset->adoEOF)
			{
				MessageBox(_T("�û�������������!"), _T("����"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_login_interface.GetCurSel();
	if (nIndex != CB_ERR)
	{
		m_login_type = m_login_interface.GetItemData(nIndex);
	}
}


void CMFCApplication2Dlg::OnEnChangeLoginInterfaceEditNumber()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
