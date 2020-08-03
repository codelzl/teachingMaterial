// Academy_Verify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Verify.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CAcademy_Verify �Ի���

IMPLEMENT_DYNAMIC(CAcademy_Verify, CDialogEx)

CAcademy_Verify::CAcademy_Verify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy_Verify::IDD, pParent)
	, tag(0)
	, m_Academy_order_id(_T(""))
{

}

CAcademy_Verify::~CAcademy_Verify()
{
}

void CAcademy_Verify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Academy_Verify_order_id_LIST, m_Academy_Verify_order_id_List);
	DDX_Control(pDX, IDC_Academy_Verify_order_details_LIST, m_Academy_Verify_order_details_List);
}


BEGIN_MESSAGE_MAP(CAcademy_Verify, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Academy_Verify_order_id_LIST, &CAcademy_Verify::OnItemchangedAcademyVerifyOrderIdList)
	ON_BN_CLICKED(IDC_Academy_Verify_pass, &CAcademy_Verify::OnBnClickedAcademyVerifypass)
	ON_BN_CLICKED(IDC_Academy_Verify_fail, &CAcademy_Verify::OnBnClickedAcademyVerifyfail)
END_MESSAGE_MAP()


// CAcademy_Verify ��Ϣ�������


BOOL CAcademy_Verify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Academy_Verify_order_details_List.DeleteAllItems();
	m_Academy_Verify_order_id_List.DeleteAllItems();

	if (tag == 0)
	{
		m_Academy_Verify_order_id_List.InsertColumn(0, _T("�������"));//�����  
		m_Academy_Verify_order_id_List.InsertColumn(1, _T("�ύ��ʦ"));
		m_Academy_Verify_order_id_List.InsertColumn(2, _T("״̬"));
		m_Academy_Verify_order_id_List.InsertColumn(3, _T("����ʱ��"));
		m_Academy_Verify_order_id_List.SetColumnWidth(0, 100);//�����п�  
		m_Academy_Verify_order_id_List.SetColumnWidth(1, 100);
		m_Academy_Verify_order_id_List.SetColumnWidth(2, 100);
		m_Academy_Verify_order_id_List.SetColumnWidth(3, 100);

		m_Academy_Verify_order_details_List.InsertColumn(0, _T("�̲ı��"));//�����  
		m_Academy_Verify_order_details_List.InsertColumn(1, _T("����"));
		m_Academy_Verify_order_details_List.InsertColumn(2, _T("����"));
		m_Academy_Verify_order_details_List.SetColumnWidth(0, 100);//�����п�  
		m_Academy_Verify_order_details_List.SetColumnWidth(1, 100);
		m_Academy_Verify_order_details_List.SetColumnWidth(2, 100);
		tag++;
	}

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString sql;
	sql.Format(_T("select * from teacher where academy_id='%s'"), temp);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

	while (!CDBO.m_pRecordset->adoEOF)
	{
		CString teacher_id = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("id"));

		CDBOperation CDBO_order;
		CDBO_order.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		sql.Format(_T("select * from orderone where user_id=%s"), teacher_id);
		CDBO_order.m_pRecordset = CDBO_order.ExecuteWithResSQL((_bstr_t)sql);

		while (!CDBO_order.m_pRecordset->adoEOF)
		{
			int i = 0;
			int nIndex;

			CString order_id = (CString)CDBO_order.m_pRecordset->GetCollect(_variant_t("order_id"));
			nIndex = m_Academy_Verify_order_id_List.InsertItem(i, order_id);
			CString state = (CString)CDBO_order.m_pRecordset->GetCollect(_variant_t("state"));
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

			CDBOperation CDBO_teacher;
			CDBO_teacher.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			sql.Format(_T("select * from teacher where id=%s"), teacher_id);
			CDBO_teacher.m_pRecordset = CDBO_teacher.ExecuteWithResSQL((_bstr_t)sql);

			m_Academy_Verify_order_id_List.SetItemText(nIndex, 1, (CString)CDBO_teacher.m_pRecordset->GetCollect(_variant_t("name")));
			m_Academy_Verify_order_id_List.SetItemText(nIndex, 2, state);
			m_Academy_Verify_order_id_List.SetItemText(nIndex, 3, (CString)CDBO_order.m_pRecordset->GetCollect(_variant_t("order_date")));
			CDBO_order.m_pRecordset->MoveNext();
			i++;
		}
		CDBO.m_pRecordset->MoveNext();
	}

	if (!m_Academy_order_id.IsEmpty())
	{
		sql.Format(_T("select * from ordertwo where order_id='%s'"), m_Academy_order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		while (!CDBO.m_pRecordset->adoEOF)
		{
			int i = 0;
			int nIndex;

			nIndex = m_Academy_Verify_order_details_List.InsertItem(0, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id")));
			
			CDBOperation CDBO_book;
			CDBO_book.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

			sql.Format(_T("select * from books where id='%s'"), (CString)CDBO.m_pRecordset->GetCollect(_variant_t("book_id")));
			CDBO_book.m_pRecordset = CDBO_book.ExecuteWithResSQL((_bstr_t)sql);
			m_Academy_Verify_order_details_List.SetItemText(nIndex, 1, (CString)CDBO_book.m_pRecordset->GetCollect(_variant_t("name")));
			
			m_Academy_Verify_order_details_List.SetItemText(nIndex, 2, (CString)CDBO.m_pRecordset->GetCollect(_variant_t("booknum")));

			CDBO.m_pRecordset->MoveNext();
		}
	}

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAcademy_Verify::OnItemchangedAcademyVerifyOrderIdList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
	{
		POSITION pos = m_Academy_Verify_order_id_List.GetFirstSelectedItemPosition();
		int nIndex;
		CString str;

		if (pos == NULL) MessageBox(_T("δѡ���У�"));
		else
		{
			while (pos)
			{
				nIndex = m_Academy_Verify_order_id_List.GetNextSelectedItem(pos);
				str = m_Academy_Verify_order_id_List.GetItemText(nIndex, 0);//���id
			}
			m_Academy_order_id = str;
			OnInitDialog();
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CAcademy_Verify::OnBnClickedAcademyVerifypass()
{
	POSITION pos = m_Academy_Verify_order_id_List.GetFirstSelectedItemPosition();
	//int nIndex;
	CString str;

	/*if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else*/
	{
		/*while (pos)
		{
			nIndex = m_Academy_Verify_order_id_List.GetNextSelectedItem(pos);
			str = m_Academy_Verify_order_id_List.GetItemText(nIndex, 0);//���id
		}*/				
		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;

		sql.Format(_T("select * from orderone where order_id=%s"), m_Academy_order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		CString state;
		state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));
		
		if (state == "3"||state=="4")
		{
			MessageBox(_T("�޸�ʧ��"));
		}
		else
		{
			sql.Format(_T("update orderone set state='2' where order_id='%s'"), m_Academy_order_id);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			OnInitDialog();
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAcademy_Verify::OnBnClickedAcademyVerifyfail()
{
	POSITION pos = m_Academy_Verify_order_id_List.GetFirstSelectedItemPosition();
	//int nIndex;
	CString str;

	/*if (pos == NULL) MessageBox(_T("δѡ���У�"));
	else*/
	{
		/*while (pos)
		{
		nIndex = m_Academy_Verify_order_id_List.GetNextSelectedItem(pos);
		str = m_Academy_Verify_order_id_List.GetItemText(nIndex, 0);//���id
		}*/
		CDBOperation CDBO;
		CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		CString sql;
		sql.Format(_T("select * from orderone where order_id=%s"), m_Academy_order_id);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
		CString state;
		state = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("state"));

		if (state == "3" || state == "4")
		{
			MessageBox(_T("�޸�ʧ��"));
		}
		else
		{
			sql.Format(_T("update orderone set state='1' where order_id='%s'"), m_Academy_order_id);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);
			OnInitDialog();
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
