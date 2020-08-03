// Academy_Teacher.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Teacher.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Academy_Teacher_Add.h"
#include "Del_OK.h"


// CAcademy_Teacher 对话框

IMPLEMENT_DYNAMIC(CAcademy_Teacher, CDialogEx)

CAcademy_Teacher::CAcademy_Teacher(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy_Teacher::IDD, pParent)
	, m_Academy_Teacher_find_key(_T(""))
	, tag(0)
	, Find_type(0)
{

}

CAcademy_Teacher::~CAcademy_Teacher()
{
}

void CAcademy_Teacher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Academy_Teacher_LIST, m_Academy_Teacher_List);
	DDX_Control(pDX, IDC_Academy_Teacher_find_type, m_Academy_Teacher_find_type);
	DDX_Text(pDX, IDC_Academy_Teacher_find_key, m_Academy_Teacher_find_key);
}


BEGIN_MESSAGE_MAP(CAcademy_Teacher, CDialogEx)
	ON_BN_CLICKED(IDC_Academy_Teacher_Add, &CAcademy_Teacher::OnBnClickedAcademyTeacherAdd)
	ON_BN_CLICKED(IDC_Academy_Teacher_Del, &CAcademy_Teacher::OnBnClickedAcademyTeacherDel)
END_MESSAGE_MAP()


// CAcademy_Teacher 消息处理程序


BOOL CAcademy_Teacher::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (tag == 0)
	{
		CString str[3] = { _T("教师编号"), _T("教师姓名"), _T("用户状态") };
		int nIndex;
		for (int i = 0; i < 3; i++)
		{
			nIndex = m_Academy_Teacher_find_type.AddString(str[i]);
			m_Academy_Teacher_find_type.SetItemData(nIndex, i);
		}
		m_Academy_Teacher_find_type.SetCurSel(1);
		Find_type = 0;
	}

	m_Academy_Teacher_List.DeleteAllItems();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from teacher where academy_id='%s' order by id asc"), temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("查询数据出现错误"));
	}
	if (CDBO.m_pRecordset->adoEOF)
	{
		CDBO.m_pRecordset->Close();
		MessageBox(_T("There is no records in this table"));
	}
	else
	{
		if (tag == 0)
		{
			m_Academy_Teacher_List.InsertColumn(0, _T("教师编号"));//添加列  
			m_Academy_Teacher_List.InsertColumn(1, _T("教师姓名"));
			m_Academy_Teacher_List.InsertColumn(2, _T("用户状态"));
			m_Academy_Teacher_List.SetColumnWidth(0, 100);//设置列宽  
			m_Academy_Teacher_List.SetColumnWidth(1, 100);
			m_Academy_Teacher_List.SetColumnWidth(2, 100);
			tag++;
		}

		_variant_t id, name, state;
		CString str_id, str_name, str_state;
		int i = 0;
		int nIndex;
		while (!CDBO.m_pRecordset->adoEOF)
		{
			//pRst->MoveFirst(); //记录集指针移动到查询结果集的前面
			id = CDBO.m_pRecordset->GetCollect(_variant_t("id"));
			name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
			state = CDBO.m_pRecordset->GetCollect(_variant_t("state"));
			str_id = (CString)id;
			str_state = (CString)state;
			if (str_state == "1")
			{
				str_state.Format(_T("禁用"));
			}
			else if (str_state == "2")
			{
				str_state.Format(_T("可用"));
			}
			if (name.vt == VT_NULL)
			{
				str_name.Format(_T(""));
			}
			else str_name = (CString)name;
			nIndex = m_Academy_Teacher_List.InsertItem(i, str_id);
			m_Academy_Teacher_List.SetItemText(nIndex, 1, str_name);
			m_Academy_Teacher_List.SetItemText(nIndex, 2, str_state);
			i++;
			CDBO.m_pRecordset->MoveNext();
		}

		m_Academy_Teacher_List.SetRedraw(TRUE);//显示 
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAcademy_Teacher::OnBnClickedAcademyTeacherAdd()
{
	CAcademy_Teacher_Add dlg;
	dlg.DoModal();
	OnInitDialog();
	// TODO:  在此添加控件通知处理程序代码
}


void CAcademy_Teacher::OnBnClickedAcademyTeacherDel()
{
	POSITION pos = m_Academy_Teacher_List.GetFirstSelectedItemPosition();

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
				nIndex = m_Academy_Teacher_List.GetNextSelectedItem(pos);
				str = m_Academy_Teacher_List.GetItemText(nIndex, 0);//获得要删除项的id
			}

			CDBOperation CDBO;
			bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			CString strSql;
			strSql.Format(_T("delete from teacher where id='%s'"), str);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

			m_Academy_Teacher_List.DeleteItem(nIndex);
			MessageBox(_T("删除成功！"));

			OnInitDialog();
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}
