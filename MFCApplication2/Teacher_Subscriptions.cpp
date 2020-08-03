// Teacher_Subscriptions.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher_Subscriptions.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "Teacher_Subscriptions_Past.h"


// CTeacher_Subscriptions �Ի���

IMPLEMENT_DYNAMIC(CTeacher_Subscriptions, CDialogEx)

CTeacher_Subscriptions::CTeacher_Subscriptions(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher_Subscriptions::IDD, pParent)
	, tag(0)
	, m_Teacher_Subscriptions_bookid(_T(""))
{

}

CTeacher_Subscriptions::~CTeacher_Subscriptions()
{
}

void CTeacher_Subscriptions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Teacher_Subscripitions_List, m_Teacher_Subscriptions_List);
	//  DDX_Text(pDX, IDC_Teacher_Subscription_sum, m_Teacher_Subscriptions_sum);
	DDX_Control(pDX, IDC_Teacher_SubScriptions_Details, m_Teacher_Subscriptions_Details_List);
}


BEGIN_MESSAGE_MAP(CTeacher_Subscriptions, CDialogEx)
//	ON_BN_CLICKED(IDC_Teacher_Subscriptions_Del, &CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsDel)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Teacher_Subscripitions_List, &CTeacher_Subscriptions::OnItemchangedTeacherSubscripitionsList)
//	ON_EN_CHANGE(IDC_Teacher_Subscription_sum, &CTeacher_Subscriptions::OnChangeTeacherSubscriptionSum)
//	ON_BN_CLICKED(IDC_Teacher_Subscripitions_Submit, &CTeacher_Subscriptions::OnBnClickedTeacherSubscripitionsSubmit)
//	ON_BN_CLICKED(IDC_Teacher_Subscriptions_Past, &CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsPast)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Teacher_Subscripitions_List, &CTeacher_Subscriptions::OnItemchangedTeacherSubscripitionsList)
	ON_BN_CLICKED(IDC_Teacher_Subscriptions_Del, &CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsDel)
END_MESSAGE_MAP()


// CTeacher_Subscriptions ��Ϣ�������


BOOL CTeacher_Subscriptions::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Teacher_Subscriptions_List.DeleteAllItems();//���List�ؼ�
	m_Teacher_Subscriptions_Details_List.DeleteAllItems();

	if (tag == 0)
	{
		m_Teacher_Subscriptions_List.InsertColumn(0, _T("�������"));//�����  
		m_Teacher_Subscriptions_List.InsertColumn(1, _T("״̬"));
		m_Teacher_Subscriptions_List.InsertColumn(2, _T("����ʱ��"));
		m_Teacher_Subscriptions_List.SetColumnWidth(0, 100);//�����п�  
		m_Teacher_Subscriptions_List.SetColumnWidth(1, 100);
		m_Teacher_Subscriptions_List.SetColumnWidth(2, 280);

		m_Teacher_Subscriptions_Details_List.InsertColumn(0, _T("�̲ı��"));//�����  
		m_Teacher_Subscriptions_Details_List.InsertColumn(1, _T("����"));
		m_Teacher_Subscriptions_Details_List.InsertColumn(2, _T("����"));
		m_Teacher_Subscriptions_Details_List.SetColumnWidth(0, 100);//�����п�  
		m_Teacher_Subscriptions_Details_List.SetColumnWidth(1, 100);
		m_Teacher_Subscriptions_Details_List.SetColumnWidth(2, 100);
		tag++;
	}

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from orderone where user_id=%s"), temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	int i = 0;
	int nIndex;

	{
		while (!CDBO.m_pRecordset->adoEOF)
		{
			CString order_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_id"));
			nIndex = m_Teacher_Subscriptions_List.InsertItem(i, order_id);
			CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
			if (state == "0")
			{
				state.Format(_T("δ���"));
			}
			else if (state == "1")
			{
				state.Format(_T("���δͨ��"));
			}
			else if (state == "2")
			{
				state.Format(_T("�ȴ����"));
			}
			else if (state == "3")
			{
				state.Format(_T("���δͨ��"));
			}
			else if (state == "4")
			{
				state.Format(_T("���ͨ��"));
			}

			m_Teacher_Subscriptions_List.SetItemText(nIndex, 1, state);
			m_Teacher_Subscriptions_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("order_date")));
			CDBO.m_pRecordset->MoveNext();
			i++;
		}
	}

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//void CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsDel()
//{
//	POSITION pos = m_Teacher_Subscriptions_List.GetFirstSelectedItemPosition();
//	int nIndex;
//	CString str;
//
//	if (pos == NULL) MessageBox(_T("δѡ���У�"));
//	else
//	{
//		while (pos)
//		{
//			nIndex = m_Teacher_Subscriptions_List.GetNextSelectedItem(pos);
//			str = m_Teacher_Subscriptions_List.GetItemText(nIndex, 0);//���Ҫɾ�����id
//		}
//		m_Teacher_Subscriptions_List.DeleteItem(nIndex);
//	}
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CTeacher_Subscriptions::OnItemchangedTeacherSubscripitionsList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//
//	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
//	{
//		POSITION pos = m_Teacher_Subscriptions_List.GetFirstSelectedItemPosition();
//		int nIndex;
//		CString str;
//
//		if (pos == NULL) MessageBox(_T("δѡ���У�"));
//		else
//		{
//			while (pos)
//			{
//				nIndex = m_Teacher_Subscriptions_List.GetNextSelectedItem(pos);
//				str = m_Teacher_Subscriptions_List.GetItemText(nIndex, 0);//���id
//			}
//			m_Teacher_Subscriptions_sum = m_Teacher_Subscriptions_List.GetItemText(nIndex, 2);
//			UpdateData(false);
//		}
//	}
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


