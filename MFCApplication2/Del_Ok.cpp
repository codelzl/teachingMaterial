// Del_OK.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Del_OK.h"
#include "afxdialogex.h"


// CDel_OK �Ի���

IMPLEMENT_DYNAMIC(CDel_OK, CDialogEx)

CDel_OK::CDel_OK(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDel_OK::IDD, pParent)
{

}

CDel_OK::~CDel_OK()
{
}

void CDel_OK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDel_OK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CDel_OK::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDel_OK ��Ϣ�������


BOOL CDel_OK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ok = "0";
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDel_OK::OnBnClickedButton3()
{
	m_ok = "1";
	CDel_OK::OnOK();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
