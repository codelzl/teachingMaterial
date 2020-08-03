#pragma once
#include "afxcmn.h"
#include "Textbook_Teacher.h"
#include "Textbook_Textbook.h"
#include "Textbook_Information.h"
#include "Textbook_Notice.h"
#include "Textbook_Verify.h"
#include "Textbook_Academy.h"


// Textbook �Ի���

class CTextbook : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook)

public:
	CTextbook(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook();

// �Ի�������
	enum { IDD = IDD_Textbook_Interface };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Textbook_Tab;
	CTextbook_Teacher m_Teacher;
	CTextbook_Textbook m_Textbook;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTextbookTab(NMHDR *pNMHDR, LRESULT *pResult);
	CTextbook_Information m_Information;
	CTextbook_Notice m_Notice;
	CTextbook_Verify m_Verify;
	CTextbook_Academy m_Academy;
};
