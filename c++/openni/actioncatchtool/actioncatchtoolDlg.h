
// actioncatchtoolDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
class CactioncatchtoolDlg;
class DlgViewEdit;
class DlgViewCatch;
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
	BOOL CreateViewGLContext(HDC hDC, HGLRC& hGLRC);
	void RenderScene();
	void RenderPerson(XnVector3D frame_point[XN_SKEL_MAX]);
	void DrawLine(XnVector3D pos_1, XnVector3D pos_2);


	void createThreadSel();
	void createThreadEdit();
	void RenderSelFrameScene();
	void RenderEditFrameScene();

	void table_update();




	DECLARE_MESSAGE_MAP()
public:


	CWnd* _wnd_main_render; 
	HDC hrenderDC;                                                            // DC
	HGLRC hrenderRC;                                                        // RC
	int PixelFormat;



	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtncatch();
	afx_msg void OnBnClickedBtncatchFrame();
	afx_msg void OnBnClickedBtndeleteFrame();
	afx_msg void OnLbnSelchangeListCatchFrames();
public:

	CTabCtrl _tab_status;
	DlgViewEdit* _page_view_edit;
	DlgViewCatch* _page_view_catch;
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMove(int x, int y);
};
;