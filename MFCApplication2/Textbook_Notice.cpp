// Textbook_Notice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Notice.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Notice �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Notice, CDialogEx)

CTextbook_Notice::CTextbook_Notice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Notice::IDD, pParent)
	, m_Textbook_Notice(_T(""))
	, m_Notice_Time(_T(""))
{

}

CTextbook_Notice::~CTextbook_Notice()
{
}

void CTextbook_Notice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Textbook_Notice, m_Textbook_Notice);
	DDX_Text(pDX, IDC_Notice_Time, m_Notice_Time);
}


BEGIN_MESSAGE_MAP(CTextbook_Notice, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Notice_Save, &CTextbook_Notice::OnBnClickedTextbookNoticeSave)
END_MESSAGE_MAP()


// CTextbook_Notice ��Ϣ�������


void CTextbook_Notice::OnBnClickedTextbookNoticeSave()
{
	UpdateData();

	CTime time = CTime::GetCurrentTime();
	CString notice_time;
	notice_time.Format(_T("%d-%.2d-%.2d"), time.GetYear(), time.GetMonth(), time.GetDay());
		// = time.Format("%Y%m%d%H%M%S");
	
	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
	
	CString strSql;
	strSql.Format(_T("insert into notice(mainword,notice_date,user_id) values('%s','%s','%s')"), m_Textbook_Notice, notice_time, temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
	
	/*m_Notice_Time = notice_time;
	UpdateData(false);*/
	MessageBox(_T("����ɹ�!"));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CTextbook_Notice::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from notice order by id desc");
	pRst = CDBO.ExecuteWithResSQL(sql);

	if (NULL == pRst)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		_variant_t word;
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			word = pRst->GetCollect(_variant_t("mainword"));
			m_Notice_Time = (CString)pRst->GetCollect(_variant_t("notice_date"));
			//pRst->MoveNext();
		}
		m_Textbook_Notice = (CString)word;
		UpdateData(false);
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
