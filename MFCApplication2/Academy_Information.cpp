// Academy_Information.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Information.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "MFCApplication2Dlg.h"


// CAcademy_Information �Ի���

IMPLEMENT_DYNAMIC(CAcademy_Information, CDialogEx)

CAcademy_Information::CAcademy_Information(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy_Information::IDD, pParent)
	, m_Academy_Information_id(_T(""))
	, m_Academy_Information_name(_T(""))
	, m_Academy_Information_password(_T(""))
{

}

CAcademy_Information::~CAcademy_Information()
{
}

void CAcademy_Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_Academy_id, m_Academy_id);
	DDX_Text(pDX, IDC_Academy_Information_id, m_Academy_Information_id);
	DDX_Text(pDX, IDC_Academy_Information_name, m_Academy_Information_name);
	DDX_Text(pDX, IDC_Academy_Information_password, m_Academy_Information_password);
}


BEGIN_MESSAGE_MAP(CAcademy_Information, CDialogEx)
	ON_BN_CLICKED(IDC_Academy_Information_save, &CAcademy_Information::OnBnClickedAcademyInformationsave)
	ON_BN_CLICKED(IDC_Academy_Down, &CAcademy_Information::OnBnClickedAcademyDown)
END_MESSAGE_MAP()


// CAcademy_Information ��Ϣ�������


BOOL CAcademy_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Academy_Information_id = temp;

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from my_user where type='2' and id='%s'"), m_Academy_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		_variant_t name;
		name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
		m_Academy_Information_password = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("password"));
		if (name.vt == VT_NULL)
		{
			m_Academy_Information_name.Format(_T(""));
		}
		else m_Academy_Information_name = (CString)name;
	}

	UpdateData(false);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAcademy_Information::OnBnClickedAcademyInformationsave()
{
	UpdateData();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("update my_user set name='%s',password='%s' where type='2' and id='%s'"), m_Academy_Information_name, m_Academy_Information_password, m_Academy_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	MessageBox(_T("����ɹ�"));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAcademy_Information::OnBnClickedAcademyDown()
{
	CAcademy_Information::OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);

	CMFCApplication2Dlg dlg;
	dlg.DoModal();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
