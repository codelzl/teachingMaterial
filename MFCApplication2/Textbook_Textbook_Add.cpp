// Textbook_Textbook_Add.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Textbook_Add.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Textbook_Add 对话框

IMPLEMENT_DYNAMIC(CTextbook_Textbook_Add, CDialogEx)

CTextbook_Textbook_Add::CTextbook_Textbook_Add(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Textbook_Add::IDD, pParent)
	, m_Textbook_Textbook_Add_Name(_T(""))
	, m_Textbook_Textbook_Add_Author(_T(""))
	, m_Textbook_Textbook_Add_Isbn(_T(""))
	, m_Textbook_Textbook_Add_Edition(_T(""))
{

}

CTextbook_Textbook_Add::~CTextbook_Textbook_Add()
{
}

void CTextbook_Textbook_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Textbook_Textbook_Add_Name, m_Textbook_Textbook_Add_Name);
	DDX_Text(pDX, IDC_Textbook_Textbook_Add_Author, m_Textbook_Textbook_Add_Author);
	DDX_Text(pDX, IDC_Textbook_Textbook_Add_ISBN, m_Textbook_Textbook_Add_Isbn);
	DDX_Text(pDX, IDC_Textbook_Textbook_Add_Edition, m_Textbook_Textbook_Add_Edition);
}


BEGIN_MESSAGE_MAP(CTextbook_Textbook_Add, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Textbook_Add, &CTextbook_Textbook_Add::OnBnClickedTextbookTextbookAdd)
END_MESSAGE_MAP()


// CTextbook_Textbook_Add 消息处理程序


void CTextbook_Textbook_Add::OnBnClickedTextbookTextbookAdd()
{
	UpdateData();
	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	if (m_Textbook_Textbook_Add_Name.IsEmpty() || m_Textbook_Textbook_Add_Author.IsEmpty() || m_Textbook_Textbook_Add_Isbn.IsEmpty())
	{
		MessageBox(_T("请填写完整的教材信息!"));
	}
	else
	{
		CString strSql;
		/*strSql.Format(_T("select * from books where id='%s'"), m_Textbook_Textbook_Add_Id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("该教材编号已存在，请重新输入！"));
		}
		else*/
		{
			strSql.Format(_T("insert into books(name,author,isbn,edition) values('%s','%s','%s','%s')"), m_Textbook_Textbook_Add_Name, m_Textbook_Textbook_Add_Author, m_Textbook_Textbook_Add_Isbn, m_Textbook_Textbook_Add_Edition);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			CTextbook_Textbook_Add::OnOK();

			MessageBox(_T("添加成功!"));
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}
