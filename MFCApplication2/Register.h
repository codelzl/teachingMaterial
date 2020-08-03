#pragma once
#include "adodc1.h"
#include "datagrid1.h"
#include "afxwin.h"


// CRegister 对话框

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegister();

// 对话框数据
	enum { IDD = IDD_Register_Interface };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CAdodc1 m_adodc_teahcer;
	CDatagrid1 m_datagrid_teacher;
	afx_msg void OnBnClickedRegisterInterfaceRegister();
//	CEdit m_tno;
//	CEdit m_tpassword;
//	CAdodc1 m_adodc1;
	CString m_tno;
	CString m_tpassword;
	CAdodc1 m_adodc_teacher;
	CComboBox m_register_interface;
	virtual BOOL OnInitDialog();
	int m_register_type;
	afx_msg void OnCbnSelchangeCombo1();
};
