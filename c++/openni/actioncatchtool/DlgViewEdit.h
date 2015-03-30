#pragma once


// DlgViewEdit dialog

class DlgViewEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgViewEdit)

public:
	DlgViewEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgViewEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAB_Edit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
