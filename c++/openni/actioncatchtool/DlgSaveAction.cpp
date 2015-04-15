// DlgSaveAction.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgSaveAction.h"
#include "afxdialogex.h"


// DlgSaveAction dialog

IMPLEMENT_DYNAMIC(DlgSaveAction, CDialogEx)

DlgSaveAction::DlgSaveAction(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSaveAction::IDD, pParent)
{

}

DlgSaveAction::~DlgSaveAction()
{
}

void DlgSaveAction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgSaveAction, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgSaveAction::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSaveAction message handlers


void DlgSaveAction::OnBnClickedOk()
{
	CString cstr_temp;
	GetDlgItemText(IDC_EDIT_SAVE_ACTION,cstr_temp);
	bool b = g_actionCheckStorage.add_action(cstr_temp);
	if (b)
	{

	}
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
