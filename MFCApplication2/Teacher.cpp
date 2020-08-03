// Teacher.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher.h"
#include "afxdialogex.h"


// CTeacher �Ի���

IMPLEMENT_DYNAMIC(CTeacher, CDialogEx)

CTeacher::CTeacher(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher::IDD, pParent)
{

}

CTeacher::~CTeacher()
{
}

void CTeacher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Teacher_Tab, m_Teacher_tab);
}


BEGIN_MESSAGE_MAP(CTeacher, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_Teacher_Tab, &CTeacher::OnSelchangeTeacherTab)
END_MESSAGE_MAP()


// CTeacher ��Ϣ�������


BOOL CTeacher::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Teacher_tab.InsertItem(0, _T("�ҵ���Ϣ"));
	m_Teacher_tab.InsertItem(1, _T("�̲�����"));
	m_Teacher_tab.InsertItem(2, _T("�鿴����"));

	m_Information.Create(IDD_Teacher_Information, &m_Teacher_tab);
	m_Demand.Create(IDD_Teacher_Demand, &m_Teacher_tab);
	m_Subscriptions.Create(IDD_Teacher_Subscriptions, &m_Teacher_tab);
	
	CRect rc;
	m_Teacher_tab.GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 2;
	rc.left += 2;
	rc.right -= 3;

	m_Information.MoveWindow(&rc);
	m_Demand.MoveWindow(&rc);
	m_Subscriptions.MoveWindow(&rc);

	/*m_Information.SetWindowPos(NULL, 2, 21, 840, 458, SWP_SHOWWINDOW);
	m_Demand.SetWindowPos(NULL, 2, 21, 840, 458, SWP_SHOWWINDOW);
	m_Subscriptions.SetWindowPos(NULL, 2, 21, 840, 458, SWP_SHOWWINDOW);*/

	m_Information.ShowWindow(true);
	m_Demand.ShowWindow(false);
	m_Subscriptions.ShowWindow(false);

	m_Teacher_tab.SetCurSel(0);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTeacher::OnSelchangeTeacherTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	switch (m_Teacher_tab.GetCurSel())
	{
	case 0:
		m_Information.ShowWindow(true);
		m_Demand.ShowWindow(false);
		m_Subscriptions.ShowWindow(false);
		break;
	case 1:
		m_Information.ShowWindow(false);
		m_Demand.ShowWindow(true);
		m_Subscriptions.ShowWindow(false);
		break;
	case 2:
		m_Information.ShowWindow(false);
		m_Demand.ShowWindow(false);
		m_Subscriptions.ShowWindow(true);
		m_Subscriptions.OnInitDialog();
		break;
	}
	*pResult = 0;
}
