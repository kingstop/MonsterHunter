
// actioncatchtoolDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
class CactioncatchtoolDlg;
typedef struct _MyData{
	int val1;
	int val2;
}MYDATA,*PMYDATA;
extern CactioncatchtoolDlg* g_dlg;

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

	void createSelView();
	void createEditView();


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC, HGLRC hGLRC);
	void RenderScene();


	void createThreadSel();
	void createThreadEdit();
	//void RenderSelFrameScene();
	//void RenderEditFrameScene();


	DECLARE_MESSAGE_MAP()
public:


	CWnd* _wnd_main_render; 
	HDC hrenderDC;                                                            // DC
	HGLRC hrenderRC;                                                        // RC
	int PixelFormat;

	HDC sel_hrenderDC;                                                            // DC
	HGLRC sel_hrenderRC;                                                        // RC
	int sel_PixelFormat;
	PMYDATA pData_sel;
	DWORD dwThreadId_sel;
	HANDLE hThread_sel;


	HDC edit_hrenderDC;                                                            // DC
	HGLRC edit_hrenderRC;                                                        // RC
	int edit_PixelFormat;
	DWORD dwThreadId_edit;
	HANDLE hThread_edit;


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtncatch();
	afx_msg void OnBnClickedBtncatchFrame();
	afx_msg void OnBnClickedBtndeleteFrame();
	afx_msg void OnLbnSelchangeListCatchFrames();
protected:
	CListBox _catch_frames_list;
};
;