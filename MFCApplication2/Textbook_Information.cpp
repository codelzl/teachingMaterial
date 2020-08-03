// Textbook_Information.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Information.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "MFCApplication2Dlg.h"


// CTextbook_Information 对话框

IMPLEMENT_DYNAMIC(CTextbook_Information, CDialogEx)

CTextbook_Information::CTextbook_Information(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Information::IDD, pParent)
	, m_Textbook_Information_id(_T(""))
	, m_Textbook_Information_password(_T(""))
{

}

CTextbook_Information::~CTextbook_Information()
{
}

void CTextbook_Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_Textbook_id, m_Textbook_id);
	//  DDX_Text(pDX, IDC_Textbook_Interface_Textbook_sum, m_Textbook_Interface_Textbook_sum);
	DDX_Text(pDX, IDC_Textbook_Information_id, m_Textbook_Information_id);
	DDX_Text(pDX, IDC_Textbook_Information_password, m_Textbook_Information_password);
}


BEGIN_MESSAGE_MAP(CTextbook_Information, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Information_save, &CTextbook_Information::OnBnClickedTextbookInformationsave)
	ON_BN_CLICKED(IDC_Textbook_Down, &CTextbook_Information::OnBnClickedTextbookDown)
END_MESSAGE_MAP()


// CTextbook_Information 消息处理程序


BOOL CTextbook_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Information_id = temp;

	CDBOperation CDBO;
	CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
	CString strSql;
	strSql.Format(_T("select * from my_user where type='3' and id='%s'"), m_Textbook_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	m_Textbook_Information_password = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("password"));
	UpdateData(false);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTextbook_Information::OnBnClickedTextbookInformationsave()
{
	UpdateData();
	CDBOperation CDBO;
	CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
	CString strSql;
	strSql.Format(_T("select * from my_user where id='%s'"), m_Textbook_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL(_bstr_t(strSql));
	if (m_Textbook_Information_password == (CString)CDBO.m_pRecordset->GetCollect(_variant_t("password")))
	{
		MessageBox(_T("无改动"));
	}
	else
	{
		strSql.Format(_T("update my_user set password='%s' where id='%s'"), m_Textbook_Information_password, m_Textbook_Information_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		MessageBox(_T("修改成功"));
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Information::OnBnClickedTextbookDown()
{
	CTextbook_Information::OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);

	CMFCApplication2Dlg dlg;
	dlg.DoModal();
	// TODO:  在此添加控件通知处理程序代码
}
