#pragma once
#import "c:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")

#include<stdio.h>
#include<windows.h>

class CDBOperation
{
public:
	CDBOperation(void);
	~CDBOperation(void);
	bool ConnToDB(char *ConnectionString, char *UserID, char *Password);
	void ExitConnect();
	_RecordsetPtr ExecuteWithResSQL(_bstr_t sql);
	//bool ExecuteNoResSQL(const char *); // delete and add

private:
	void PrintErrorInfo(_com_error &);

private:
	_ConnectionPtr CreateConnPtr();
	_CommandPtr CreateCommPtr();
	_RecordsetPtr CreateRecsetPtr();

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	_CommandPtr m_pCommand;
};


