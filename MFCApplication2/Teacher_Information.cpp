// Teacher_Information.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher_Information.h"
#include "afxdialogex.h"
#include "Teacher_Information_Modify.h"
#include "ADOConn.h"
#include "MFCApplication2Dlg.h"
#include "Teacher_Information.h"


// CTeacher_Information �Ի���

IMPLEMENT_DYNAMIC(CTeacher_Information, CDialogEx)

CTeacher_Information::CTeacher_Information(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher_Information::IDD, pParent)
	, m_Teacher_id(_T(""))
	, m_Teacher_Information_Type(_T(""))
	, m_Teacher_name(_T(""))
	, m_Teacher_Information_password(_T(""))
{

}

CTeacher_Information::~CTeacher_Information()
{
}

void CTeacher_Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Teacher_id, m_Teacher_id);
	DDX_Text(pDX, IDC_Teacher_Information_Type, m_Teacher_Information_Type);
	DDX_Text(pDX, IDC_Teacher_Information_name, m_Teacher_name);
	DDX_Text(pDX, IDC_Teacher_Information_password, m_Teacher_Information_password);
}


BEGIN_MESSAGE_MAP(CTeacher_Information, CDialogEx)
	ON_BN_CLICKED(IDC_Teacher_Information_save, &CTeacher_Information::OnBnClickedTeacherInformationsave)
	ON_BN_CLICKED(IDC_Teacher_Down, &CTeacher_Information::OnBnClickedTeacherDown)
END_MESSAGE_MAP()


// CTeacher_Information ��Ϣ�������

BOOL CTeacher_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Teacher_id = temp;

	m_Teacher_Information_Type.Format(_T("��ʦ�û�"));

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
	
	CString strSql;
	strSql.Format(_T("select * from teacher where id='%s'"), m_Teacher_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		_variant_t name;
		CString str_name;
		name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
		m_Teacher_Information_password = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("password"));
		if (name.vt == VT_NULL)
		{
			str_name.Format(_T(""));
		}
		else str_name = (CString)name;
		m_Teacher_name = str_name;
	}

	UpdateData(false);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CTeacher_Information::OnBnClickedTeacherInformationsave()
{
	UpdateData();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("update teacher set name='%s',password='%s' where id='%s'"), m_Teacher_name, m_Teacher_Information_password, m_Teacher_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	MessageBox(_T("����ɹ�"));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTeacher_Information::OnBnClickedTeacherDown()
{
	CTeacher_Information::OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);

	CMFCApplication2Dlg dlg;
	dlg.DoModal();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
