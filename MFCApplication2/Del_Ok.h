#pragma once


// CDel_OK 对话框

class CDel_OK : public CDialogEx
{
	DECLARE_DYNAMIC(CDel_OK)

public:
	CDel_OK(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDel_OK();

// 对话框数据
	enum { IDD = IDD_Del_OK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
};
