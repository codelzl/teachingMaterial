// Textbook_Teacher.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Teacher.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTextbook_Teacher �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Teacher, CDialogEx)

CTextbook_Teacher::CTextbook_Teacher(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Teacher::IDD, pParent)
	, m_Textbook_Teacher_find_key(_T(""))
	, tag(0)
	, Find_type(0)
{

}

CTextbook_Teacher::~CTextbook_Teacher()
{
}

void CTextbook_Teacher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Teacher_LIST, m_Textbook_Teacher_List);
	//  DDX_CBString(pDX, IDC_Textbook_Teacher_find_type, m_Textbook_Teacher_find_type);
	DDX_Text(pDX, IDC_Textbook_Teacher_find_key, m_Textbook_Teacher_find_key);
	DDX_Control(pDX, IDC_Textbook_Teacher_find_type, m_Textbook_Teacher_find_type);
}


BEGIN_MESSAGE_MAP(CTextbook_Teacher, CDialogEx)
	ON_CBN_SELCHANGE(IDC_Textbook_Teacher_find_type, &CTextbook_Teacher::OnSelchangeTextbookTeacherFindType)
	ON_BN_CLICKED(IDC_Textbook_Teacher_Find, &CTextbook_Teacher::OnBnClickedTextbookTeacherFind)
END_MESSAGE_MAP()


// CTextbook_Teacher ��Ϣ�������


