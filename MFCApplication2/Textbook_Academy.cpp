// Textbook_Academy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Textbook_Academy_Add.h"
#include "Textbook_Academy_Details.h"
#include "Del_OK.h"


// CTextbook_Academy �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Academy, CDialogEx)

CTextbook_Academy::CTextbook_Academy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Academy::IDD, pParent)
	, ADD_tag(0)
{

}

CTextbook_Academy::~CTextbook_Academy()
{
}

void CTextbook_Academy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Academy_List, m_Textbook_Academy_List);
}


BEGIN_MESSAGE_MAP(CTextbook_Academy, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Academy_Add, &CTextbook_Academy::OnBnClickedTextbookAcademyAdd)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details, &CTextbook_Academy::OnBnClickedTextbookAcademyDetails)
	ON_BN_CLICKED(IDC_Textbook_Academy_Del, &CTextbook_Academy::OnBnClickedTextbookAcademyDel)
END_MESSAGE_MAP()


// CTextbook_Academy ��Ϣ�������


BOOL CTextbook_Academy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Academy_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select id,name,state from my_user where type='2' order by id asc");
	pRst = CDBO.ExecuteWithResSQL(sql);

	if (NULL == pRst)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();
		MessageBox(_T("����ѧԺ��Ϣ"));
	}
	else
	{
		if (ADD_tag == 0)
		{
			m_Textbook_Academy_List.InsertColumn(0, _T("ѧԺ���"));//�����  
			m_Textbook_Academy_List.InsertColumn(1, _T("����"));
			m_Textbook_Academy_List.InsertColumn(2, _T("��ʦ"));
			m_Textbook_Academy_List.InsertColumn(3, _T("״̬"));
			m_Textbook_Academy_List.SetColumnWidth(0, 100);//�����п�  
			m_Textbook_Academy_List.SetColumnWidth(1, 100);
			m_Textbook_Academy_List.SetColumnWidth(2, 100);
			m_Textbook_Academy_List.SetColumnWidth(3, 100);
			ADD_tag++;
		}

		CDBOperation CDBO_teacher;
		bool con = CDBO_teacher.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		_variant_t id, name, state;
		CString str_id, str_name, str_state;
		int i = 0;
		int nIndex;
		while (!pRst->adoEOF)
		{
			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			id = pRst->GetCollect(_variant_t("id"));
			name = pRst->GetCollect(_variant_t("name"));
			state = pRst->GetCollect(_variant_t("state"));
			str_id = (CString)id;
			str_name = (CString)name;
			str_state = (CString)state;
			if (str_state == "0")
			{
				str_state.Format(_T("����"));
			}
			else if (str_state == "1")
			{
				str_state.Format(_T("����"));
			}
			nIndex = m_Textbook_Academy_List.InsertItem(i, str_id);
			m_Textbook_Academy_List.SetItemText(nIndex, 1, str_name);

			CString strSql;
			strSql.Format(_T("select count(*)as sum from teacher where academy_id='%s'"), str_id);
			CDBO_teacher.m_pRecordset = CDBO_teacher.ExecuteWithResSQL((_bstr_t)strSql);
			_variant_t sum;
			CString str_sum;
			sum = CDBO_teacher.m_pRecordset->GetCollect(_variant_t("sum"));
			str_sum = (CString)sum;

			m_Textbook_Academy_List.SetItemText(nIndex, 2, str_sum);
			m_Textbook_Academy_List.SetItemText(nIndex, 3, str_state);
			i++;
			pRst->MoveNext();
		}

		m_Textbook_Academy_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTextbook_Academy::OnBnClickedTextbookAcademyAdd()
{
	CTextbook_Academy_Add dlg;
	dlg.DoModal();
	OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Academy::OnBnClickedTextbookAcademyDetails()
{
	POSITION pos = m_Textbook_Academy_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("��ѡ��ѧԺ��"));
	else
	{
		CDBOperation CDBO;
		int nIndex;
		while (pos)
		{
			nIndex = m_Textbook_Academy_List.GetNextSelectedItem(pos);
			m_Textbook_Academy_Details_id = m_Textbook_Academy_List.GetItemText(nIndex, 0);//���ѡ��ѧԺ��id
		}

		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString strSql;
		strSql.Format(_T("select * from teacher where academy_id='%s'"), m_Textbook_Academy_Details_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		if (CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("��ѧԺ���޽�ʦ��"));
		}
		CTextbook_Academy_Details dlg;
		dlg.DoModal();
		OnInitDialog();
	}

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Academy::OnBnClickedTextbookAcademyDel()
{
	POSITION pos = m_Textbook_Academy_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		CDel_OK dlg;
		dlg.DoModal();

		if (m_ok == "1")
		{
			int nIndex;
			CString str;

			while (pos)
			{
				nIndex = m_Textbook_Academy_List.GetNextSelectedItem(pos);
				str = m_Textbook_Academy_List.GetItemText(nIndex, 0);//���Ҫɾ�����id
			}

			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString strSql;
			strSql.Format(_T("select * from teacher where academy_id='%s'"), str);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL(_bstr_t(strSql));

			if (CDBO.m_pRecordset->adoEOF)
			{
				CDBOperation CDBO_del;
				CDBO_del.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

				CString sql;
				sql.Format(_T("delete from my_user where type='2' and id='%s'"), str);

				CDBO_del.ExecuteWithResSQL((_bstr_t)sql);

				m_Textbook_Academy_List.DeleteItem(nIndex);
				MessageBox(_T("ɾ���ɹ���"));

				OnInitDialog();
			}
			else
			{
				MessageBox(_T("���ڽ�ʦ��ɾ��ʧ�ܣ�"));
			}
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
