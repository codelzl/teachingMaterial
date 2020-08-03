// Del_OK.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Del_OK.h"
#include "afxdialogex.h"


// CDel_OK 对话框

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


// CDel_OK 消息处理程序


BOOL CDel_OK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ok = "0";
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDel_OK::OnBnClickedButton3()
{
	m_ok = "1";
	CDel_OK::OnOK();
	// TODO:  在此添加控件通知处理程序代码
}