BOOL CTextbook_Teacher::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Teacher_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from teacher "));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		if (tag == 0)
		{
			CString str[3] = { _T("��ʦ���"), _T("��ʦ����"), _T("״̬") };//��ʼ����Ͽ�
			int nIndex;
			for (int i = 0; i<3; i++)
			{
				nIndex = m_Textbook_Teacher_find_type.AddString(str[i]);
				m_Textbook_Teacher_find_type.SetItemData(nIndex, i);
			}
			m_Textbook_Teacher_find_type.SetCurSel(0);
			Find_type = 0;

			m_Textbook_Teacher_List.InsertColumn(0, _T("��ʦ���"));//�����  
			m_Textbook_Teacher_List.InsertColumn(1, _T("��ʦ����"));
			m_Textbook_Teacher_List.InsertColumn(2, _T("����"));
			m_Textbook_Teacher_List.InsertColumn(3, _T("״̬"));
			m_Textbook_Teacher_List.InsertColumn(4, _T("ѧԺ"));
			m_Textbook_Teacher_List.SetColumnWidth(0, 100);//�����п�  
			m_Textbook_Teacher_List.SetColumnWidth(1, 100);
			m_Textbook_Teacher_List.SetColumnWidth(2, 100);
			m_Textbook_Teacher_List.SetColumnWidth(3, 100);
			m_Textbook_Teacher_List.SetColumnWidth(4, 100);
			tag++;
		}

		_variant_t id, name, password, state, academy;
		CString str_id, str_name, str_password, str_state, str_academy;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
			password = CDBO.m_pRecordset->GetCollect(_variant_t("password"));
			state = CDBO.m_pRecordset->GetCollect(_variant_t("state"));
			academy = CDBO.m_pRecordset->GetCollect(_variant_t("academy_id"));
			str_id = (CString)id;
			if (name.vt == VT_NULL)
			{
				str_name.Format(_T(""));
			}
			else
			{
				str_name = (CString)name;
			}
			str_password = (CString)password;
			str_state = (CString)state;
			if (str_state == "1")
			{
				str_state.Format(_T("����"));
			}
			else if (str_state == "2")
			{
				str_state.Format(_T("����"));
			}
			str_academy = (CString)academy;

			CDBOperation CDBO_academy;
			CDBO_academy.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString strSql;
			strSql.Format(_T("select * from my_user where type='2' and id=%s"), str_academy);
			CDBO_academy.m_pRecordset = CDBO_academy.ExecuteWithResSQL((_bstr_t)strSql);
			
			_variant_t academy_name;
			academy_name = CDBO_academy.m_pRecordset->GetCollect(_variant_t("name"));
			/*if (CDBO_academy.m_pRecordset->adoEOF)
			{
				MessageBox(_T("111"));
			}
			try
			{//���Ӵ���}
			catch (_com_error& e)
			{
				CString strMsg;
				strMsg.Format(_T("����������%s\n������Ϣ%s"),
					(LPCTSTR)e.Description(),
					(LPCTSTR)e.ErrorMessage());
				AfxMessageBox(strMsg);
			}*/
			
			if (academy_name.vt == VT_NULL)
			{
				str_academy.Format(_T(""));
			}
			else str_academy = (CString)academy_name;

			nIndex = m_Textbook_Teacher_List.InsertItem(i, str_id);
			m_Textbook_Teacher_List.SetItemText(nIndex, 1, str_name);
			m_Textbook_Teacher_List.SetItemText(nIndex, 2, str_password);
			m_Textbook_Teacher_List.SetItemText(nIndex, 3, str_state);
			m_Textbook_Teacher_List.SetItemText(nIndex, 4, str_academy);
			i++;
			CDBO.m_pRecordset->MoveNext();
		}

		m_Textbook_Teacher_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTextbook_Teacher::OnSelchangeTextbookTeacherFindType()
{
	int nIndex = m_Textbook_Teacher_find_type.GetCurSel();
	if (nIndex != CB_ERR)
	{
		Find_type = m_Textbook_Teacher_find_type.GetItemData(nIndex);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Teacher::OnBnClickedTextbookTeacherFind()
{
	UpdateData();
	
	m_Textbook_Teacher_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
	
	CString sql;
	sql.Format(_T("select * from teacher order by teacher.id asc"));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
	
	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		_variant_t id, name, password, state, academy;
		CString str_id, str_name, str_password, str_state, str_academy;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
			password = CDBO.m_pRecordset->GetCollect(_variant_t("password"));
			state = CDBO.m_pRecordset->GetCollect(_variant_t("state"));
			academy = CDBO.m_pRecordset->GetCollect(_variant_t("academy_id"));
	
			str_id = (CString)id;
			if (name.vt == VT_NULL)
			{
				str_name.Format(_T(""));
			}
			else str_name = name;
			str_password = password;
			str_state = state;
			if (str_state == "1")
			{
				str_state.Format(_T("����"));
			}
			else if (str_state == "2")
			{
				str_state.Format(_T("����"));
			}
			str_academy = (CString)academy;

			CDBOperation CDBO_academy;
			CDBO_academy.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
			CString strSql;
			strSql.Format(_T("select name from my_user where type='2' and id='%s'"), str_academy);
			CDBO_academy.m_pRecordset = CDBO_academy.ExecuteWithResSQL((_bstr_t)strSql);
			str_academy = (CString)CDBO_academy.m_pRecordset->GetCollect(_variant_t("name"));

			int n = 0;
			if (Find_type == 0)
			{
				if (str_id.Find(m_Textbook_Teacher_find_key) != -1){ n = 1; }
			}
			else if (Find_type == 1)
			{
				if (str_name.Find(m_Textbook_Teacher_find_key) != -1){ n = 1; }
			}
			else if (Find_type == 2)
			{
				if (str_state.Find(m_Textbook_Teacher_find_key) != -1){ n = 1; }
			}
			else if (Find_type == 3)
			{
				if (str_academy.Find(m_Textbook_Teacher_find_key) != -1){ n = 1; }
			}
	
			if (n != 0)
			{
				nIndex = m_Textbook_Teacher_List.InsertItem(i, str_id);
				m_Textbook_Teacher_List.SetItemText(nIndex, 1, str_name);
				m_Textbook_Teacher_List.SetItemText(nIndex, 2, str_password);
				m_Textbook_Teacher_List.SetItemText(nIndex, 3, str_state);
				m_Textbook_Teacher_List.SetItemText(nIndex, 4, str_academy);
				i++;
			}
			CDBO.m_pRecordset->MoveNext();
		}
	
		m_Textbook_Teacher_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
