#pragma once


// CTeacher_Information_Modify 对话框

class CTeacher_Information_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Information_Modify)

public:
	CTeacher_Information_Modify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTeacher_Information_Modify();

// 对话框数据
	enum { IDD = IDD_Teacher_Information_Modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
