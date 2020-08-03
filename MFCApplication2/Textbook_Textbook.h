#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTextbook_Textbook �Ի���

class CTextbook_Textbook : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Textbook)

public:
	CTextbook_Textbook(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Textbook();

// �Ի�������
	enum { IDD = IDD_Textbook_Textbook };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Textbook_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTextbookTextbookDel();
	afx_msg void OnBnClickedTextbookTextbookAdd();
	int ADD_tag=0;
	afx_msg void OnBnClickedTextbookTextbookAll();
	int Find_type;
	CString m_Textbook_Textbook_find_key;
	CComboBox m_Textbook_Textbook_find_type;
	afx_msg void OnSelchangeTextbookTextbookFindType();
	afx_msg void OnBnClickedTextbookTextbookfind();
};
