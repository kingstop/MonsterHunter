// DlgViewEdit.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "DlgViewEdit.h"
#include "afxdialogex.h"
#include "frameStorage.h"


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


BOOL DlgViewEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	resetCombox();
	return TRUE;
}

void DlgViewEdit::resetCombox()
{
	for (int i = XN_SKEL_HEAD; i < XN_SKEL_MAX; i ++)
	{
		for (int j = 0; j < 3; j ++)
		{
			_combo_[j].AddString(pos_name_config[i].c_str());
		}
	}
	for (int i = 0; i < 3; i ++)
	{
		setCombox(i, (XnSkeletonJoint)(i + 1));
	}
}

XnSkeletonJoint DlgViewEdit::getCombox(int i)
{
	int nNumber = _combo_[i].GetCurSel();
	XnSkeletonJoint enType = (XnSkeletonJoint)(nNumber + 1);
	return enType;

}

void DlgViewEdit::setCombox(int i, XnSkeletonJoint en)
{
	int nNumber = 0;
	nNumber = (int)en - 1;
	_combo_[i].SetCurSel(nNumber);
}

void DlgViewEdit::updateCombox()
{
	XnSkeletonJoint enType[3];
	XnVector3D point_3d[3];
	for (int i = 0; i < 3; i ++)
	{
		enType[i] = getCombox(i);
	}
	
	frame_check* frame_temp = g_frameStorage.get_frame_check(g_frameStorage._cur_sel.c_str());
	std::string str_angle = "无可编辑对象";
	if (frame_temp)
	{
		for (int i = 0; i < 3; i ++)
		{
			point_3d[i] =  frame_temp->frame_real_point[i];
		}
		int angle = getangleforposition(point_3d[0], point_3d[1], point_3d[2]);
		char sz_temp[128];
		sprintf(sz_temp, " %d ", angle);
		str_angle = sz_temp;
	}
	SetDlgItemText(IDC_EDIT_DEGREE,str_angle.c_str()); 

	std::string save_name;
	CHECKDEGREES::iterator it = _degrees.begin();
	for (; it != _degrees.end(); ++ it)
	{
		check_degree entry_temp = it->second;
		if (entry_temp.pos[1] == enType[1])
		{
			if ((entry_temp.pos[0] == enType[0] && entry_temp.pos[2] == enType[2]) ||(entry_temp.pos[0] == enType[2] && entry_temp.pos[2] == enType[0]))
			{
				save_name = it->first;
				break;
			}
		}
	}
	bool have_check = false;

	if (save_name.empty() != false)
	{
		int count_temp = _frame_checks.GetCount();
		for (int i = 0; i < count_temp; i ++)
		{
			CString str_temp;
			CString current_temp;
			current_temp = save_name.c_str();

			_frame_checks.GetText(i, str_temp);
			if (current_temp == str_temp)
			{
				_frame_checks.SetCurSel(i);
				have_check = true;
				break;
			}
		}
	}
	else
	{
		_frame_checks.SetSel(_frame_checks.GetCurSel(), FALSE);
	}

}

void DlgViewEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FRAME_EDIT, _edit_frames);
	DDX_Control(pDX, IDC_LIST_FRAME_CHECKS, _frame_checks);
	DDX_Control(pDX, IDC_COMBO_1, _combo_[0]);
	DDX_Control(pDX, IDC_COMBO_2, _combo_[1]);
	DDX_Control(pDX, IDC_COMBO_3, _combo_[2]);
	
}


