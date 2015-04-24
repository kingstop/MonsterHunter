#pragma once
#include "afxwin.h"


// DlgActionCheck dialog

class DlgActionCheck : public CDialogEx
{
	DECLARE_DYNAMIC(DlgActionCheck)

public:
	DlgActionCheck(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgActionCheck();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAB_EDIT_ACTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnLoadActionFrames(FRAMECHECKS& entry);

	DECLARE_MESSAGE_MAP()
public:
	CListBox _lits_actions;
	CListBox _list_action_frames;
	CListBox _list_frame_source;
	afx_msg void OnBnClickedBtnNewAction();
	afx_msg void OnLbnSelchangeListActions();
	afx_msg void OnLbnSelchangeListActionFrames();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnUse();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnLbnSelchangeListFrameChecks();
};
