// Acamedy_Textbook.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Acamedy_Textbook.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CAcamedy_Textbook �Ի���

IMPLEMENT_DYNAMIC(CAcademy_Textbook, CDialogEx)

CAcademy_Textbook::CAcademy_Textbook(CWnd* pParent /*=NULL*/)
: CDialogEx(CAcademy_Textbook::IDD, pParent)
, m_Academy_Textbook_find_key(_T(""))
, tag(0)
, Find_type(0)
{

}

CAcademy_Textbook::~CAcademy_Textbook()
{
}

void CAcademy_Textbook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Academy_Textbook_List, m_Academy_Textbook_List);
	DDX_Control(pDX, IDC_Academy_Textbook_find_type, m_Academy_Textbook_find_type);
	DDX_Text(pDX, IDC_Academy_Textbook_find_key, m_Academy_Textbook_find_key);
}


BEGIN_MESSAGE_MAP(CAcademy_Textbook, CDialogEx)
	ON_CBN_SELCHANGE(IDC_Academy_Textbook_find_type, &CAcademy_Textbook::OnSelchangeAcademyTextbookFindType)
	ON_BN_CLICKED(IDC_Academy_Textbook_find, &CAcademy_Textbook::OnBnClickedAcademyTextbookfind)
	ON_BN_CLICKED(IDC_Academy_Textbook_Find_All, &CAcademy_Textbook::OnBnClickedAcademyTextbookFindAll)
END_MESSAGE_MAP()


// CAcamedy_Textbook ��Ϣ�������


BOOL CAcademy_Textbook::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (tag == 0)
	{
		CString str[4] = { _T("�̲ı��"), _T("�̲�����"), _T("����"), _T("������") };//��ʼ����Ͽ�
		int nIndex;
		for (int i = 0; i<4; i++)
		{
			nIndex = m_Academy_Textbook_find_type.AddString(str[i]);
			m_Academy_Textbook_find_type.SetItemData(nIndex, i);
		}
		m_Academy_Textbook_find_type.SetCurSel(1);
		Find_type = 0;
	}

	m_Academy_Textbook_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from books order by id asc");
	pRst = CDBO.ExecuteWithResSQL(sql);

	if (NULL == pRst)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	if (pRst->adoEOF)
	{
		pRst->Close();
		MessageBox(_T("There is no records in this table"));
	}
	else
	{
		if (tag == 0)
		{
			m_Academy_Textbook_List.InsertColumn(0, _T("�̲ı��"));//�����  
			m_Academy_Textbook_List.InsertColumn(1, _T("����"));
			m_Academy_Textbook_List.InsertColumn(2, _T("����"));
			m_Academy_Textbook_List.InsertColumn(3, _T("ISBN"));
			m_Academy_Textbook_List.InsertColumn(4, _T("������"));
			m_Academy_Textbook_List.SetColumnWidth(0, 100);//�����п�  
			m_Academy_Textbook_List.SetColumnWidth(1, 100);
			m_Academy_Textbook_List.SetColumnWidth(2, 100);
			m_Academy_Textbook_List.SetColumnWidth(3, 100);
			m_Academy_Textbook_List.SetColumnWidth(4, 100);
			tag++;
		}

		_variant_t id, name, author, isbn, edition;
		CString str_id, str_name, str_author, str_isbn, str_edition;
		int i = 0;
		int nIndex;
		while (!pRst->adoEOF)
		{
			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			id = pRst->GetCollect(_variant_t("id"));
			name = pRst->GetCollect(_variant_t("name"));
			author = pRst->GetCollect(_variant_t("author"));
			isbn = pRst->GetCollect(_variant_t("isbn"));
			edition = pRst->GetCollect(_variant_t("edition"));
			str_id = (CString)id;
			str_name = (CString)name;
			str_author = (CString)author;
			str_isbn = (CString)isbn;
			if (edition.vt == VT_NULL)
			{
				str_edition.Format(_T(" "));
			}
			else str_edition = (CString)edition;
			nIndex = m_Academy_Textbook_List.InsertItem(i, str_id);
			m_Academy_Textbook_List.SetItemText(nIndex, 1, str_name);
			m_Academy_Textbook_List.SetItemText(nIndex, 2, str_author);
			m_Academy_Textbook_List.SetItemText(nIndex, 3, str_isbn);
			m_Academy_Textbook_List.SetItemText(nIndex, 4, str_edition);
			i++;
			pRst->MoveNext();
		}

		m_Academy_Textbook_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAcademy_Textbook::OnSelchangeAcademyTextbookFindType()
{
	int nIndex = m_Academy_Textbook_find_type.GetCurSel();
	if (nIndex != CB_ERR)
	{
		Find_type = m_Academy_Textbook_find_type.GetItemData(nIndex);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAcademy_Textbook::OnBnClickedAcademyTextbookfind()
{
	UpdateData();

	m_Academy_Textbook_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from books order by id asc"));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	if (CDBO.m_pRecordset->adoEOF)
	{
		CDBO.m_pRecordset->Close();
		MessageBox(_T("�̲Ĳ�����"));
	}
	else
	{
		if (tag == 0)
		{
			m_Academy_Textbook_List.InsertColumn(0, _T("�̲ı��"));//�����  
			m_Academy_Textbook_List.InsertColumn(1, _T("����"));
			m_Academy_Textbook_List.InsertColumn(2, _T("����"));
			m_Academy_Textbook_List.InsertColumn(3, _T("ISBN"));
			m_Academy_Textbook_List.InsertColumn(4, _T("������"));
			m_Academy_Textbook_List.SetColumnWidth(0, 100);//�����п�  
			m_Academy_Textbook_List.SetColumnWidth(1, 100);
			m_Academy_Textbook_List.SetColumnWidth(2, 100);
			m_Academy_Textbook_List.SetColumnWidth(3, 100);
			m_Academy_Textbook_List.SetColumnWidth(4, 100);
			tag++;
		}

		_variant_t id, name, author, isbn, edition;
		CString str_id, str_name, str_author, str_isbn, str_edition;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
			author = CDBO.m_pRecordset->GetCollect(_variant_t("author"));
			isbn = CDBO.m_pRecordset->GetCollect(_variant_t("isbn"));
			edition = CDBO.m_pRecordset->GetCollect(_variant_t("edition"));
			str_id = (CString)id;
			str_name = (CString)name;
			str_author = (CString)author;
			str_isbn = (CString)isbn;
			if (edition.vt == VT_NULL)
			{
				str_edition.Format(_T(""));
			}
			else str_edition = (CString)edition;
			int tag = 0;
			if (Find_type == 0)
			{
				if (str_id.Find(m_Academy_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 1)
			{
				if (str_name.Find(m_Academy_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 2)
			{
				if (str_author.Find(m_Academy_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 3)
			{
				if (str_edition.Find(m_Academy_Textbook_find_key) != -1){ tag = 1; }
			}

			if (tag != 0)
			{
				nIndex = m_Academy_Textbook_List.InsertItem(i, str_id);
				m_Academy_Textbook_List.SetItemText(nIndex, 1, str_name);
				m_Academy_Textbook_List.SetItemText(nIndex, 2, str_author);
				m_Academy_Textbook_List.SetItemText(nIndex, 3, str_isbn);
				m_Academy_Textbook_List.SetItemText(nIndex, 4, str_edition);
				i++;
			}
			CDBO.m_pRecordset->MoveNext();
		}
		if (i == 0) { MessageBox(_T("�̲Ĳ�����")); }

		m_Academy_Textbook_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAcademy_Textbook::OnBnClickedAcademyTextbookFindAll()
{
	OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
