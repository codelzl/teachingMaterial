
// MFCApplication2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Login_Interface };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
