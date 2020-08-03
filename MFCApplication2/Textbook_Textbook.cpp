// Textbook_Textbook.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Textbook.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Textbook_Textbook_Add.h"
#include "Del_Ok.h"


// CTextbook_Textbook 对话框

IMPLEMENT_DYNAMIC(CTextbook_Textbook, CDialogEx)

CTextbook_Textbook::CTextbook_Textbook(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextbook_Textbook::IDD, pParent)
	, ADD_tag(0)
	, Find_type(0)
	, m_Textbook_Textbook_find_key(_T(""))
{

}

CTextbook_Textbook::~CTextbook_Textbook()
{
}

void CTextbook_Textbook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Textbook_Textbook_List, m_Textbook_Textbook_List);
	DDX_Text(pDX, IDC_Textbook_Textbook_find_key, m_Textbook_Textbook_find_key);
	DDX_Control(pDX, IDC_Textbook_Textbook_find_type, m_Textbook_Textbook_find_type);
}


BEGIN_MESSAGE_MAP(CTextbook_Textbook, CDialogEx)
	ON_BN_CLICKED(IDC_Textbook_Textbook_Del, &CTextbook_Textbook::OnBnClickedTextbookTextbookDel)
	ON_BN_CLICKED(IDC_Textbook_Textbook_Add, &CTextbook_Textbook::OnBnClickedTextbookTextbookAdd)
	ON_BN_CLICKED(IDC_Textbook_Textbook_All, &CTextbook_Textbook::OnBnClickedTextbookTextbookAll)
	ON_CBN_SELCHANGE(IDC_Textbook_Textbook_find_type, &CTextbook_Textbook::OnSelchangeTextbookTextbookFindType)
	ON_BN_CLICKED(IDC_Textbook_Textbook_find, &CTextbook_Textbook::OnBnClickedTextbookTextbookfind)
END_MESSAGE_MAP()


// CTextbook_Textbook 消息处理程序


