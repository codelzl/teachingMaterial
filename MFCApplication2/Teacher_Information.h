#pragma once


// CTeacher_Information �Ի���

class CTeacher_Information : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Information)

public:
	CTeacher_Information(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTeacher_Information();

// �Ի�������
	enum { IDD = IDD_Teacher_Information };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedcancellation();
//	afx_msg void OnBnClickedcancellation();
//	afx_msg void OnBnClickedModify();
	CString m_Teacher_id;
//	afx_msg void OnStnClickedTeacherid();
	virtual BOOL OnInitDialog();
	CString m_Teacher_Information_Type;
	CString m_Teacher_name;
	CString m_Teacher_Information_password;
	afx_msg void OnBnClickedTeacherInformationsave();
	afx_msg void OnBnClickedTeacherDown();
};
