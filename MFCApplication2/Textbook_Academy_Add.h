#pragma once


// CTextbook_Academy_Add �Ի���

class CTextbook_Academy_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy_Add)

public:
	CTextbook_Academy_Add(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Academy_Add();

// �Ի�������
	enum { IDD = IDD_Textbook_Academy_Add };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTextbookAcademyAdd();
	CString m_Textbook_Academy_Add_id;
	CString m_Textbook_Academy_Add_name;
	CString m_Textbook_Academy_Add_password;
};
