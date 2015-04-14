#pragma once
#include "afxwin.h"


// DlgViewCatch dialog

class DlgViewCatch : public CDialogEx
{
	DECLARE_DYNAMIC(DlgViewCatch)

public:
	DlgViewCatch(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgViewCatch();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAB_Catch };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListBox _view_catch;
	afx_msg void OnBnClickedBtnCatch();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnUse();
	afx_msg void OnLbnSelchangeListViewCatch();
	void update_state_check();
	afx_msg void OnBnClickedRadioCatch();
	afx_msg void OnBnClickedRadioEdit();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnCatchSave();
};
