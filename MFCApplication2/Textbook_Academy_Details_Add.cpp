// Textbook_Academy_Details_Add.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy_Details_Add.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Academy_Details_Add 对话框

IMPLEMENT_DYNAMIC(CTextbook_Academy_Details_Add, CDialogEx)

CTextbook_Academy_Details_Add::CTextbook_Academy_Details_Add(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Academy_Details_Add::IDD, pParent)
	, m_Textbook_Academy_Details_Add_name(_T(""))
	, m_Textbook_Academy_Details_Add_password(_T(""))
{

}

CTextbook_Academy_Details_Add::~CTextbook_Academy_Details_Add()
{
}

void CTextbook_Academy_Details_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Textbook_Academy_Details_Add_name, m_Textbook_Academy_Details_Add_name);
	DDX_Text(pDX, IDC_Textbook_Academy_Details_Add_password, m_Textbook_Academy_Details_Add_password);
}


BEGIN_MESSAGE_MAP(CTextbook_Academy_Details_Add, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_Add_add, &CTextbook_Academy_Details_Add::OnBnClickedTextbookAcademyDetailsAddadd)
END_MESSAGE_MAP()


// CTextbook_Academy_Details_Add 消息处理程序


void CTextbook_Academy_Details_Add::OnBnClickedTextbookAcademyDetailsAddadd()
{
	UpdateData();
	if (m_Textbook_Academy_Details_Add_password.IsEmpty())
	{
		MessageBox(_T("请输入用户密码"));
	}
	else
	{
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		//CTime t = CTime::GetCurrentTime();
		CString str;

		CString sql;
		sql.Format(_T("insert into teacher(name,academy_id,state,password) values('%s','%s','2','%s')"),  m_Textbook_Academy_Details_Add_name, m_Textbook_Academy_Details_id, m_Textbook_Academy_Details_Add_password);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		sql.Format(_T("select * from teacher where name='%s' and academy_id='%s' and state='2' and password='%s'"), m_Textbook_Academy_Details_Add_name, m_Textbook_Academy_Details_id, m_Textbook_Academy_Details_Add_password);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		str = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("id"));

		CTextbook_Academy_Details_Add::OnOK();

		CString strMsg;
		strMsg.Format(_T("教师编号：%s"), str, str);

		MessageBox(strMsg);
	}
	// TODO:  在此添加控件通知处理程序代码
}
