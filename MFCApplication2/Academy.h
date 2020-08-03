#pragma once
#include "afxcmn.h"
#include "Academy_Information.h"
#include "Academy_Teacher.h"
#include "Acamedy_Textbook.h"
#include "Academy_Verify.h"


// Academy �Ի���

class CAcademy : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy)

public:
	CAcademy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAcademy();

// �Ի�������
	enum { IDD = IDD_Academy_Interface };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Academy_Tab;
	virtual BOOL OnInitDialog();
	CAcademy_Information m_Information;
	afx_msg void OnSelchangeAcademyTab(NMHDR *pNMHDR, LRESULT *pResult);
	CAcademy_Teacher m_Teacher;
	CAcademy_Textbook m_Textbook;
	CAcademy_Verify m_Verify;
};
