#pragma once


// CTextbook_Academy_Details_Add �Ի���

class CTextbook_Academy_Details_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Academy_Details_Add)

public:
	CTextbook_Academy_Details_Add(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Academy_Details_Add();

// �Ի�������
	enum { IDD = IDD_Textbook_Academy_Details_Add };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Academy_Details_Add_name;
	CString m_Textbook_Academy_Details_Add_password;
	afx_msg void OnBnClickedTextbookAcademyDetailsAddadd();
};
