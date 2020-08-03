// Academy_Teacher_Add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "Academy_Teacher_Add.h"
#include "afxdialogex.h"
#include "ADOConn.h"


// CAcademy_Teacher_Add �Ի���

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


// CAcademy_Teacher_Add ��Ϣ�������


void CAcademy_Teacher_Add::OnBnClickedAcademyTeacherAddadd()
{
	UpdateData();
	if (m_Academy_Teacher_Add_password.IsEmpty())
	{
		MessageBox(_T("�������û�����"));
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
		strMsg.Format(_T("��ʦ��ţ�%s"), str, str);

		MessageBox(strMsg);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
