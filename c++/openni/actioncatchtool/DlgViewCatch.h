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

	DECLARE_MESSAGE_MAP()
public:
	CListBox _view_catch;
	afx_msg void OnBnClickedBtnCatch();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
