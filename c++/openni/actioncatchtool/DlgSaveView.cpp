// DlgSaveView.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgSaveView.h"
#include "afxdialogex.h"


// DlgSaveView dialog

IMPLEMENT_DYNAMIC(DlgSaveView, CDialogEx)

DlgSaveView::DlgSaveView(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSaveView::IDD, pParent)
{

}

DlgSaveView::~DlgSaveView()
{
}

void DlgSaveView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgSaveView, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgSaveView::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSaveView message handlers


void DlgSaveView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
