#pragma once
#include "afxcmn.h"


// CTeacher_Subscriptions �Ի���

class CTeacher_Subscriptions : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Subscriptions)

public:
	CTeacher_Subscriptions(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTeacher_Subscriptions();

// �Ի�������
	enum { IDD = IDD_Teacher_Subscriptions };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubscriptionsNew();
	CListCtrl m_Teacher_Subscriptions_List;
//	CString m_Teacher_Subscriptions_sum;
	virtual BOOL OnInitDialog();
	int tag = 0;
//	afx_msg void OnBnClickedTeacherSubscriptionsDel();
//	afx_msg void OnItemchangedTeacherSubscripitionsList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnChangeTeacherSubscriptionSum();
//	afx_msg void OnBnClickedTeacherSubscripitionsSubmit();
	CString m_Teacher_Subscriptions_bookid;
//	afx_msg void OnBnClickedTeacherSubscriptionsPast();
	CListCtrl m_Teacher_Subscriptions_Details_List;
	afx_msg void OnItemchangedTeacherSubscripitionsList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTeacherSubscriptionsDel();
};
