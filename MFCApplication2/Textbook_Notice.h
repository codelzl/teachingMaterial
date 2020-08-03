#pragma once


// CTextbook_Notice 对话框

class CTextbook_Notice : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Notice)

public:
	CTextbook_Notice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextbook_Notice();

// 对话框数据
	enum { IDD = IDD_Textbook_Notice };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Notice;
	afx_msg void OnBnClickedTextbookNoticeSave();
	virtual BOOL OnInitDialog();
	CString m_Notice_Time;
};
