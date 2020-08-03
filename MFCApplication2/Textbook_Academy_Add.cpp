// Textbook_Academy_Add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy_Add.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Academy_Add �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Academy_Add, CDialogEx)

CTextbook_Academy_Add::CTextbook_Academy_Add(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Academy_Add::IDD, pParent)
	, m_Textbook_Academy_Add_id(_T(""))
	, m_Textbook_Academy_Add_name(_T(""))
	, m_Textbook_Academy_Add_password(_T(""))
{

}

CTextbook_Academy_Add::~CTextbook_Academy_Add()
{
}

void CTextbook_Academy_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Textbook_Academy_Add_id, m_Textbook_Academy_Add_id);
	DDX_Text(pDX, IDC_Textbook_Academy_name, m_Textbook_Academy_Add_name);
	DDX_Text(pDX, IDC_Textbook_Academy_Add_password, m_Textbook_Academy_Add_password);
}


BEGIN_MESSAGE_MAP(CTextbook_Academy_Add, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Academy_Add, &CTextbook_Academy_Add::OnBnClickedTextbookAcademyAdd)
END_MESSAGE_MAP()


// CTextbook_Academy_Add ��Ϣ�������


void CTextbook_Academy_Add::OnBnClickedTextbookAcademyAdd()
{
	UpdateData();
	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	if (m_Textbook_Academy_Add_id.IsEmpty() || m_Textbook_Academy_Add_name.IsEmpty() || m_Textbook_Academy_Add_password.IsEmpty())
	{
		MessageBox(_T("����д������ѧԺ��Ϣ!"));
	}
	else
	{
		CString strSql;
		strSql.Format(_T("select * from my_user where id='%s'"), m_Textbook_Academy_Add_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("�ñ���Ѵ��ڣ����������룡"));
		}
		else
		{
			strSql.Format(_T("insert into my_user(id,password,type,state,name) values('%s','%s','2','1','%s')"), m_Textbook_Academy_Add_id, m_Textbook_Academy_Add_password, m_Textbook_Academy_Add_name);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			CTextbook_Academy_Add::OnOK();

			MessageBox(_T("��ӳɹ�!"));
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
