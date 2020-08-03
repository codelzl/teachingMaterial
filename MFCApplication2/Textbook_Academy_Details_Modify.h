#pragma once


// CTextbook_Academy_Details_Modify 对话框

class CTextbook_Academy_Details_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy_Details_Modify)

public:
	CTextbook_Academy_Details_Modify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Academy_Details_Modify();

// 对话框数据
	enum { IDD = IDD_Textbook_Academy_Details_Modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Academy_Details_Modify_name;
	CString m_Textbook_Academy_Details_Modify_password;
	virtual BOOL OnInitDialog();
	CString m_Textbook_Academy_Details_id;
	afx_msg void OnBnClickedTextbookAcademyDetailsModifySave();
};
