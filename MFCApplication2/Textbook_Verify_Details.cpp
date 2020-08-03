// Textbook_Verify_Details.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Verify_Details.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Verify_Details �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Verify_Details, CDialogEx)

CTextbook_Verify_Details::CTextbook_Verify_Details(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Verify_Details::IDD, pParent)
{

}

CTextbook_Verify_Details::~CTextbook_Verify_Details()
{
}

void CTextbook_Verify_Details::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Verify_Details_List, m_Textbook_Verify_Details_List);
}


BEGIN_MESSAGE_MAP(CTextbook_Verify_Details, CDialogEx)
END_MESSAGE_MAP()


// CTextbook_Verify_Details ��Ϣ�������


BOOL CTextbook_Verify_Details::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Verify_Details_List.DeleteAllItems();

	//if (tag == 0)
	{
		m_Textbook_Verify_Details_List.InsertColumn(0, _T("�̲ı��"));//�����  
		m_Textbook_Verify_Details_List.InsertColumn(1, _T("�̲�����"));
		m_Textbook_Verify_Details_List.InsertColumn(2, _T("�̲�����"));
		m_Textbook_Verify_Details_List.SetColumnWidth(0, 100);//�����п�  
		m_Textbook_Verify_Details_List.SetColumnWidth(1, 100);
		m_Textbook_Verify_Details_List.SetColumnWidth(2, 100);
		//tag++;
	}

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from ordertwo where order_id='%s'"), m_Teacher_Demand_bookid/*������*/);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	while (!CDBO.m_pRecordset->adoEOF)
	{
		int i = 0;
		int nIndex;

		nIndex = m_Textbook_Verify_Details_List.InsertItem(0, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id")));

		CDBOperation CDBO_book;
		CDBO_book.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		sql.Format(_T("select * from books where id='%s'"), (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id")));
		CDBO_book.m_pRecordset = CDBO_book.ExecuteWithResSQL((_bstr_t)sql);
		m_Textbook_Verify_Details_List.SetItemText(nIndex, 1, (CString)CDBO_book.m_pRecordset->GetCollect(_variant_t("name")));

		m_Textbook_Verify_Details_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("booknum")));
		CDBO.m_pRecordset->MoveNext();
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
