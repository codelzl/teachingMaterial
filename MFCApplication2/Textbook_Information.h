#pragma once


// CTextbook_Information 对话框

class CTextbook_Information : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Information)

public:
	CTextbook_Information(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Information();

// 对话框数据
	enum { IDD = IDD_Textbook_Information };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_Textbook_id;
//	CString m_Textbook_Interface_Textbook_sum;
	virtual BOOL OnInitDialog();
	CString m_Textbook_Information_id;
	CString m_Textbook_Information_password;
	afx_msg void OnBnClickedTextbookInformationsave();
	afx_msg void OnBnClickedTextbookDown();
};
