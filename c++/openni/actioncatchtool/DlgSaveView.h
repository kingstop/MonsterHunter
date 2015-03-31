#pragma once


// DlgSaveView dialog

class DlgSaveView : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveView)

public:
	DlgSaveView(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgSaveView();

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
