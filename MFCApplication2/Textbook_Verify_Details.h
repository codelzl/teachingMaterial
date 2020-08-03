#pragma once
#include "afxcmn.h"


// CTextbook_Verify_Details 对话框

class CTextbook_Verify_Details : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Verify_Details)

public:
	CTextbook_Verify_Details(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Verify_Details();

// 对话框数据
	enum { IDD = IDD_Textbook_Verify_Details };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Verify_Details_List;
	virtual BOOL OnInitDialog();
};
