// Teacher_Demand.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher_Demand.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Teacher_Subscriptions.h"


// CTeacher_Demand �Ի���

IMPLEMENT_DYNAMIC(CTeacher_Demand, CDialogEx)

CTeacher_Demand::CTeacher_Demand(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher_Demand::IDD, pParent)
	, m_Teacher_Demand_find_key(_T(""))
	, Demand_tag(0)
	, Find_type(0)
	, tag(0)
	, m_Teacher_Demand_Num(_T(""))
{

}

CTeacher_Demand::~CTeacher_Demand()
{
}

void CTeacher_Demand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Teacher_Demand_List, m_Teacher_Demand_List);
	DDX_Control(pDX, IDC_Teacher_Demand_find_type, m_Teacher_Demand_find_type);
	DDX_Text(pDX, IDC_Teacher_Demand_find_key, m_Teacher_Demand_find_key);
	DDX_Control(pDX, IDC_Teacher_Demand_Order_List, m_Teacher_Demand_Order_List);
	DDX_Text(pDX, IDC_Teacher_Demand_Num, m_Teacher_Demand_Num);
}


BEGIN_MESSAGE_MAP(CTeacher_Demand, CDialogEx)
	ON_CBN_SELCHANGE(IDC_Teacher_Demand_find_type, &CTeacher_Demand::OnSelchangeTeacherDemandFindType)
	ON_BN_CLICKED(IDC_Teacher_Demand_find, &CTeacher_Demand::OnBnClickedTeacherDemandfind)
	ON_BN_CLICKED(IDC_Teacher_Demand_Add_subscription, &CTeacher_Demand::OnBnClickedTeacherDemandAddsubscription)
	ON_EN_CHANGE(IDC_Teacher_Demand_Num, &CTeacher_Demand::OnChangeTeacherDemandNum)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Teacher_Demand_Order_List, &CTeacher_Demand::OnItemchangedTeacherDemandOrderList)
	ON_BN_CLICKED(IDC_Teacher_Demand_Del, &CTeacher_Demand::OnBnClickedTeacherDemandDel)
	ON_BN_CLICKED(IDC_Teacher_Demand_Submit, &CTeacher_Demand::OnBnClickedTeacherDemandSubmit)
END_MESSAGE_MAP()


// CTeacher_Demand ��Ϣ�������


