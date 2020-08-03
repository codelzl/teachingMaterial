#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTextbook_Academy_Details �Ի���

class CTextbook_Academy_Details : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy_Details)

public:
	CTextbook_Academy_Details(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Academy_Details();

// �Ի�������
	enum { IDD = IDD_Textbook_Academy_Details };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Academy_Details_List;
	virtual BOOL OnInitDialog();
	int tag = 0;
//	CComboBox m_Textbook_Academy_Details_find_type;
//	CString m_Textbook_Academy_Details_find_key;
//	afx_msg void OnBnClickedTextbookAcademyDetailsFind();
	int Find_type;
//	afx_msg void OnSelchangeTextbookAcademyDetailsFindType();
	afx_msg void OnBnClickedTextbookAcademyDetailsAdd();
	afx_msg void OnBnClickedTextbookAcademyDetailsDel();
	afx_msg void OnBnClickedTextbookAcademyDetailsModify();
	afx_msg void OnBnClickedTextbookAcademyDetailsState();
};
