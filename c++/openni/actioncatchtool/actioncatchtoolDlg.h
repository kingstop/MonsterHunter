
// actioncatchtoolDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CactioncatchtoolDlg dialog
class CactioncatchtoolDlg : public CDialogEx
{
// Construction
public:
	CactioncatchtoolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ACTIONCATCHTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene();

	DECLARE_MESSAGE_MAP()
public:


	CWnd* _wnd_main_render; 
	HDC hrenderDC;                                                            // DC
	HGLRC hrenderRC;                                                        // RC
	int PixelFormat;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtncatch();
};
