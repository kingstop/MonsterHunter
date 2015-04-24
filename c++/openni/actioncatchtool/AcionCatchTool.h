#pragma once


// AcionCatchTool dialog

class AcionCatchTool : public CDialogEx
{
	DECLARE_DYNAMIC(AcionCatchTool)

public:
	AcionCatchTool(CWnd* pParent = NULL);   // standard constructor
	virtual ~AcionCatchTool();

// Dialog Data
	enum { IDD = IDD_ACTIONCATCHTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};
