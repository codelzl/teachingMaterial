#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTextbook_Teacher �Ի���

class CTextbook_Teacher : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Teacher)

public:
	CTextbook_Teacher(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Teacher();

// �Ի�������
	enum { IDD = IDD_Textbook_Teacher };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_Textbook_Teacher_List;
//	CString m_Textbook_Teacher_find_type;
	CString m_Textbook_Teacher_find_key;
	int tag = 0;
	CComboBox m_Textbook_Teacher_find_type;
	int Find_type;
	afx_msg void OnSelchangeTextbookTeacherFindType();
	afx_msg void OnBnClickedTextbookTeacherFind();
};
