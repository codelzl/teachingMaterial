#pragma once
#include "afxcmn.h"


// CTextbook_Academy �Ի���

class CTextbook_Academy : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy)

public:
	CTextbook_Academy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Academy();

// �Ի�������
	enum { IDD = IDD_Textbook_Academy };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Academy_List;
	virtual BOOL OnInitDialog();
	int ADD_tag = 0;
	afx_msg void OnBnClickedTextbookAcademyAdd();
	afx_msg void OnBnClickedTextbookAcademyDetails();
	afx_msg void OnBnClickedTextbookAcademyDel();
};
