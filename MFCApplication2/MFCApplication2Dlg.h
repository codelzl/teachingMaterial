
// MFCApplication2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Login_Interface };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginInterfaceRegister();
//	afx_msg void OnEnChangeLoginInterfaceEditPassword();
	afx_msg void OnBnClickedLoginInterfaceLogin();
	CComboBox m_login_interface;
	int m_login_type;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeLoginInterfaceEditNumber();
//	CEdit m_password;
//	CEdit m_user;
	CString m_user;
	CString m_password;
	CString m_Login_Notice;
	int tag = 0;
	CString m_Notice_Time;
};
