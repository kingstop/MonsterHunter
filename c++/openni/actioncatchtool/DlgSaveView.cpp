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


BOOL DlgSaveView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rtClient;
	GetWindowRect(rtClient);  	
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW); 
	return TRUE;
}

BEGIN_MESSAGE_MAP(DlgSaveView, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgSaveView::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSaveView message handlers


void DlgSaveView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString temp_str;
	GetDlgItemTextA(IDC_EDIT_SAVE_VIEW, temp_str);
	g_frameStorage.add_cur_sel(temp_str);


	CDialogEx::OnOK();
}