BEGIN_MESSAGE_MAP(DlgViewEdit, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_FRAME_EDIT, &DlgViewEdit::OnLbnSelchangeListFrameEdit)
	ON_LBN_SELCHANGE(IDC_LIST_FRAME_CHECKS, &DlgViewEdit::OnLbnSelchangeListFrameChecks)
	ON_BN_CLICKED(IDC_BTN_SAVE_CHECK, &DlgViewEdit::OnBnClickedBtnSaveCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_1, &DlgViewEdit::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_2, &DlgViewEdit::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO_3, &DlgViewEdit::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// DlgViewEdit message handlers


void DlgViewEdit::OnLbnSelchangeListFrameEdit()
{
	int cur_sel = _edit_frames.GetCurSel();
	CString temp_str;
	_edit_frames.GetText(cur_sel,temp_str);
	g_frameStorage._cur_sel = temp_str;
	frame_check* temp = g_frameStorage.get_frame_check(g_frameStorage._cur_sel.c_str());
	
	if (temp)
	{
		_degrees = temp->check_degrees;
		CHECKDEGREES::iterator it = _degrees.begin();
		for (; it != _degrees.end(); ++ it)
		{
			check_degree temp_entry = it->second;
			std::string temp_str = it->first;
			_frame_checks.AddString(temp_str.c_str());
		}		
	}


	

	// TODO: Add your control notification handler code here
}


void DlgViewEdit::OnLbnSelchangeListFrameChecks()
{	
	int cur_sel = _frame_checks.GetCurSel();
	CString temp_str;
	_frame_checks.GetText(cur_sel,temp_str);
	std::string temp = temp_str;

	CHECKDEGREES::iterator it = _degrees.find(temp);
	if (it != _degrees.end())
	{
		check_degree temp = it->second;
		for (int i = 0; i < 3; i ++)
		{
			setCombox(i, it->second.pos[i]);
		}
		
		char sztemp[128];
		sprintf(sztemp, "%d", temp.degree);
		SetDlgItemText(IDC_EDIT_DEGREE,sztemp); 
		sprintf(sztemp, "%d", temp.Recognize);
		SetDlgItemText(IDC_EDIT_RECOGNIZE,sztemp); 
	}
	// TODO: Add your control notification handler code here
}



void DlgViewEdit::OnBnClickedBtnSaveCheck()
{
	XnSkeletonJoint pos_temp[3];
	for (int i = 0; i < 3; i ++)
	{
		pos_temp[i] = (XnSkeletonJoint)_combo_[0].GetCurSel();
	}

	if (pos_temp[0] == pos_temp[1] || pos_temp[1] == pos_temp[2] || pos_temp[2] == pos_temp[0])
	{
		// messagebox 不能重复
	}
	
	std::string save_name;
	CHECKDEGREES::iterator it = _degrees.begin();
	for (; it != _degrees.end(); ++ it)
	{
		check_degree entry_temp = it->second;
		if (entry_temp.pos[1] == pos_temp[1])
		{
			if ((entry_temp.pos[0] == pos_temp[0] && entry_temp.pos[2] == pos_temp[2]) ||(entry_temp.pos[0] == pos_temp[2] && entry_temp.pos[2] == pos_temp[0]))
			{
				save_name = it->first;
				break;
			}
		}
	}

	std::string edit_name;
	CString sztemp;
	GetDlgItemText(IDC_EDIT_RECOGNIZE,sztemp); 
	int Number = atoi(sztemp);

	
	GetDlgItemText(IDC_EDIT_DEGREE, sztemp);
	int Number_temp = atoi(sztemp);

	if (save_name.empty())
	{
		edit_name = mk_degree_title(pos_temp[0], pos_temp[1], pos_temp[2]);
		check_degree entry_temp;
		for (int i = 0; i < 3; i ++)
		{
			entry_temp.pos[i] = pos_temp[i];
		}
		entry_temp.Recognize = Number;
		entry_temp.degree = Number_temp;

		_degrees.insert(CHECKDEGREES::value_type(edit_name,entry_temp ));
	}
	else
	{
		it = _degrees.find(save_name);
		if (it != _degrees.end())
		{
			it->second.Recognize = Number;			
		}
		edit_name = save_name;
	}

	// TODO: Add your control notification handler code here
}


void DlgViewEdit::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void DlgViewEdit::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
}


void DlgViewEdit::OnCbnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
}
