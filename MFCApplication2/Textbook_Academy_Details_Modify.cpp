// Textbook_Academy_Details_Modify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy_Details_Modify.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Academy_Details_Modify �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Academy_Details_Modify, CDialogEx)

CTextbook_Academy_Details_Modify::CTextbook_Academy_Details_Modify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Academy_Details_Modify::IDD, pParent)
	, m_Textbook_Academy_Details_Modify_name(_T(""))
	, m_Textbook_Academy_Details_Modify_password(_T(""))
	, m_Textbook_Academy_Details_id(_T(""))
{

}

CTextbook_Academy_Details_Modify::~CTextbook_Academy_Details_Modify()
{
}

void CTextbook_Academy_Details_Modify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Textbook_Academy_Details_Modify_name, m_Textbook_Academy_Details_Modify_name);
	DDX_Text(pDX, IDC_Textbook_Academy_Details_Modify_password, m_Textbook_Academy_Details_Modify_password);
	DDX_Text(pDX, IDC_Textbook_Academy_Details_Modify_id, m_Textbook_Academy_Details_id);
}


BEGIN_MESSAGE_MAP(CTextbook_Academy_Details_Modify, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_Modify_Save, &CTextbook_Academy_Details_Modify::OnBnClickedTextbookAcademyDetailsModifySave)
END_MESSAGE_MAP()


// CTextbook_Academy_Details_Modify ��Ϣ�������


BOOL CTextbook_Academy_Details_Modify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from teacher where id='%s'"), temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	_variant_t id, name, password;
	CString str_id, str_name, str_password;
	int i = 0;

	id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
	name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
	password = CDBO.m_pRecordset->GetCollect(_variant_t("password"));

	m_Textbook_Academy_Details_id = (CString)id;
	if (name.vt == VT_NULL)
	{
		m_Textbook_Academy_Details_Modify_name.Format(_T(""));
	}
	else
	{
		m_Textbook_Academy_Details_Modify_name = (CString)name;
	}
	m_Textbook_Academy_Details_Modify_password = (CString)password;

	UpdateData(false);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTextbook_Academy_Details_Modify::OnBnClickedTextbookAcademyDetailsModifySave()
{
	UpdateData();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("update teacher set name='%s',password='%s' where id='%s'"), m_Textbook_Academy_Details_Modify_name, m_Textbook_Academy_Details_Modify_password, m_Textbook_Academy_Details_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	MessageBox(_T("�޸ĳɹ���"));

	CTextbook_Academy_Details_Modify::OnOK();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
