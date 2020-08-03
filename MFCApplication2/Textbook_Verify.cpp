// Textbook_Verify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Verify.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Textbook_Verify_Details.h"


// CTextbook_Verify �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Verify, CDialogEx)

CTextbook_Verify::CTextbook_Verify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Verify::IDD, pParent)
	, tag(0)
{

}

CTextbook_Verify::~CTextbook_Verify()
{
}

void CTextbook_Verify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Verify_List, m_Textbook_Verify_List);
}


BEGIN_MESSAGE_MAP(CTextbook_Verify, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Verify_fail, &CTextbook_Verify::OnBnClickedTextbookVerifyfail)
	ON_BN_CLICKED(IDC_Textbook_Verify_pass, &CTextbook_Verify::OnBnClickedTextbookVerifypass)
	ON_BN_CLICKED(IDC_Textbook_Verify_Details, &CTextbook_Verify::OnBnClickedTextbookVerifyDetails)
END_MESSAGE_MAP()


// CTextbook_Verify ��Ϣ�������


BOOL CTextbook_Verify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Verify_List.DeleteAllItems();

	if (tag == 0)
	{
		m_Textbook_Verify_List.InsertColumn(0, _T("�������"));//�����  
		m_Textbook_Verify_List.InsertColumn(1, _T("�ύ��ʦ"));
		m_Textbook_Verify_List.InsertColumn(2, _T("״̬"));
		m_Textbook_Verify_List.InsertColumn(3, _T("����ʱ��"));
		m_Textbook_Verify_List.SetColumnWidth(0, 100);//�����п�  
		m_Textbook_Verify_List.SetColumnWidth(1, 100);
		m_Textbook_Verify_List.SetColumnWidth(2, 100);
		m_Textbook_Verify_List.SetColumnWidth(3, 100);
		tag++;
	}

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from orderone where state='2' or state='3' or state='4'"));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	while (!CDBO.m_pRecordset->adoEOF)
	{
		int i = 0;
		int nIndex;

		CString order_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_id"));
		nIndex = m_Textbook_Verify_List.InsertItem(i, order_id);
		CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
		if (state == "2")
		{
			state.Format(_T("δ���"));
		}
		else if (state == "3")
		{
			state.Format(_T("���δͨ��"));
		}
		else if (state == "4")
		{
			state.Format(_T("���ͨ��"));
		}

		CDBOperation CDBO_teacher;
		CDBO_teacher.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("user_id"));
		sql.Format(_T("select * from teacher where id=%s"), id);
		CDBO_teacher.m_pRecordset = CDBO_teacher.ExecuteWithResSQL((_bstr_t)sql);

		_variant_t name;
		CString str_name;
		
		try
		{
			name = CDBO_teacher.m_pRecordset->GetCollect(_variant_t("name"));
		}

		catch (_com_error& e)

		{

			CString strMsg;
			strMsg.Format(_T("����������%s\n������Ϣ%s"),

				(LPCTSTR)e.Description(),

				(LPCTSTR)e.ErrorMessage());

			AfxMessageBox(strMsg);

		}

		if (name.vt == VT_NULL)
		{
			str_name.Format(_T(""));
		}
		else str_name = (CString)name;
		m_Textbook_Verify_List.SetItemText(nIndex, 1, str_name);
		m_Textbook_Verify_List.SetItemText(nIndex, 2, state);
		m_Textbook_Verify_List.SetItemText(nIndex, 3, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_date")));
		i++;
		CDBO.m_pRecordset->MoveNext();
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTextbook_Verify::OnBnClickedTextbookVerifyfail()
{
	POSITION pos = m_Textbook_Verify_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Textbook_Verify_List.GetNextSelectedItem(pos);
			str = m_Textbook_Verify_List.GetItemText(nIndex, 0);//���id
		}
		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("update orderone set state='3' where order_id='%s'"), str);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		OnInitDialog();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Verify::OnBnClickedTextbookVerifypass()
{
	POSITION pos = m_Textbook_Verify_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Textbook_Verify_List.GetNextSelectedItem(pos);
			str = m_Textbook_Verify_List.GetItemText(nIndex, 0);//���id
		}
		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("update orderone set state='4' where order_id='%s'"), str);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		OnInitDialog();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Verify::OnBnClickedTextbookVerifyDetails()
{
	POSITION pos = m_Textbook_Verify_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Textbook_Verify_List.GetNextSelectedItem(pos);
			str = m_Textbook_Verify_List.GetItemText(nIndex, 0);//���id
		}
		m_Teacher_Demand_bookid = str;
		CTextbook_Verify_Details dlg;
		dlg.DoModal();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
