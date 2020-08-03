// Academy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy.h"
#include "afxdialogex.h"


// Academy �Ի���

IMPLEMENT_DYNAMIC(CAcademy, CDialogEx)

CAcademy::CAcademy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy::IDD, pParent)
{

}

CAcademy::~CAcademy()
{
}

void CAcademy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Academy_Tab, m_Academy_Tab);
}


BEGIN_MESSAGE_MAP(CAcademy, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_Academy_Tab, &CAcademy::OnSelchangeAcademyTab)
END_MESSAGE_MAP()


// Academy ��Ϣ�������


BOOL CAcademy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Academy_Tab.InsertItem(0, _T("ѧԺ��Ϣ"));
	m_Academy_Tab.InsertItem(1, _T("��ʦ����"));
	m_Academy_Tab.InsertItem(2, _T("�̲Ĳ�ѯ"));
	m_Academy_Tab.InsertItem(3, _T("�������"));

	m_Information.Create(IDD_Academy_Information, &m_Academy_Tab);
	m_Teacher.Create(IDD_Academy_Teacher, &m_Academy_Tab);
	m_Textbook.Create(IDD_Academy_Textbook, &m_Academy_Tab);
	m_Verify.Create(IDD_Academy_Verify, &m_Academy_Tab);

	CRect rc;
	m_Academy_Tab.GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 2;
	rc.left += 2;
	rc.right -= 3;

	m_Information.MoveWindow(&rc);
	m_Teacher.MoveWindow(&rc);
	m_Textbook.MoveWindow(&rc);
	m_Verify.MoveWindow(&rc);

	/*m_Information.SetWindowPos(NULL, 2, 21, 561, 291, SWP_SHOWWINDOW);
	m_Teacher.SetWindowPos(NULL, 2, 21, 561, 291, SWP_SHOWWINDOW);
	m_Textbook.SetWindowPos(NULL, 2, 21, 561, 291, SWP_SHOWWINDOW);
	m_Verify.SetWindowPos(NULL, 2, 21, 561, 291, SWP_SHOWWINDOW);*/

	m_Information.ShowWindow(true);
	m_Teacher.ShowWindow(false);
	m_Textbook.ShowWindow(false);
	m_Verify.ShowWindow(false);

	m_Academy_Tab.SetCurSel(0);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAcademy::OnSelchangeAcademyTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_Academy_Tab.GetCurSel())
	{
	case 0:
		m_Information.ShowWindow(true);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 1:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(true);
		m_Textbook.ShowWindow(false);
		m_Verify.ShowWindow(false);
		break;
	case 2:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(true);
		m_Verify.ShowWindow(false);
		break;
	case 3:
		m_Information.ShowWindow(false);
		m_Teacher.ShowWindow(false);
		m_Textbook.ShowWindow(false);
		m_Verify.ShowWindow(true);
		break;
	}
	*pResult = 0;
}
