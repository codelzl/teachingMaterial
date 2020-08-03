// Teacher_Subscriptions_Past.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher_Subscriptions_Past.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CTeacher_Subscriptions_Past 对话框

IMPLEMENT_DYNAMIC(CTeacher_Subscriptions_Past, CDialogEx)

CTeacher_Subscriptions_Past::CTeacher_Subscriptions_Past(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher_Subscriptions_Past::IDD, pParent)
	, tag(0)
	, order_id(_T(""))
{

}

CTeacher_Subscriptions_Past::~CTeacher_Subscriptions_Past()
{
}

void CTeacher_Subscriptions_Past::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Teacher_Subscriptions_Past_order_id, m_Teacher_Subscriptions_Past_order_id_List);
	DDX_Control(pDX, IDC_Teacher_Subscriptions_Past_order_details, m_Teacher_Subscriptions_Past_order_Details_List);
}


BEGIN_MESSAGE_MAP(CTeacher_Subscriptions_Past, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Teacher_Subscriptions_Past_order_id, &CTeacher_Subscriptions_Past::OnItemchangedTeacherSubscriptionsPastOrderId)
END_MESSAGE_MAP()


// CTeacher_Subscriptions_Past 消息处理程序


BOOL CTeacher_Subscriptions_Past::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Teacher_Subscriptions_Past_order_Details_List.DeleteAllItems();

	if (tag == 0)
	{
		m_Teacher_Subscriptions_Past_order_id_List.InsertColumn(0, _T("订单编号"));//添加列  
		m_Teacher_Subscriptions_Past_order_id_List.InsertColumn(1, _T("状态"));
		m_Teacher_Subscriptions_Past_order_id_List.InsertColumn(2, _T("订单时间"));
		m_Teacher_Subscriptions_Past_order_id_List.SetColumnWidth(0, 100);//设置列宽  
		m_Teacher_Subscriptions_Past_order_id_List.SetColumnWidth(1, 100);
		m_Teacher_Subscriptions_Past_order_id_List.SetColumnWidth(2, 100);

		m_Teacher_Subscriptions_Past_order_Details_List.InsertColumn(0, _T("教材编号"));//添加列  
		m_Teacher_Subscriptions_Past_order_Details_List.InsertColumn(1, _T("名称"));
		m_Teacher_Subscriptions_Past_order_Details_List.InsertColumn(2, _T("数量"));
		m_Teacher_Subscriptions_Past_order_Details_List.SetColumnWidth(0, 100);//设置列宽  
		m_Teacher_Subscriptions_Past_order_Details_List.SetColumnWidth(1, 100);
		m_Teacher_Subscriptions_Past_order_Details_List.SetColumnWidth(2, 100);
		tag++;
	}

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from orderone where user_id='%s'"), temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
	
	int i = 0;
	int nIndex;

	if (CDBO.m_pRecordset->adoEOF)
	{
		MessageBox(_T("暂无订单"));
	}
	else
	{
		while (!CDBO.m_pRecordset->adoEOF)
		{
			order_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_id"));
			nIndex = m_Teacher_Subscriptions_Past_order_id_List.InsertItem(i, order_id);
			CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
			if (state == "0")
			{
				state.Format(_T("未审核"));
			}
			else if (state == "1")
			{
				state.Format(_T("审核未通过"));
			}
			else if (state == "2")
			{
				state.Format(_T("审核通过"));
			}

			m_Teacher_Subscriptions_Past_order_id_List.SetItemText(nIndex, 1, state);
			m_Teacher_Subscriptions_Past_order_id_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_date")));
			CDBO.m_pRecordset->MoveNext();
			i++;
		}
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTeacher_Subscriptions_Past::OnItemchangedTeacherSubscriptionsPastOrderId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
	{
		POSITION pos = m_Teacher_Subscriptions_Past_order_id_List.GetFirstSelectedItemPosition();
		int nIndex;

		if (pos == NULL) MessageBox(_T("未选中行！"));
		else
		{
			while (pos)
			{
				nIndex = m_Teacher_Subscriptions_Past_order_id_List.GetNextSelectedItem(pos);
				order_id = m_Teacher_Subscriptions_Past_order_id_List.GetItemText(nIndex, 0);//获得id
			}
		}

		m_Teacher_Subscriptions_Past_order_Details_List.DeleteAllItems();

		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CDBOperation CDBO_bookname;
		CDBO_bookname.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("select * from ordertwo where order_id='%s'"), order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		while (!CDBO.m_pRecordset->adoEOF)
		{
			CString book_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id"));
			nIndex = m_Teacher_Subscriptions_Past_order_Details_List.InsertItem(0, book_id);

			sql.Format(_T("select * from books where id='%s'"), book_id);
			CDBO_bookname.m_pRecordset = CDBO_bookname.ExecuteWithResSQL((_bstr_t)sql);
			m_Teacher_Subscriptions_Past_order_Details_List.SetItemText(nIndex, 1, (CString)CDBO_bookname.m_pRecordset->GetCollect(_variant_t("name")));
			
			m_Teacher_Subscriptions_Past_order_Details_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("booknum")));
			CDBO.m_pRecordset->MoveNext();
		}
	}
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
