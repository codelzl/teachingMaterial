#pragma once


// CAcademy_Information �Ի���

class CAcademy_Information : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Information)

public:
	CAcademy_Information(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAcademy_Information();

// �Ի�������
	enum { IDD = IDD_Academy_Information };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
