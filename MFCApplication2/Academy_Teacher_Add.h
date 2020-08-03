#pragma once


// CAcademy_Teacher_Add 对话框

class CAcademy_Teacher_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Teacher_Add)

public:
	CAcademy_Teacher_Add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAcademy_Teacher_Add();

// 对话框数据
	enum { IDD = IDD_Academy_Teacher_Add };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Academy_Teacher_Add_name;
	CString m_Academy_Teacher_Add_password;
	afx_msg void OnBnClickedAcademyTeacherAddadd();
};
