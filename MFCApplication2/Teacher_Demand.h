#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTeacher_Demand 对话框

class CTeacher_Demand : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Demand)

public:
	CTeacher_Demand(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTeacher_Demand();

// 对话框数据
	enum { IDD = IDD_Teacher_Demand };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_Teacher_Demand_List;
	CComboBox m_Teacher_Demand_find_type;
	CString m_Teacher_Demand_find_key;
	int Demand_tag = 0;
	int Find_type;
	afx_msg void OnSelchangeTeacherDemandFindType();
	afx_msg void OnBnClickedTeacherDemandfind();
	afx_msg void OnBnClickedTeacherDemandAddsubscription();
	CListCtrl m_Teacher_Demand_Order_List;
	int tag = 0;
	afx_msg void OnChangeTeacherDemandNum();
	CString m_Teacher_Demand_Num;
	afx_msg void OnItemchangedTeacherDemandOrderList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTeacherDemandDel();
	afx_msg void OnBnClickedTeacherDemandSubmit();
};