BOOL CTeacher_Demand::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (Demand_tag == 0)
	{
		CString str[4] = { _T("�̲ı��"), _T("�̲�����"), _T("����"), _T("������") };//��ʼ����Ͽ�
		int nIndex;
		for (int i = 0; i<4; i++)
		{
			nIndex = m_Teacher_Demand_find_type.AddString(str[i]);
			m_Teacher_Demand_find_type.SetItemData(nIndex, i);
		}
		m_Teacher_Demand_find_type.SetCurSel(1);
		Find_type = 0;
	}

	m_Teacher_Demand_List.DeleteAllItems();//���List�ؼ�

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
		if (Demand_tag == 0)
		{
			m_Teacher_Demand_List.InsertColumn(0, _T("�̲ı��"));//�����  
			m_Teacher_Demand_List.InsertColumn(1, _T("����"));
			m_Teacher_Demand_List.InsertColumn(2, _T("����"));
			m_Teacher_Demand_List.InsertColumn(3, _T("ISBN"));
			m_Teacher_Demand_List.InsertColumn(4, _T("������"));
			m_Teacher_Demand_List.SetColumnWidth(0, 100);//�����п�  
			m_Teacher_Demand_List.SetColumnWidth(1, 100);
			m_Teacher_Demand_List.SetColumnWidth(2, 100);
			m_Teacher_Demand_List.SetColumnWidth(3, 100);
			m_Teacher_Demand_List.SetColumnWidth(4, 100);

			m_Teacher_Demand_Order_List.InsertColumn(0, _T("�̲ı��"));//�����  
			m_Teacher_Demand_Order_List.InsertColumn(1, _T("����"));
			m_Teacher_Demand_Order_List.InsertColumn(2, _T("����"));
			m_Teacher_Demand_Order_List.SetColumnWidth(0, 100);//�����п�  
			m_Teacher_Demand_Order_List.SetColumnWidth(1, 100);
			m_Teacher_Demand_Order_List.SetColumnWidth(2, 100);
			Demand_tag++;
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
			nIndex = m_Teacher_Demand_List.InsertItem(i, str_id);
			m_Teacher_Demand_List.SetItemText(nIndex, 1, str_name);
			m_Teacher_Demand_List.SetItemText(nIndex, 2, str_author);
			m_Teacher_Demand_List.SetItemText(nIndex, 3, str_isbn);
			m_Teacher_Demand_List.SetItemText(nIndex, 4, str_edition);
			i++;
			pRst->MoveNext();
		}

		m_Teacher_Demand_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTeacher_Demand::OnSelchangeTeacherDemandFindType()
{
	int nIndex = m_Teacher_Demand_find_type.GetCurSel();
	if (nIndex != CB_ERR)
	{
		Find_type = m_Teacher_Demand_find_type.GetItemData(nIndex);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTeacher_Demand::OnBnClickedTeacherDemandfind()
{
	UpdateData();

	m_Teacher_Demand_List.DeleteAllItems();//���List�ؼ�

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
		MessageBox(_T("�̲Ŀ����޽̲�"));
	}
	else
	{
		if (Demand_tag == 0)
		{
			m_Teacher_Demand_List.InsertColumn(0, _T("�̲ı��"));//�����  
			m_Teacher_Demand_List.InsertColumn(1, _T("����"));
			m_Teacher_Demand_List.InsertColumn(2, _T("����"));
			m_Teacher_Demand_List.InsertColumn(3, _T("ISBN"));
			m_Teacher_Demand_List.InsertColumn(4, _T("������"));
			m_Teacher_Demand_List.SetColumnWidth(0, 100);//�����п�  
			m_Teacher_Demand_List.SetColumnWidth(1, 100);
			m_Teacher_Demand_List.SetColumnWidth(2, 100);
			m_Teacher_Demand_List.SetColumnWidth(3, 100);
			m_Teacher_Demand_List.SetColumnWidth(4, 100);
			Demand_tag++;
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
				if (str_id.Find(m_Teacher_Demand_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 1)
			{
				if (str_name.Find(m_Teacher_Demand_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 2)
			{
				if (str_author.Find(m_Teacher_Demand_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 3)
			{
				if (str_edition.Find(m_Teacher_Demand_find_key) != -1){ tag = 1; }
			}

			if (tag != 0)
			{
				nIndex = m_Teacher_Demand_List.InsertItem(i, str_id);
				m_Teacher_Demand_List.SetItemText(nIndex, 1, str_name);
				m_Teacher_Demand_List.SetItemText(nIndex, 2, str_author);
				m_Teacher_Demand_List.SetItemText(nIndex, 3, str_isbn);
				m_Teacher_Demand_List.SetItemText(nIndex, 4, str_edition);
				i++;
			}
			CDBO.m_pRecordset->MoveNext();
		}
		if (i == 0) { MessageBox(_T("�̲Ĳ�����")); }

		m_Teacher_Demand_List.SetRedraw(TRUE);//��ʾ 
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void CTeacher_Demand::OnBnClickedTeacherDemandAddsubscription()
{
	POSITION pos = m_Teacher_Demand_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		int nIndex;
		CString str;

		while (pos)
		{
			nIndex = m_Teacher_Demand_List.GetNextSelectedItem(pos);
			str = m_Teacher_Demand_List.GetItemText(nIndex, 0);//���id
		}

		//m_Teacher_Demand_Order_List.DeleteAllItems();//���List�ؼ�
		int n = 0;
		int i = m_Teacher_Demand_Order_List.GetItemCount();
		for (int j = 0; j < i; j++)
		{
			if (m_Teacher_Demand_Order_List.GetItemText(j, 0) == str)
			{
				n++;
			}
		}

		if (n == 0)
		{
			int nIndex;

			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString sql;
			nIndex = m_Teacher_Demand_Order_List.InsertItem(0, str);
			sql.Format(_T("select * from books where id='%s'"), str);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			if (!CDBO.m_pRecordset->adoEOF)
			{
				CString book_name = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("name"));

				m_Teacher_Demand_Order_List.SetItemText(nIndex, 1, book_name);
				m_Teacher_Demand_Order_List.SetItemText(nIndex, 2, _T("1"));
			}
		}
		else if (n != 0)
		{
			MessageBox(_T("�������ڶ���"));
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTeacher_Demand::OnChangeTeacherDemandNum()
{
	UpdateData();

	POSITION pos = m_Teacher_Demand_Order_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Teacher_Demand_Order_List.GetNextSelectedItem(pos);
			str = m_Teacher_Demand_Order_List.GetItemText(nIndex, 0);//���id
		}
		m_Teacher_Demand_Order_List.SetItemText(nIndex, 2, m_Teacher_Demand_Num);
		UpdateData(false);
	}
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTeacher_Demand::OnItemchangedTeacherDemandOrderList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
	{
		POSITION pos = m_Teacher_Demand_Order_List.GetFirstSelectedItemPosition();
		int nIndex;
		CString str;

		if (pos == NULL) MessageBox(_T("δѡ���У�"));
		else
		{
			while (pos)
			{
				nIndex = m_Teacher_Demand_Order_List.GetNextSelectedItem(pos);
				str = m_Teacher_Demand_Order_List.GetItemText(nIndex, 0);//���id
			}
			m_Teacher_Demand_Num = m_Teacher_Demand_Order_List.GetItemText(nIndex, 2);
			UpdateData(false);
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTeacher_Demand::OnBnClickedTeacherDemandDel()
{
	POSITION pos = m_Teacher_Demand_Order_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Teacher_Demand_Order_List.GetNextSelectedItem(pos);
			str = m_Teacher_Demand_Order_List.GetItemText(nIndex, 0);//���Ҫɾ�����id
		}
		m_Teacher_Demand_Order_List.DeleteItem(nIndex);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTeacher_Demand::OnBnClickedTeacherDemandSubmit()
{
	if (m_Teacher_Demand_Order_List.GetItemCount() != 0)
	{
		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("select * from teacher where id=%s"), temp);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));

		if (state == "2")//1���ã�2����
		{
			CTime time = CTime::GetCurrentTime();
			CString Subscriptions_id = time.Format("%Y%m%d%H%M%S");
			int i = m_Teacher_Demand_Order_List.GetItemCount();

			//CDBOperation CDBO;
			//bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			sql.Format(_T("insert into orderone(order_id,user_id,state,order_date) values('%s','%s','0','%s')"), Subscriptions_id, temp, Subscriptions_id);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			for (int j = 0; j < i; j++)
			{
				sql.Format(_T("insert into ordertwo values('%s','%s','%s')"), Subscriptions_id, m_Teacher_Demand_Order_List.GetItemText(j, 0), m_Teacher_Demand_Order_List.GetItemText(j, 2));
				CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			}

			MessageBox(_T("�ύ�ɹ�"));

			m_Teacher_Demand_Order_List.DeleteAllItems();
		}
		else if (state == "1")
		{
			MessageBox(_T("�Բ��������˺��ѱ�����"));
		}
	}
	else
	{
		MessageBox(_T("����Ϊ��"));
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
