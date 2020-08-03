#pragma once
#include "afxcmn.h"
#include "Academy_Information.h"
#include "Academy_Teacher.h"
#include "Acamedy_Textbook.h"
#include "Academy_Verify.h"


// Academy 对话框

class CAcademy : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy)

public:
	CAcademy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAcademy();

// 对话框数据
	enum { IDD = IDD_Academy_Interface };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
