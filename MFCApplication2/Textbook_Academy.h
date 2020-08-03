#pragma once
#include "afxcmn.h"


// CTextbook_Academy 对话框

class CTextbook_Academy : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy)

public:
	CTextbook_Academy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Academy();

// 对话框数据
	enum { IDD = IDD_Textbook_Academy };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Academy_List;
	virtual BOOL OnInitDialog();
	int ADD_tag = 0;
	afx_msg void OnBnClickedTextbookAcademyAdd();
	afx_msg void OnBnClickedTextbookAcademyDetails();
	afx_msg void OnBnClickedTextbookAcademyDel();
};
