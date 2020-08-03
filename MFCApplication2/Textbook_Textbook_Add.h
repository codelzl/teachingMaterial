#pragma once


// CTextbook_Textbook_Add 对话框

class CTextbook_Textbook_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Textbook_Add)

public:
	CTextbook_Textbook_Add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Textbook_Add();

// 对话框数据
	enum { IDD = IDD_Textbook_Textbook_Add };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Textbook_Add_Id;
	CString m_Textbook_Textbook_Add_Name;
	CString m_Textbook_Textbook_Add_Author;
	CString m_Textbook_Textbook_Add_Isbn;
	afx_msg void OnBnClickedTextbookTextbookAdd();
	CString m_Textbook_Textbook_Add_Edition;
};