BOOL CTextbook_Textbook::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (ADD_tag == 0)
	{
		CString str[4] = { _T("教材编号"), _T("教材名称"), _T("作者"), _T("出版社") };//初始化组合框
		int nIndex;
		for (int i = 0; i<4; i++)
		{
			nIndex = m_Textbook_Textbook_find_type.AddString(str[i]);
			m_Textbook_Textbook_find_type.SetItemData(nIndex, i);
		}
		m_Textbook_Textbook_find_type.SetCurSel(1);
		Find_type = 0;
	}

	m_Textbook_Textbook_List.DeleteAllItems();//清空List控件

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select * from books order by id asc");
	pRst = CDBO.ExecuteWithResSQL(sql);

	if (NULL == pRst)
	{
		MessageBox(_T("查询数据出现错误"));
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();
		MessageBox(_T("暂无教材信息"));
	}
	else
	{
		if (ADD_tag == 0)
		{
			m_Textbook_Textbook_List.InsertColumn(0, _T("教材编号"));//添加列  
			m_Textbook_Textbook_List.InsertColumn(1, _T("名称"));
			m_Textbook_Textbook_List.InsertColumn(2, _T("作者"));
			m_Textbook_Textbook_List.InsertColumn(3, _T("ISBN"));
			m_Textbook_Textbook_List.InsertColumn(4, _T("出版社"));
			m_Textbook_Textbook_List.SetColumnWidth(0, 100);//设置列宽  
			m_Textbook_Textbook_List.SetColumnWidth(1, 100);
			m_Textbook_Textbook_List.SetColumnWidth(2, 100);
			m_Textbook_Textbook_List.SetColumnWidth(3, 100);
			m_Textbook_Textbook_List.SetColumnWidth(4, 100);
			ADD_tag++;
		}

		_variant_t id, name, author, isbn, edition;
		CString str_id, str_name, str_author, str_isbn, str_edition;
		int i = 0;
		int nIndex;
		while (!pRst->adoEOF)
		{
			//pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
				str_edition.Format(_T(""));
			}
			else str_edition = (CString)edition;
			nIndex = m_Textbook_Textbook_List.InsertItem(i, str_id);
			m_Textbook_Textbook_List.SetItemText(nIndex, 1, str_name);
			m_Textbook_Textbook_List.SetItemText(nIndex, 2, str_author);
			m_Textbook_Textbook_List.SetItemText(nIndex, 3, str_isbn);
			m_Textbook_Textbook_List.SetItemText(nIndex, 4, str_edition);
			i++;
			pRst->MoveNext();
		}

		m_Textbook_Textbook_List.SetRedraw(TRUE);//显示 
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTextbook_Textbook::OnBnClickedTextbookTextbookDel()
{
	POSITION pos = m_Textbook_Textbook_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString str;

	if (pos == NULL) MessageBox(_T("未选中行！"));
	else
	{
		CDel_OK dlg;
		dlg.DoModal();

		if (m_ok == "1")
		{
			while (pos)
			{
				nIndex = m_Textbook_Textbook_List.GetNextSelectedItem(pos);
				str = m_Textbook_Textbook_List.GetItemText(nIndex, 0);//获得要删除项的id
			}

			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString strSql;
			strSql.Format(_T("delete from books where id='%s'"), str);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			m_Textbook_Textbook_List.DeleteItem(nIndex);
			MessageBox(_T("删除成功！"));
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Textbook::OnBnClickedTextbookTextbookAdd()
{
	CTextbook_Textbook_Add dlg;
	dlg.DoModal();
	OnInitDialog();
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Textbook::OnBnClickedTextbookTextbookAll()
{
	OnInitDialog();
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Textbook::OnSelchangeTextbookTextbookFindType()
{
	int nIndex = m_Textbook_Textbook_find_type.GetCurSel();
	if (nIndex != CB_ERR)
	{
		Find_type = m_Textbook_Textbook_find_type.GetItemData(nIndex);
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Textbook::OnBnClickedTextbookTextbookfind()
{
	UpdateData();

	m_Textbook_Textbook_List.DeleteAllItems();//清空List控件

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from books order by id asc"));
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("查询数据出现错误"));
	}
	if (CDBO.m_pRecordset->adoEOF)
	{
		CDBO.m_pRecordset->Close();
		MessageBox(_T("教材不存在"));
	}
	else
	{
		if (ADD_tag == 0)
		{
			m_Textbook_Textbook_List.InsertColumn(0, _T("教材编号"));//添加列  
			m_Textbook_Textbook_List.InsertColumn(1, _T("名称"));
			m_Textbook_Textbook_List.InsertColumn(2, _T("作者"));
			m_Textbook_Textbook_List.InsertColumn(3, _T("ISBN"));
			m_Textbook_Textbook_List.InsertColumn(4, _T("出版社"));
			m_Textbook_Textbook_List.SetColumnWidth(0, 100);//设置列宽  
			m_Textbook_Textbook_List.SetColumnWidth(1, 100);
			m_Textbook_Textbook_List.SetColumnWidth(2, 100);
			m_Textbook_Textbook_List.SetColumnWidth(3, 100);
			m_Textbook_Textbook_List.SetColumnWidth(4, 100);
			ADD_tag++;
		}

		_variant_t id, name, author, isbn, edition;
		CString str_id, str_name, str_author, str_isbn, str_edition;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			//pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
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
			int tag=0;
			if (Find_type == 0)
			{
				if (str_id.Find(m_Textbook_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 1)
			{
				if (str_name.Find(m_Textbook_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 2)
			{
				if (str_author.Find(m_Textbook_Textbook_find_key) != -1){ tag = 1; }
			}
			else if (Find_type == 3)
			{
				if (str_edition.Find(m_Textbook_Textbook_find_key) != -1){ tag = 1; }
			}
			
			if (tag != 0)
			{
				nIndex = m_Textbook_Textbook_List.InsertItem(i, str_id);
				m_Textbook_Textbook_List.SetItemText(nIndex, 1, str_name);
				m_Textbook_Textbook_List.SetItemText(nIndex, 2, str_author);
				m_Textbook_Textbook_List.SetItemText(nIndex, 3, str_isbn);
				m_Textbook_Textbook_List.SetItemText(nIndex, 4, str_edition);
				i++;
			}
			CDBO.m_pRecordset->MoveNext();
		}
		if (i == 0) { MessageBox(_T("教材不存在")); }

		m_Textbook_Textbook_List.SetRedraw(TRUE);//显示 
	}
	// TODO:  在此添加控件通知处理程序代码
}
