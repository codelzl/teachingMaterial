#pragma once


// CTextbook_Notice �Ի���

class CTextbook_Notice : public CDialogEx
{
	DECLARE_DYNAMIC(CTextbook_Notice)

public:
	CTextbook_Notice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextbook_Notice();

// �Ի�������
	enum { IDD = IDD_Textbook_Notice };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Textbook_Notice;
	afx_msg void OnBnClickedTextbookNoticeSave();
	virtual BOOL OnInitDialog();
	CString m_Notice_Time;
};
