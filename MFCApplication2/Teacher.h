#pragma once
#include "afxcmn.h"
#include "Teacher_Information.h"
#include "Teacher_Demand.h"
#include "Teacher_Subscriptions.h"


// CTeacher 对话框

class CTeacher : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher)

public:
	CTeacher(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTeacher();

// 对话框数据
	enum { IDD = IDD_Teacher_Interface };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_Teacher_tab;
	CTeacher_Information m_Information;
	CTeacher_Demand m_Demand;
	CTeacher_Subscriptions m_Subscriptions;
	afx_msg void OnSelchangeTeacherTab(NMHDR *pNMHDR, LRESULT *pResult);
};
