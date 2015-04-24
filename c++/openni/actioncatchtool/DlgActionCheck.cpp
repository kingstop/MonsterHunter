// DlgActionCheck.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgActionCheck.h"
#include "afxdialogex.h"
#include "DlgSaveAction.h"


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
	ON_BN_CLICKED(IDC_BTN_SAVE, &DlgActionCheck::OnBnClickedBtnSave)
	ON_LBN_SELCHANGE(IDC_LIST_FRAME_CHECKS, &DlgActionCheck::OnLbnSelchangeListFrameChecks)
END_MESSAGE_MAP()


// DlgActionCheck message handlers


void DlgActionCheck::OnBnClickedBtnNewAction()
{
	DlgSaveAction dlg(this);
	int iRet = dlg.DoModal();
	// TODO: Add your control notification handler code here
}

void DlgActionCheck::OnLoadActionFrames(FRAMECHECKS& entry)
{
	_list_action_frames.ResetContent();
	FRAMECHECKS::iterator it = entry.begin();
	for (; it != entry.end(); ++ it)
	{
		frameCheck entry_temp = (*it);
		_list_action_frames.AddString(entry_temp.check_name.c_str());
	}

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
			OnLoadActionFrames(entry_check->check_frames);
		}
	}

	// TODO: Add your control notification handler code here
}



void DlgActionCheck::OnLbnSelchangeListActionFrames()
{
	int cur_sel = _list_action_frames.GetCurSel();
	CString temp_str;
	_list_action_frames.GetText(cur_sel,temp_str);

	CString temp_action_name;
	_lits_actions.GetText(_lits_actions.GetCurSel(), temp_action_name);
	actionCheck* action_check_entry = g_actionCheckStorage.get_action(temp_action_name);
	if (action_check_entry)
	{
		if (action_check_entry->action_name.c_str() == temp_action_name 
			&& action_check_entry->check_frames[cur_sel].check_name.c_str() == temp_str)
		{
			SetDlgItemInt(IDC_EDIT_INTERVAL_TIME,action_check_entry->check_frames[cur_sel].interval_time);
			SetDlgItemInt(IDC_EDIT_TIME_OF_DURATION, action_check_entry->check_frames[cur_sel].duration_time);
		}
		else
		{
			AfxMessageBox("选择和实际不一致");
		}
		
	}
	

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnUp()
{
	int cur_sel = _list_action_frames.GetCurSel();
	if (cur_sel > 0)
	{
		CString temp_str;
		_list_action_frames.GetText(cur_sel,temp_str);

		CString temp_action_name;
		_lits_actions.GetText(_lits_actions.GetCurSel(), temp_action_name);
		actionCheck* action_check_entry = g_actionCheckStorage.get_action(temp_action_name);
		if (action_check_entry)
		{
			if (action_check_entry->action_name.c_str() == temp_action_name 
				&& action_check_entry->check_frames[cur_sel].check_name.c_str() == temp_str)
			{
				int temp_swap = cur_sel - 1;
				frameCheck entry_swap = action_check_entry->check_frames[temp_swap];
				action_check_entry->check_frames[temp_swap] = action_check_entry->check_frames[cur_sel];
				action_check_entry->check_frames[cur_sel] =  entry_swap;
				OnLoadActionFrames(action_check_entry->check_frames);
				_list_action_frames.SetCurSel(temp_swap);

			}
			else
			{
				AfxMessageBox("选择和实际不一致");
			}
		}
	}
	else
	{
		AfxMessageBox("不能为第一节点");
	}

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnDown()
{
	int cur_sel = _list_action_frames.GetCurSel();
	int temp_count = _list_action_frames.GetCount();
	if (cur_sel < temp_count -1)
	{
		CString temp_str;
		_list_action_frames.GetText(cur_sel,temp_str);

		CString temp_action_name;
		_lits_actions.GetText(_lits_actions.GetCurSel(), temp_action_name);
		actionCheck* action_check_entry = g_actionCheckStorage.get_action(temp_action_name);
		if (action_check_entry)
		{
			if (action_check_entry->action_name.c_str() == temp_action_name 
				&& action_check_entry->check_frames[cur_sel].check_name.c_str() == temp_str)
			{
				int temp_swap = cur_sel + 1;
				frameCheck entry_swap = action_check_entry->check_frames[temp_swap];
				action_check_entry->check_frames[temp_swap] = action_check_entry->check_frames[cur_sel];
				action_check_entry->check_frames[cur_sel] =  entry_swap;
				OnLoadActionFrames(action_check_entry->check_frames);
				_list_action_frames.SetCurSel(temp_swap);

			}
			else
			{
				AfxMessageBox("选择和实际不一致");
			}
		}
	}
	else
	{
		AfxMessageBox("不能为最后节点");
	}

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnUse()
{
	CString str_entry;
	_list_frame_source.GetText(_list_frame_source.GetCurSel(), str_entry);
	std::string str_temp = str_entry;
	frame_check* entry_temp = g_frameStorage.get_frame_check(str_temp.c_str());
	if (entry_temp == NULL)
	{
		AfxMessageBox("没有正确的帧");
	}
	else
	{
		_lits_actions.GetText(_lits_actions.GetCurSel(), str_entry);
		actionCheck* entry_action = g_actionCheckStorage.get_action(str_entry);
		if (entry_action == NULL)
		{
			AfxMessageBox("没有正确的动作");
		}
		else
		{
			frameCheck temp_check;
			CHECKDEGREES::iterator it = entry_temp->check_degrees.begin();
			for (; it != entry_temp->check_degrees.end(); ++ it)
			{
				temp_check.check_degrees.push_back(it->second);
			}
			temp_check.check_name = entry_temp->frame_name;
			temp_check.duration_time = 100;
			temp_check.interval_time = 100;
			entry_action->check_frames.push_back(temp_check);
			_list_action_frames.AddString(temp_check.check_name.c_str());
		}
	}

	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnBnClickedBtnSave()
{
	g_actionCheckStorage.save();
	// TODO: Add your control notification handler code here
}


void DlgActionCheck::OnLbnSelchangeListFrameChecks()
{
	// TODO: Add your control notification handler code here
}
