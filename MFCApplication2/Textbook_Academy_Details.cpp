// Textbook_Academy_Details.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy_Details.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Textbook_Academy_Details_Add.h"
#include "Textbook_Academy_Details_Modify.h"
#include "Del_Ok.h"


// CTextbook_Academy_Details �Ի���

IMPLEMENT_DYNAMIC(CTextbook_Academy_Details, CDialogEx)

CTextbook_Academy_Details::CTextbook_Academy_Details(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Academy_Details::IDD, pParent)
	, tag(0)
	//, m_Textbook_Academy_Details_find_key(_T(""))
	, Find_type(0)
{

}

CTextbook_Academy_Details::~CTextbook_Academy_Details()
{
}

void CTextbook_Academy_Details::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Academy_Details_List, m_Textbook_Academy_Details_List);
	//  DDX_Control(pDX, IDC_Textbook_Academy_Details_find_type, m_Textbook_Academy_Details_find_type);
	//  DDX_Text(pDX, IDC_Textbook_Academy_Details_find_key, m_Textbook_Academy_Details_find_key);
}


BEGIN_MESSAGE_MAP(CTextbook_Academy_Details, CDialogEx)
	//ON_BN_CLICKED(IDC_Textbook_Academy_Details_Find, &CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsFind)
	//ON_CBN_SELCHANGE(IDC_Textbook_Academy_Details_find_type, &CTextbook_Academy_Details::OnSelchangeTextbookAcademyDetailsFindType)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_Add, &CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsAdd)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_Del, &CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsDel)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_Modify, &CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsModify)
	ON_BN_CLICKED(IDC_Textbook_Academy_Details_State, &CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsState)
END_MESSAGE_MAP()


// CTextbook_Academy_Details ��Ϣ�������


BOOL CTextbook_Academy_Details::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Academy_Details_List.DeleteAllItems();//���List�ؼ�

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from teacher where academy_id='%s' order by id asc"), m_Textbook_Academy_Details_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("��ѯ���ݳ��ִ���"));
	}
	else
	{
		if (tag == 0)
		{
			/*CString str[3] = { _T("��ʦ���"), _T("��ʦ����"), _T("״̬") };//��ʼ����Ͽ�
			int nIndex;
			for (int i = 0; i<3; i++)
			{
				nIndex = m_Textbook_Academy_Details_find_type.AddString(str[i]);
				m_Textbook_Academy_Details_find_type.SetItemData(nIndex, i);
			}
			m_Textbook_Academy_Details_find_type.SetCurSel(0);
			Find_type = 0;*/

			m_Textbook_Academy_Details_List.InsertColumn(0, _T("��ʦ���"));//�����  
			m_Textbook_Academy_Details_List.InsertColumn(1, _T("��������"));
			m_Textbook_Academy_Details_List.InsertColumn(2, _T("����"));
			m_Textbook_Academy_Details_List.InsertColumn(3, _T("״̬"));
			m_Textbook_Academy_Details_List.SetColumnWidth(0, 100);//�����п�  
			m_Textbook_Academy_Details_List.SetColumnWidth(1, 100);
			m_Textbook_Academy_Details_List.SetColumnWidth(2, 100);
			m_Textbook_Academy_Details_List.SetColumnWidth(3, 100);
			tag++;
		}

		_variant_t id, name, password, state;
		CString str_id, str_name, str_password, str_state;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
			password = CDBO.m_pRecordset->GetCollect(_variant_t("password"));
			state = CDBO.m_pRecordset->GetCollect(_variant_t("state"));
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
			nIndex = m_Textbook_Academy_Details_List.InsertItem(i, str_id);
			m_Textbook_Academy_Details_List.SetItemText(nIndex, 1, str_name);
			m_Textbook_Academy_Details_List.SetItemText(nIndex, 2, str_password);
			m_Textbook_Academy_Details_List.SetItemText(nIndex, 3, str_state);
			i++;
			CDBO.m_pRecordset->MoveNext();
		}

		m_Textbook_Academy_Details_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//void CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsFind()
