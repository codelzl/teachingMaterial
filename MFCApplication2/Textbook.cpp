// Textbook.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook.h"
#include "afxdialogex.h"


// Textbook �Ի���

IMPLEMENT_DYNAMIC(CTextbook, CDialogEx)

CTextbook::CTextbook(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook::IDD, pParent)
{

}

CTextbook::~CTextbook()
{
}

void CTextbook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Tab, m_Textbook_Tab);
}


BEGIN_MESSAGE_MAP(CTextbook, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_Textbook_Tab, &CTextbook::OnSelchangeTextbookTab)
END_MESSAGE_MAP()


// Textbook ��Ϣ�������


BOOL CTextbook::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);

	m_Textbook_Tab.InsertItem(0, _T("�û���Ϣ"));
	m_Textbook_Tab.InsertItem(1, _T("��ʦ��Ϣ"));
	m_Textbook_Tab.InsertItem(2, _T("�̲Ĺ���"));
	m_Textbook_Tab.InsertItem(3, _T("�û�����"));
	m_Textbook_Tab.InsertItem(4, _T("�������"));
	m_Textbook_Tab.InsertItem(5, _T("�������"));

	m_Information.Create(IDD_Textbook_Information, &m_Textbook_Tab);
	m_Teacher.Create(IDD_Textbook_Teacher, &m_Textbook_Tab);
	m_Textbook.Create(IDD_Textbook_Textbook, &m_Textbook_Tab);
	m_Academy.Create(IDD_Textbook_Academy, &m_Textbook_Tab);
	m_Notice.Create(IDD_Textbook_Notice, &m_Textbook_Tab);
	m_Verify.Create(IDD_Textbook_Verify, &m_Textbook_Tab);

	CRect rc;
	m_Textbook_Tab.GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 2;
	rc.left += 2;
	rc.right -= 3;

	m_Information.MoveWindow(&rc);
	m_Teacher.MoveWindow(&rc);
	m_Textbook.MoveWindow(&rc);
	m_Academy.MoveWindow(&rc);
	m_Notice.MoveWindow(&rc);
	m_Verify.MoveWindow(&rc);

	/*m_Information.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);
	m_Teacher.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);
	m_Textbook.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);
	m_Academy.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);
	m_Notice.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);
	m_Verify.SetWindowPos(NULL, 2, 21, 530, 277, SWP_SHOWWINDOW);*/

	m_Information.ShowWindow(true);
	m_Teacher.ShowWindow(false);
	m_Textbook.ShowWindow(false);
	m_Academy.ShowWindow(false);
	m_Notice.ShowWindow(false);
	m_Verify.ShowWindow(false);

	m_Textbook_Tab.SetCurSel(0);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTextbook::OnSelchangeTextbookTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_Textbook_Tab.GetCurSel())
	{
	case 0:
		m_Information.ShowWindow(true);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Academy.ShowWindow(false);
		m_Notice.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 1:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(true);
		m_Teacher.OnInitDialog();//ˢ��
		m_Textbook.ShowWindow(false);
		m_Academy.ShowWindow(false);
		m_Notice.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 2:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(true);
		m_Academy.ShowWindow(false);
		m_Notice.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 3:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Academy.ShowWindow(true);
		m_Notice.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 4:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Academy.ShowWindow(false);
		m_Notice.ShowWindow(true);
		m_Verify.ShowWindow(false);
		break;
	case 5:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Academy.ShowWindow(false);
		m_Notice.ShowWindow(false);
		m_Verify.ShowWindow(true);
		break;
	}
	*pResult = 0;
}
