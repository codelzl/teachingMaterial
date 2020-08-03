#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAcademy_Teacher �Ի���

class CAcademy_Teacher : public CDialogEx
{
	DECLARE_DYNAMIC(CAcademy_Teacher)

public:
	CAcademy_Teacher(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAcademy_Teacher();

// �Ի�������
	enum { IDD = IDD_Academy_Teacher };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Academy_Teacher_List;
	CComboBox m_Academy_Teacher_find_type;
	CString m_Academy_Teacher_find_key;
	virtual BOOL OnInitDialog();
	int tag = 0;
	int Find_type;
	afx_msg void OnBnClickedAcademyTeacherAdd();
	afx_msg void OnBnClickedAcademyTeacherDel();
//	afx_msg void OnCbnSelchangeAcademyTeacherfindtype();
};
