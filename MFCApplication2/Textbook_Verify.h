#pragma once
#include "afxcmn.h"


// CTextbook_Verify 对话框

class CTextbook_Verify : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Verify)

public:
	CTextbook_Verify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Verify();

// 对话框数据
	enum { IDD = IDD_Textbook_Verify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Verify_List;
	virtual BOOL OnInitDialog();
	int tag = 0;
	afx_msg void OnBnClickedTextbookVerifyfail();
	afx_msg void OnBnClickedTextbookVerifypass();
	afx_msg void OnBnClickedTextbookVerifyDetails();
};
