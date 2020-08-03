// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Register.h"
#include "afxdialogex.h"
#include "Teacher.h"
#include "Academy.h"
#include "ADOConn.h"


// CRegister 对话框

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegister::IDD, pParent)
	, m_tno(_T(""))
	, m_tpassword(_T(""))
	, m_register_type(0)
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_ADODC1, m_adodc_teahcer);
	DDX_Control(pDX, IDC_DATAGRID1, m_datagrid_teacher);
	//  DDX_Control(pDX, IDC_Register_Interface_EDIT_Number, m_tno);
	//  DDX_Control(pDX, IDC_Register_Interface_EDIT_Password, m_tpassword);
	//  DDX_Control(pDX, IDC_ADODC1, m_adodc1);
	DDX_Text(pDX, IDC_Register_Interface_EDIT_Number, m_tno);
	DDX_Text(pDX, IDC_Register_Interface_EDIT_Password, m_tpassword);
	DDX_Control(pDX, IDC_ADODC1, m_adodc_teacher);
	DDX_Control(pDX, IDC_COMBO1, m_register_interface);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDC_Register_Interface_Register, &CRegister::OnBnClickedRegisterInterfaceRegister)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRegister::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CRegister 消息处理程序


void CRegister::OnBnClickedRegisterInterfaceRegister()
{
	// TODO:  在此添加控件通知处理程序代码
	/*UpdateData(true);    //控件连接
	CString str;
	str.Format(_T("insert into teacher(tno,tpassword,tstate) values('%d','%d','n')",m_tno,m_tpassword));
	m_adodc_teacher.put_CommandType(8);
	m_adodc_teacher.put_RecordSource(str);
	//m_adodc_teacher.Refresh();
	m_adodc_teacher.UpdateData();
	m_datagrid_teacher.putref_DataSource(m_adodc_teacher.GetControlUnknown());
	CRegister::OnOK();*/

	if (m_register_type == 0)  //注册教师账户,注册后转到对应界面
	{
		UpdateData();
		CString c_tno, c_tpassword;
		c_tno = m_tno;
		c_tpassword = m_tpassword;
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
		if (con == false)
		{
			MessageBox(_T("数据库连接出错"));
			return;
		}
		if (m_tno.IsEmpty() || m_tpassword.IsEmpty())
		{
			MessageBox(_T("用户名或密码不能为空"), _T("用户登录信息"));
			return;
		}
		CString strSql;
	    strSql.Format(_T("select * from my_user where id='%s'"), c_tno);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("账号已存在，请重新输入！"));
		}
		else
		{
			strSql.Format(_T("insert into my_user values('%s','%s','1','0')"), c_tno, c_tpassword);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			MessageBox(_T("注册成功!"));
			temp = c_tno;
			CRegister::OnOK();
			CTeacher dlg;
			dlg.DoModal();
		}
	}
	else if (m_register_type == 1)//注册学院账户
	{
		UpdateData();
		CString c_tno, c_tpassword;
		c_tno = m_tno;
		c_tpassword = m_tpassword;
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
		if (con == false)
		{
			MessageBox(_T("数据库连接出错"));
			return;
		}
		if (m_tno.IsEmpty() || m_tpassword.IsEmpty())
		{
			MessageBox(_T("用户名或密码不能为空"), _T("用户登录信息"));
			return;
		}
		CString strSql;
		strSql.Format(_T("select * from my_user where id='%s'"), c_tno);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("账号已存在，请重新输入！"));
		}
		else
		{
			strSql.Format(_T("insert into my_user values('%s','%s','2','0')"), c_tno, c_tpassword);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			MessageBox(_T("注册成功!"));
			temp = c_tno;
			CRegister::OnOK();
			CAcademy dlg;
			dlg.DoModal();
		}
	}
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str[2] = { _T("教师用户"),_T( "学院用户" )};//注册0为教师，1为学院
	int nIndex;
	for (int i = 0; i<2; i++)
	{
		nIndex = m_register_interface.AddString(str[i]);
		m_register_interface.SetItemData(nIndex, i);
	}
	m_register_interface.SetCurSel(0);
	m_register_type = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CRegister::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	int nIndex = m_register_interface.GetCurSel();
	if (nIndex != CB_ERR)
	{
		m_register_type = m_register_interface.GetItemData(nIndex);
	}
}
