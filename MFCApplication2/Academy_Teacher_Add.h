#pragma once


// CAcademy_Teacher_Add �Ի���

class CAcademy_Teacher_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Teacher_Add)

public:
	CAcademy_Teacher_Add(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAcademy_Teacher_Add();

// �Ի�������
	enum { IDD = IDD_Academy_Teacher_Add };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Academy_Teacher_Add_name;
	CString m_Academy_Teacher_Add_password;
	afx_msg void OnBnClickedAcademyTeacherAddadd();
};
