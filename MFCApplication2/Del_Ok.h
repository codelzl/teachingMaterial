#pragma once


// CDel_OK �Ի���

class CDel_OK : public CDialogEx
{
	DECLARE_DYNAMIC(CDel_OK)

public:
	CDel_OK(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDel_OK();

// �Ի�������
	enum { IDD = IDD_Del_OK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
};
