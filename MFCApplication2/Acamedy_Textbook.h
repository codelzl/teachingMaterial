#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAcamedy_Textbook 对话框

class CAcademy_Textbook : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Textbook)

public:
	CAcademy_Textbook(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAcademy_Textbook();

// 对话框数据
	enum { IDD = IDD_Academy_Textbook };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_Academy_List;
	CListCtrl m_Academy_Textbook_List;
	virtual BOOL OnInitDialog();
	CComboBox m_Academy_Textbook_find_type;
	CString m_Academy_Textbook_find_key;
	int tag = 0;
	int Find_type;
	afx_msg void OnSelchangeAcademyTextbookFindType();
	afx_msg void OnBnClickedAcademyTextbookfind();
	afx_msg void OnBnClickedAcademyTextbookFindAll();
};
