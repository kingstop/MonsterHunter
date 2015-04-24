#pragma once


// DlgSaveAction dialog

class DlgSaveAction : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveAction)

public:
	DlgSaveAction(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgSaveAction();

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_ACTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL PreTranslateMessage(MSG* pMsg);
};
