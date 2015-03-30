// DlgViewEdit.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgViewEdit.h"
#include "afxdialogex.h"


// DlgViewEdit dialog

IMPLEMENT_DYNAMIC(DlgViewEdit, CDialogEx)

DlgViewEdit::DlgViewEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgViewEdit::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

DlgViewEdit::~DlgViewEdit()
{
}

void DlgViewEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgViewEdit, CDialogEx)
END_MESSAGE_MAP()


// DlgViewEdit message handlers
