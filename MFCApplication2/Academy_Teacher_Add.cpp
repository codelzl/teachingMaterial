// Academy_Teacher_Add.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Teacher_Add.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CAcademy_Teacher_Add 对话框

IMPLEMENT_DYNAMIC(CAcademy_Teacher_Add, CDialogEx)

CAcademy_Teacher_Add::CAcademy_Teacher_Add(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy_Teacher_Add::IDD, pParent)
	, m_Academy_Teacher_Add_name(_T(""))
	, m_Academy_Teacher_Add_password(_T(""))
{

}

CAcademy_Teacher_Add::~CAcademy_Teacher_Add()
{
}

void CAcademy_Teacher_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Academy_Teacher_Add_name, m_Academy_Teacher_Add_name);
	DDX_Text(pDX, IDC_Academy_Teacher_Add_password, m_Academy_Teacher_Add_password);
}


BEGIN_MESSAGE_MAP(CAcademy_Teacher_Add, CDialogEx)
	ON_BN_CLICKED(IDC_Academy_Teacher_Add_add, &CAcademy_Teacher_Add::OnBnClickedAcademyTeacherAddadd)
END_MESSAGE_MAP()


// CAcademy_Teacher_Add 消息处理程序


void CAcademy_Teacher_Add::OnBnClickedAcademyTeacherAddadd()
{
	UpdateData();
	if (m_Academy_Teacher_Add_password.IsEmpty())
	{
		MessageBox(_T("请输入用户密码"));
	}
	else
	{
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

		/*CTime t = CTime::GetCurrentTime();*/
		CString str;

		CString sql;
		sql.Format(_T("insert into teacher(name,academy_id,state,password) values(%s,'%s',2,'%s')"), m_Academy_Teacher_Add_name, temp, m_Academy_Teacher_Add_password);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		sql.Format(_T("select * from teacher where name='%s' and academy_id='%s' and state='2' and password='%s'"), m_Academy_Teacher_Add_name, temp, m_Academy_Teacher_Add_password);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)sql);

		str = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("id"));

		CAcademy_Teacher_Add::OnOK();

		CString strMsg;
		strMsg.Format(_T("教师编号：%s"), str, str);

		MessageBox(strMsg);
	}
	// TODO:  在此添加控件通知处理程序代码
}
