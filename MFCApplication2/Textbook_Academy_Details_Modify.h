#pragma once


// CTextbook_Academy_Details_Modify �Ի���

class CTextbook_Academy_Details_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy_Details_Modify)

public:
	CTextbook_Academy_Details_Modify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Academy_Details_Modify();

// �Ի�������
	enum { IDD = IDD_Textbook_Academy_Details_Modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Academy_Details_Modify_name;
	CString m_Textbook_Academy_Details_Modify_password;
	virtual BOOL OnInitDialog();
	CString m_Textbook_Academy_Details_id;
	afx_msg void OnBnClickedTextbookAcademyDetailsModifySave();
};
