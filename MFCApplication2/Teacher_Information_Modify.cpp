// Teacher_Information_Modify.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Teacher_Information_Modify.h"
#include "afxdialogex.h"


// CTeacher_Information_Modify 对话框

IMPLEMENT_DYNAMIC(CTeacher_Information_Modify, CDialogEx)

CTeacher_Information_Modify::CTeacher_Information_Modify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeacher_Information_Modify::IDD, pParent)
{

}

CTeacher_Information_Modify::~CTeacher_Information_Modify()
{
}

void CTeacher_Information_Modify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTeacher_Information_Modify, CDialogEx)
	ON_BN_CLICKED(IDC_Cancel, &CTeacher_Information_Modify::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTeacher_Information_Modify 消息处理程序


void CTeacher_Information_Modify::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CTeacher_Information_Modify::OnOK();
}
