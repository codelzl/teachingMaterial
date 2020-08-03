#pragma once


// CAcademy_Information 对话框

class CAcademy_Information : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Information)

public:
	CAcademy_Information(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAcademy_Information();

// 对话框数据
	enum { IDD = IDD_Academy_Information };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_Academy_id;
	virtual BOOL OnInitDialog();
	CString m_Academy_Information_id;
	CString m_Academy_Information_name;
	CString m_Academy_Information_password;
	afx_msg void OnBnClickedAcademyInformationsave();
	afx_msg void OnBnClickedAcademyDown();
};
