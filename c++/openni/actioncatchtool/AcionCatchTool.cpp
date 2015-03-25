// AcionCatchTool.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "AcionCatchTool.h"
#include "afxdialogex.h"


// AcionCatchTool dialog

IMPLEMENT_DYNAMIC(AcionCatchTool, CDialogEx)

AcionCatchTool::AcionCatchTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(AcionCatchTool::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

AcionCatchTool::~AcionCatchTool()
{
}

void AcionCatchTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AcionCatchTool, CDialogEx)
END_MESSAGE_MAP()


// AcionCatchTool message handlers
