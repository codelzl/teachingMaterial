#pragma once
#include "afxcmn.h"


// CTeacher_Subscriptions_Past �Ի���

class CTeacher_Subscriptions_Past : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Subscriptions_Past)

public:
	CTeacher_Subscriptions_Past(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTeacher_Subscriptions_Past();

// �Ի�������
	enum { IDD = IDD_Teacher_Subscriptions_Past };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CListCtrl m_Teacher_Subscriptions_order_id_List;
	CListCtrl m_Teacher_Subscriptions_Past_order_id_List;
	CListCtrl m_Teacher_Subscriptions_Past_order_Details_List;
	int tag = 0;
	afx_msg void OnItemchangedTeacherSubscriptionsPastOrderId(NMHDR *pNMHDR, LRESULT *pResult);
	CString order_id;
};
