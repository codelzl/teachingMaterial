#pragma once


// CTeacher_Information_Modify �Ի���

class CTeacher_Information_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacher_Information_Modify)

public:
	CTeacher_Information_Modify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTeacher_Information_Modify();

// �Ի�������
	enum { IDD = IDD_Teacher_Information_Modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