//{
//	UpdateData();
//
//	m_Textbook_Academy_Details_List.DeleteAllItems();//���List�ؼ�
//
//	CDBOperation CDBO;
//	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
//
//	CString sql;
//	sql.Format(_T("select * from teacher where academy_id='%s' order by id asc"), m_Textbook_Academy_Details_id);
//	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
//
//	if (NULL == CDBO.m_pRecordset)
//	{
//		MessageBox(_T("��ѯ���ݳ��ִ���"));
//	}
//	else
//	{
//		/*if (tag == 0)
//		{
//			m_Textbook_Academy_Details_List.InsertColumn(0, _T("��ʦ���"));//�����  
//			m_Textbook_Academy_Details_List.InsertColumn(1, _T("��������"));
//			m_Textbook_Academy_Details_List.InsertColumn(2, _T("����"));
//			m_Textbook_Academy_Details_List.InsertColumn(3, _T("״̬"));
//			m_Textbook_Academy_Details_List.SetColumnWidth(0, 100);//�����п�  
//			m_Textbook_Academy_Details_List.SetColumnWidth(1, 100);
//			m_Textbook_Academy_Details_List.SetColumnWidth(2, 100);
//			m_Textbook_Academy_Details_List.SetColumnWidth(3, 100);
//			tag++;
//		}*/
//
//		_variant_t id, name, password, state;
//		CString str_id, str_name, str_password, str_state;
//		int i = 0;
//		int nIndex;
//		while (!CDBO.m_pRecordset->adoEOF)
//		{
//			//pRst->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
//			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
//			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
//			password = CDBO.m_pRecordset->GetCollect(_variant_t("password"));
//			state = CDBO.m_pRecordset->GetCollect(_variant_t("state"));
//
//			str_id = (CString)id;
//			if (name.vt == VT_NULL)
//			{
//				str_name.Format(_T(""));
//			}
//			else str_name = name;
//			str_password = password;
//			str_state = state;
//			if (str_state == "0")
//			{
//				str_state.Format(_T("����"));
//			}
//			else
//			{
//				str_state.Format(_T("����"));
//			}
//
//			int n = 0;
//			if (Find_type == 0)
//			{
//				if (str_id.Find(m_Textbook_Academy_Details_find_key) != -1){ n = 1; }
//			}
//			else if (Find_type == 1)
//			{
//				if (str_name.Find(m_Textbook_Academy_Details_find_key) != -1){ n = 1; }
//			}
//			else if (Find_type == 2)
//			{
//				if (str_state.Find(m_Textbook_Academy_Details_find_key) != -1){ n = 1; }
//			}
//
//			if (n != 0)
//			{
//				nIndex = m_Textbook_Academy_Details_List.InsertItem(i, str_id);
//				m_Textbook_Academy_Details_List.SetItemText(nIndex, 1, str_name);
//				m_Textbook_Academy_Details_List.SetItemText(nIndex, 2, str_password);
//				m_Textbook_Academy_Details_List.SetItemText(nIndex, 3, str_state);
//				i++;
//			}
//			CDBO.m_pRecordset->MoveNext();
//		}
//
//		m_Textbook_Academy_Details_List.SetRedraw(TRUE);//��ʾ 
//	}
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CTextbook_Academy_Details::OnSelchangeTextbookAcademyDetailsFindType()
//{
//	int nIndex = m_Textbook_Academy_Details_find_type.GetCurSel();
//	if (nIndex != CB_ERR)
//	{
//		Find_type = m_Textbook_Academy_Details_find_type.GetItemData(nIndex);
//	}
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsAdd()
{
	CTextbook_Academy_Details_Add dlg;
	dlg.DoModal();
	OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsDel()
{
	POSITION pos = m_Textbook_Academy_Details_List.GetFirstSelectedItemPosition();

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
				nIndex = m_Textbook_Academy_Details_List.GetNextSelectedItem(pos);
				str = m_Textbook_Academy_Details_List.GetItemText(nIndex, 0);//���Ҫɾ�����id
			}

			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString strSql;
			strSql.Format(_T("delete from teacher where id='%s'"), str);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			m_Textbook_Academy_Details_List.DeleteItem(nIndex);
			MessageBox(_T("ɾ���ɹ���"));

			OnInitDialog();
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsModify()
{
	POSITION pos = m_Textbook_Academy_Details_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		int nIndex;
		CString str;

		while (pos)
		{
			nIndex = m_Textbook_Academy_Details_List.GetNextSelectedItem(pos);
			str = m_Textbook_Academy_Details_List.GetItemText(nIndex, 0);//���id
		}
		temp = str;
		
		CTextbook_Academy_Details_Modify dlg;
		dlg.DoModal();

		OnInitDialog();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTextbook_Academy_Details::OnBnClickedTextbookAcademyDetailsState()
{
	POSITION pos = m_Textbook_Academy_Details_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		int nIndex;
		CString str;

		while (pos)
		{
			nIndex = m_Textbook_Academy_Details_List.GetNextSelectedItem(pos);
			str = m_Textbook_Academy_Details_List.GetItemText(nIndex, 0);//���id
		}

		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString strSql;
		strSql.Format(_T("select * from teacher where id='%s'"), str);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		CString state;
		state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
		if (state == "1") state = "2";//1���ã�2����
		else if (state == "2") state = "1";

		strSql.Format(_T("update teacher set state='%s' where id='%s'"), state, str);
		CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		OnInitDialog();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
