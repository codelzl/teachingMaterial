// Academy_Information.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Information.h"
#include "afxdialogex.h"
#include "ADOConn.h"
#include "MFCApplication2Dlg.h"


// CAcademy_Information 对话框

IMPLEMENT_DYNAMIC(CAcademy_Information, CDialogEx)

CAcademy_Information::CAcademy_Information(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcademy_Information::IDD, pParent)
	, m_Academy_Information_id(_T(""))
	, m_Academy_Information_name(_T(""))
	, m_Academy_Information_password(_T(""))
{

}

CAcademy_Information::~CAcademy_Information()
{
}

void CAcademy_Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_Academy_id, m_Academy_id);
	DDX_Text(pDX, IDC_Academy_Information_id, m_Academy_Information_id);
	DDX_Text(pDX, IDC_Academy_Information_name, m_Academy_Information_name);
	DDX_Text(pDX, IDC_Academy_Information_password, m_Academy_Information_password);
}


BEGIN_MESSAGE_MAP(CAcademy_Information, CDialogEx)
	ON_BN_CLICKED(IDC_Academy_Information_save, &CAcademy_Information::OnBnClickedAcademyInformationsave)
	ON_BN_CLICKED(IDC_Academy_Down, &CAcademy_Information::OnBnClickedAcademyDown)
END_MESSAGE_MAP()


// CAcademy_Information 消息处理程序


BOOL CAcademy_Information::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Academy_Information_id = temp;

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("select * from my_user where type='2' and id='%s'"), m_Academy_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	if (NULL == CDBO.m_pRecordset)
	{
		MessageBox(_T("查询数据出现错误"));
	}
	else
	{
		_variant_t name;
		name = CDBO.m_pRecordset->GetCollect(_variant_t("name"));
		m_Academy_Information_password = (CString)CDBO.m_pRecordset->GetCollect(_variant_t("password"));
		if (name.vt == VT_NULL)
		{
			m_Academy_Information_name.Format(_T(""));
		}
		else m_Academy_Information_name = (CString)name;
	}

	UpdateData(false);
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAcademy_Information::OnBnClickedAcademyInformationsave()
{
	UpdateData();

	CDBOperation CDBO;
	bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");

	CString strSql;
	strSql.Format(_T("update my_user set name='%s',password='%s' where type='2' and id='%s'"), m_Academy_Information_name, m_Academy_Information_password, m_Academy_Information_id);
	CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);

	MessageBox(_T("保存成功"));
	// TODO:  在此添加控件通知处理程序代码
}


void CAcademy_Information::OnBnClickedAcademyDown()
{
	CAcademy_Information::OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);

	CMFCApplication2Dlg dlg;
	dlg.DoModal();
	// TODO:  在此添加控件通知处理程序代码
}
