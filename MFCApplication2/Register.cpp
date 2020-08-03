// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Register.h"
#include "afxdialogex.h"
#include "Teacher.h"
#include "Academy.h"
#include "ADOConn.h"


// CRegister �Ի���

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


// CRegister ��Ϣ�������


void CRegister::OnBnClickedRegisterInterfaceRegister()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData(true);    //�ؼ�����
	CString str;
	str.Format(_T("insert into teacher(tno,tpassword,tstate) values('%d','%d','n')",m_tno,m_tpassword));
	m_adodc_teacher.put_CommandType(8);
	m_adodc_teacher.put_RecordSource(str);
	//m_adodc_teacher.Refresh();
	m_adodc_teacher.UpdateData();
	m_datagrid_teacher.putref_DataSource(m_adodc_teacher.GetControlUnknown());
	CRegister::OnOK();*/

	if (m_register_type == 0)  //ע���ʦ�˻�,ע���ת����Ӧ����
	{
		UpdateData();
		CString c_tno, c_tpassword;
		c_tno = m_tno;
		c_tpassword = m_tpassword;
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
		if (con == false)
		{
			MessageBox(_T("���ݿ����ӳ���"));
			return;
		}
		if (m_tno.IsEmpty() || m_tpassword.IsEmpty())
		{
			MessageBox(_T("�û��������벻��Ϊ��"), _T("�û���¼��Ϣ"));
			return;
		}
		CString strSql;
	    strSql.Format(_T("select * from my_user where id='%s'"), c_tno);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("�˺��Ѵ��ڣ����������룡"));
		}
		else
		{
			strSql.Format(_T("insert into my_user values('%s','%s','1','0')"), c_tno, c_tpassword);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			MessageBox(_T("ע��ɹ�!"));
			temp = c_tno;
			CRegister::OnOK();
			CTeacher dlg;
			dlg.DoModal();
		}
	}
	else if (m_register_type == 1)//ע��ѧԺ�˻�
	{
		UpdateData();
		CString c_tno, c_tpassword;
		c_tno = m_tno;
		c_tpassword = m_tpassword;
		CDBOperation CDBO;
		bool con = CDBO.ConnToDB("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;Data Source=121.42.189.254", "creategod", "creategod");
		if (con == false)
		{
			MessageBox(_T("���ݿ����ӳ���"));
			return;
		}
		if (m_tno.IsEmpty() || m_tpassword.IsEmpty())
		{
			MessageBox(_T("�û��������벻��Ϊ��"), _T("�û���¼��Ϣ"));
			return;
		}
		CString strSql;
		strSql.Format(_T("select * from my_user where id='%s'"), c_tno);
		CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
		if (!CDBO.m_pRecordset->adoEOF)
		{
			MessageBox(_T("�˺��Ѵ��ڣ����������룡"));
		}
		else
		{
			strSql.Format(_T("insert into my_user values('%s','%s','2','0')"), c_tno, c_tpassword);
			CDBO.m_pRecordset = CDBO.ExecuteWithResSQL((_bstr_t)strSql);
			MessageBox(_T("ע��ɹ�!"));
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str[2] = { _T("��ʦ�û�"),_T( "ѧԺ�û�" )};//ע��0Ϊ��ʦ��1ΪѧԺ
	int nIndex;
	for (int i = 0; i<2; i++)
	{
		nIndex = m_register_interface.AddString(str[i]);
		m_register_interface.SetItemData(nIndex, i);
	}
	m_register_interface.SetCurSel(0);
	m_register_type = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CRegister::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_register_interface.GetCurSel();
	if (nIndex != CB_ERR)
	{
		m_register_type = m_register_interface.GetItemData(nIndex);
	}
}
