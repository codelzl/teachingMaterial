#pragma once
#include "afxcmn.h"


// CTextbook_Verify_Details �Ի���

class CTextbook_Verify_Details : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Verify_Details)

public:
	CTextbook_Verify_Details(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Verify_Details();

// �Ի�������
	enum { IDD = IDD_Textbook_Verify_Details };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Textbook_Verify_Details_List;
	virtual BOOL OnInitDialog();
};
