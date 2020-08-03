// Textbook_Information.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Information.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "MFCApplication2Dlg.h"


// CTextbook_Information �Ի���

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


// CTextbook_Information ��Ϣ�������


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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
		MessageBox(_T("�޸Ķ�"));
	}
	else
	{
		strSql.Format(_T("update my_user set password='%s' where id='%s'"), m_Textbook_Information_password, m_Textbook_Information_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		MessageBox(_T("�޸ĳɹ�"));
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Information::OnBnClickedTextbookDown()
{
	CTextbook_Information::OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);

	CMFCApplication2Dlg dlg;
	dlg.DoModal();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
