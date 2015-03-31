// DlgViewCatch.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgViewCatch.h"
#include "afxdialogex.h"


// DlgViewCatch dialog

IMPLEMENT_DYNAMIC(DlgViewCatch, CDialogEx)

DlgViewCatch::DlgViewCatch(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgViewCatch::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

DlgViewCatch::~DlgViewCatch()
{
}

void DlgViewCatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_CATCH, _view_catch);
}


BEGIN_MESSAGE_MAP(DlgViewCatch, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CATCH, &DlgViewCatch::OnBnClickedBtnCatch)
	ON_BN_CLICKED(IDC_BTN_USE, &DlgViewCatch::OnBnClickedBtnUse)
	ON_LBN_SELCHANGE(IDC_LIST_VIEW_CATCH, &DlgViewCatch::OnLbnSelchangeListViewCatch)
	ON_BN_CLICKED(IDC_RADIO_CATCH, &DlgViewCatch::OnBnClickedRadioCatch)
	ON_BN_CLICKED(IDC_RADIO_EDIT, &DlgViewCatch::OnBnClickedRadioEdit)
	ON_BN_CLICKED(IDC_BTN_DELETE, &DlgViewCatch::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// DlgViewCatch message handlers

BOOL DlgViewCatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	((CButton* )GetDlgItem(IDC_RADIO_CATCH))->SetCheck(1);
	update_state_check();
	return TRUE;

}
void DlgViewCatch::OnBnClickedBtnCatch()
{
	XnUserID aUsers[15];
	XnUInt16 nUsers = 15;
	g_UserGenerator.GetUsers(aUsers, nUsers);
	if (nUsers != 1)
	{
		return;
	}
	if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[0]))
	{

		XnVector3D XnVector3Ds[XN_SKEL_MAX];
		for (int i = XN_SKEL_BEGIN; i < XN_SKEL_MAX; i ++)
		{
			XnSkeletonJointPosition joint1;	
			g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(1, (XnSkeletonJoint)i, joint1);
			XnVector3Ds[i].X = joint1.position.X;
			XnVector3Ds[i].Y = joint1.position.Y;
			XnVector3Ds[i].Z = joint1.position.Z;

		}
		g_frameCatch.add_frame_data(XnVector3Ds);
	}
	


	// TODO: Add your control notification handler code here
}

BOOL DlgViewCatch::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN  &&  pMsg->wParam==VK_ESCAPE)    
	{    
		return TRUE;
		//也会去调用OnOK函数，而OnOK什么也不做，这样ESC也被屏蔽  
	}    

	return   CDialogEx::PreTranslateMessage(pMsg);  
}

void DlgViewCatch::OnBnClickedBtnUse()
{
	// TODO: Add your control notification handler code here
}


void DlgViewCatch::OnLbnSelchangeListViewCatch()
{
	CString temp_str;
	_view_catch.GetText(_view_catch.GetCurSel(),temp_str);
	g_frameCatch._cur_sel_catch_frame = temp_str;
	// TODO: Add your control notification handler code here
}


void DlgViewCatch::update_state_check()
{
	int check = ((CButton* )GetDlgItem(IDC_RADIO_CATCH))->GetCheck();
	if (check)
	{
		g_catch_view_type = catch_view_catch;
	}
	else
	{
		g_catch_view_type = catch_view_select;

	}

}

void DlgViewCatch::OnBnClickedRadioCatch()
{
	update_state_check();
	// TODO: Add your control notification handler code here
}


void DlgViewCatch::OnBnClickedRadioEdit()
{
	update_state_check();
	// TODO: Add your control notification handler code here
}


void DlgViewCatch::OnBnClickedBtnDelete()
{
	g_frameCatch.del_frame_data(g_frameCatch._cur_sel_catch_frame.c_str());
	//g_frameCatch
	// TODO: Add your control notification handler code here
}
