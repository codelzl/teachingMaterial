#pragma once
#include "afxcmn.h"


// CAcademy_Verify 对话框

class CAcademy_Verify : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Verify)

public:
	CAcademy_Verify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAcademy_Verify();

// 对话框数据
	enum { IDD = IDD_Academy_Verify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Academy_Verify_order_id_List;
	CListCtrl m_Academy_Verify_order_details_List;
	virtual BOOL OnInitDialog();
	int tag = 0;
	afx_msg void OnItemchangedAcademyVerifyOrderIdList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Academy_order_id;
	afx_msg void OnBnClickedAcademyVerifypass();
	afx_msg void OnBnClickedAcademyVerifyfail();
};