//void CTeacher_Subscriptions::OnChangeTeacherSubscriptionSum()
//{
//	UpdateData();
//
//	POSITION pos = m_Teacher_Subscriptions_List.GetFirstSelectedItemPosition();
//	int nIndex;
//	CString str;
//
//	if (pos == NULL) MessageBox(_T("δѡ���У�"));
//	else
//	{
//		while (pos)
//		{
//			nIndex = m_Teacher_Subscriptions_List.GetNextSelectedItem(pos);
//			str = m_Teacher_Subscriptions_List.GetItemText(nIndex, 0);//���id
//		}
//		m_Teacher_Subscriptions_List.SetItemText(nIndex, 2, m_Teacher_Subscriptions_sum);
//		UpdateData(false);
//	}
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CTeacher_Subscriptions::OnBnClickedTeacherSubscripitionsSubmit()
//{
//	CDBOperation CDBO;
//	CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
//	
//	CString sql;
//	sql.Format(_T("select * from teacher where id=%s"), temp);
//	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
//	CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
//
//	if (state == "2")//1���ã�2����
//	{
//		CTime time = CTime::GetCurrentTime();
//		CString Subscriptions_id = time.Format("%Y%m%d%H%M%S");
//		int i = m_Teacher_Subscriptions_List.GetItemCount();
//
//		//CDBOperation CDBO;
//		//bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
//
//		sql.Format(_T("insert into orderone(order_id,user_id,state,order_date) values('%s','%s','0','%s')"), Subscriptions_id, temp, Subscriptions_id);
//		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
//		for (int j = 0; j < i; j++)
//		{
//			sql.Format(_T("insert into ordertwo values('%s','%s','%s')"), Subscriptions_id, m_Teacher_Subscriptions_List.GetItemText(j, 0), m_Teacher_Subscriptions_List.GetItemText(j, 2));
//			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
//		}
//
//		MessageBox(_T("�ύ�ɹ�"));
//
//		m_Teacher_Subscriptions_List.DeleteAllItems();
//	}
//	else if (state == "1")
//	{
//		MessageBox(_T("�Բ��������˺��ѱ�����"));
//	}
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsPast()
//{
//	CTeacher_Subscriptions_Past dlg;
//	dlg.DoModal();
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CTeacher_Subscriptions::OnItemchangedTeacherSubscripitionsList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
	{
		m_Teacher_Subscriptions_Details_List.DeleteAllItems();

		POSITION pos = m_Teacher_Subscriptions_List.GetFirstSelectedItemPosition();
		int nIndex;
		CString order_id;

		if (pos == NULL) MessageBox(_T("δѡ���У�"));
		else
		{
			while (pos)
			{
				nIndex = m_Teacher_Subscriptions_List.GetNextSelectedItem(pos);
				order_id = m_Teacher_Subscriptions_List.GetItemText(nIndex, 0);//���id
			}
		}

		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CDBOperation CDBO_bookname;
		CDBO_bookname.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("select * from ordertwo where order_id=%s"), order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		while (!CDBO.m_pRecordset->adoEOF)
		{
			CString book_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id"));
			nIndex = m_Teacher_Subscriptions_Details_List.InsertItem(0, book_id);

			sql.Format(_T("select * from books where id='%s'"), book_id);
			CDBO_bookname.m_pRecordset = CDBO_bookname.ExecuteWithResSQL((_bstr_t)sql);
			m_Teacher_Subscriptions_Details_List.SetItemText(nIndex, 1, (CString)CDBO_bookname.m_pRecordset->GetCollect(_variant_t("name")));

			m_Teacher_Subscriptions_Details_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("booknum")));
			CDBO.m_pRecordset->MoveNext();
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTeacher_Subscriptions::OnBnClickedTeacherSubscriptionsDel()
{
	POSITION pos = m_Teacher_Subscriptions_List.GetFirstSelectedItemPosition();
	int nIndex;
	CString order_id;

	if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else
	{
		while (pos)
		{
			nIndex = m_Teacher_Subscriptions_List.GetNextSelectedItem(pos);
			order_id = m_Teacher_Subscriptions_List.GetItemText(nIndex, 0);//���id
		}

		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("select * from orderone where order_id=%s"), order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		CString state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
		if (state == "0")
		{
			sql.Format(_T("delete from orderone where order_id=%s"), order_id);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

			sql.Format(_T("delete from ordertwo where order_id=%s"), order_id);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			MessageBox(_T("�����ɹ�"));
			OnInitDialog();
		}
		else
		{
			MessageBox(_T("�ö���������˻���ͨ����ˣ��޷�����"));
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
