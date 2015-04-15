// DlgActionCheck.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgActionCheck.h"
#include "afxdialogex.h"


// DlgActionCheck dialog

IMPLEMENT_DYNAMIC(DlgActionCheck, CDialogEx)

DlgActionCheck::DlgActionCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgActionCheck::IDD, pParent)
{

}

DlgActionCheck::~DlgActionCheck()
{
}

void DlgActionCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACTIONS, _lits_actions);
	DDX_Control(pDX, IDC_LIST_ACTION_FRAMES, _list_action_frames);
	DDX_Control(pDX, IDC_LIST_FRAME_CHECKS, _list_frame_source);
}


BEGIN_MESSAGE_MAP(DlgActionCheck, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEW_ACTION, &DlgActionCheck::OnBnClickedBtnNewAction)
	ON_LBN_SELCHANGE(IDC_LIST_ACTIONS, &DlgActionCheck::OnLbnSelchangeListActions)
	ON_LBN_SELCHANGE(IDC_LIST_ACTION_FRAMES, &DlgActionCheck::OnLbnSelchangeListActionFrames)
	ON_BN_CLICKED(IDC_BTN_UP, &DlgActionCheck::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &DlgActionCheck::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_USE, &DlgActionCheck::OnBnClickedBtnUse)
END_MESSAGE_MAP()


// DlgActionCheck message handlers


void DlgActionCheck::OnBnClickedBtnNewAction()
{

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnLbnSelchangeListActions()
{
	int cur_sel = _lits_actions.GetCurSel();
	CString temp_str;
	_lits_actions.GetText(cur_sel,temp_str);
	if (temp_str != g_actionCheckStorage.cur_select.c_str())
	{
		g_actionCheckStorage.cur_select = temp_str;
		actionCheck* entry_check = g_actionCheckStorage.get_action(g_actionCheckStorage.cur_select.c_str());
		if (entry_check)
		{
			_lits_actions.ResetContent();
			FRAMECHECKS::iterator it = entry_check->check_frames.begin();
			for (; it != entry_check->check_frames.end(); ++ it)
			{
				frameCheck entry = (*it);
				_lits_actions.AddString(entry.check_name.c_str());
			}
			//entry_check->check_frames
		}
	}

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnLbnSelchangeListActionFrames()
{
	int cur_sel = _lits_actions.GetCurSel();
	CString temp_str;
	_lits_actions.GetText(cur_sel,temp_str);
	

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnUp()
{
	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnDown()
{
	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnUse()
{
	// TODO: Add your control notification handler code here
}
