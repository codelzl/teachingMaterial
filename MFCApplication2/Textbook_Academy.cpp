// Textbook_Academy.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Textbook_Academy.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Textbook_Academy_Add.h"
#include "Textbook_Academy_Details.h"
#include "Del_OK.h"


// CTextbook_Academy 对话框

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


// CTextbook_Academy 消息处理程序


BOOL CTextbook_Academy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Textbook_Academy_List.DeleteAllItems();//清空List控件

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	_RecordsetPtr pRst;
	char sql[255] = { 0 };
	strcpy_s(sql, "select id,name,state from my_user where type='2' order by id asc");
	pRst = CDBO.ExecuteWithResSQL(sql);

	if (NULL == pRst)
	{
		MessageBox(_T("查询数据出现错误"));
	}
	else if (pRst->adoEOF)
	{
		pRst->Close();
		MessageBox(_T("暂无学院信息"));
	}
	else
	{
		if (ADD_tag == 0)
		{
			m_Textbook_Academy_List.InsertColumn(0, _T("学院编号"));//添加列  
			m_Textbook_Academy_List.InsertColumn(1, _T("名称"));
			m_Textbook_Academy_List.InsertColumn(2, _T("教师"));
			m_Textbook_Academy_List.InsertColumn(3, _T("状态"));
			m_Textbook_Academy_List.SetColumnWidth(0, 100);//设置列宽  
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
			//pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
			id = pRst->GetCollect(_variant_t("id"));
			name = pRst->GetCollect(_variant_t("name"));
			state = pRst->GetCollect(_variant_t("state"));
			str_id = (CString)id;
			str_name = (CString)name;
			str_state = (CString)state;
			if (str_state == "0")
			{
				str_state.Format(_T("禁用"));
			}
			else if (str_state == "1")
			{
				str_state.Format(_T("可用"));
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

		m_Textbook_Academy_List.SetRedraw(TRUE);//显示 
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTextbook_Academy::OnBnClickedTextbookAcademyAdd()
{
	CTextbook_Academy_Add dlg;
	dlg.DoModal();
	OnInitDialog();
	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Academy::OnBnClickedTextbookAcademyDetails()
{
	POSITION pos = m_Textbook_Academy_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("请选择学院！"));
	else
	{
		CDBOperation CDBO;
		int nIndex;
		while (pos)
		{
			nIndex = m_Textbook_Academy_List.GetNextSelectedItem(pos);
			m_Textbook_Academy_Details_id = m_Textbook_Academy_List.GetItemText(nIndex, 0);//获得选中学院的id
		}

		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString strSql;
		strSql.Format(_T("select * from teacher where academy_id='%s'"), m_Textbook_Academy_Details_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

		if (CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("此学院暂无教师！"));
		}
		CTextbook_Academy_Details dlg;
		dlg.DoModal();
		OnInitDialog();
	}

	// TODO:  在此添加控件通知处理程序代码
}


void CTextbook_Academy::OnBnClickedTextbookAcademyDel()
{
	POSITION pos = m_Textbook_Academy_List.GetFirstSelectedItemPosition();

	if (pos == NULL) MessageBox(_T("未选中行！"));
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
				str = m_Textbook_Academy_List.GetItemText(nIndex, 0);//获得要删除项的id
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
				MessageBox(_T("删除成功！"));

				OnInitDialog();
			}
			else
			{
				MessageBox(_T("存在教师，删除失败！"));
			}
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}
