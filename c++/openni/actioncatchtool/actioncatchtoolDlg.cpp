
// actioncatchtoolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "actioncatchtoolDlg.h"
#include "afxdialogex.h"
#include "GL/glut.h"
//#include "GL/glaux.h"    
#include<windows.h>
#include<strsafe.h>//win2003SDK必须安装　要不无此头文件。此文件是为了实现StringCchPrintf，StringCchLength。
#define MAX_THREADS 3
#define BUF_SIZE 255

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	HANDLE hStdout;
	PMYDATA pData;
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;
	hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdout==INVALID_HANDLE_VALUE)
		return 1;
	//Casttheparametertothecorrectdatatype.
	pData=(PMYDATA)lpParam;
	//Printtheparametervaluesusingthread-safefunctions.
	//StringCchPrintf(msgBuf,BUF_SIZE,TEXT("Parameters=%d,%d\n"),
	//	pData->val1,pData->val2);
	//StringCchLength(msgBuf,BUF_SIZE,&cchStringSize);
	//WriteConsole(hStdout,msgBuf,cchStringSize,&dwChars,NULL);
	//Freethememoryallocatedbythecallerforthethread
	//datastructure.
	HeapFree(GetProcessHeap(),0,pData);
	return 0;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CactioncatchtoolDlg* g_dlg = NULL;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CactioncatchtoolDlg dialog




CactioncatchtoolDlg::CactioncatchtoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CactioncatchtoolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_wnd_main_render = NULL;

}

void CactioncatchtoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_ANIMATION_MAIN, _animate_main);
	DDX_Control(pDX, IDC_LIST_CATCH_FRAMES, _catch_frames_list);
}
/*

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

*/

void CactioncatchtoolDlg::createEditView()
{
	pData_sel=(PMYDATA)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,
		sizeof(MYDATA));
	if(pData_sel==NULL)
		ExitProcess(2);
	//Generateuniquedataforeachthread.
	pData_sel->val1=i;
	pData_sel->val2=i+100;
	hThread[i]=CreateThread(
		NULL,//defaultsecurityattributes
		0,//usedefaultstacksize
		ThreadProc,//threadfunction
		pData,//argumenttothreadfunction
		0,//usedefaultcreationflags
		&dwThreadId[i]);//returnsthethreadidentifier
}

void CactioncatchtoolDlg::createSelView()
{
	pData=(PMYDATA)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,
		sizeof(MYDATA));
	if(pData==NULL)
		ExitProcess(2);
	//Generateuniquedataforeachthread.
	pData->val1=i;
	pData->val2=i+100;
	hThread[i]=CreateThread(
		NULL,//defaultsecurityattributes
		0,//usedefaultstacksize
		ThreadProc,//threadfunction
		pData,//argumenttothreadfunction
		0,//usedefaultcreationflags
		&dwThreadId[i]);//returnsthethreadidentifier
}

BEGIN_MESSAGE_MAP(CactioncatchtoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNCATCH_FRAME, &CactioncatchtoolDlg::OnBnClickedBtncatchFrame)
	ON_BN_CLICKED(IDC_BTNDELETE_FRAME, &CactioncatchtoolDlg::OnBnClickedBtndeleteFrame)
	ON_LBN_SELCHANGE(IDC_LIST_CATCH_FRAMES, &CactioncatchtoolDlg::OnLbnSelchangeListCatchFrames)
END_MESSAGE_MAP()

BOOL CactioncatchtoolDlg::CreateViewGLContext(HDC hDC, HGLRC hGLRC) {
	hGLRC = wglCreateContext(hDC);
	if(hGLRC == NULL) {
		return FALSE;
	}
	if(wglMakeCurrent(hDC, hGLRC) == FALSE) {
		return FALSE;
	}
	return TRUE;
}

BOOL CactioncatchtoolDlg::SetWindowPixelFormat(HDC hDC) { // CCOpenGLDlg改为你自己创建的MFC类名
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 0;
	pixelDesc.cRedShift = 0;
	pixelDesc.cGreenBits = 0;
	pixelDesc.cGreenShift = 0;
	pixelDesc.cBlueBits = 0;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 0;
	pixelDesc.cAccumRedBits = 0;
	pixelDesc.cAccumGreenBits = 0;
	pixelDesc.cAccumBlueBits = 0;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 0;
	pixelDesc.cStencilBits = 1;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	PixelFormat = ChoosePixelFormat(hDC, &pixelDesc);
	if(PixelFormat == 0) {
		PixelFormat = 1;
		if(DescribePixelFormat(hDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0) {
			return FALSE;
		}
	}
	if(SetPixelFormat(hDC, PixelFormat, &pixelDesc) == FALSE) {
		return FALSE;
	}
	return TRUE;
}

// CactioncatchtoolDlg message handlers

BOOL CactioncatchtoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	_wnd_main_render = GetDlgItem(IDC_RENDER_MAIN);

	PMYDATA pData;
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];
	int i;
	//CreateMAX_THREADSworkerthreads.
	for(i=0;i<MAX_THREADS;i++)
	{
		//Allocatememoryforthreaddata.
		pData=(PMYDATA)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,
			sizeof(MYDATA));
		if(pData==NULL)
			ExitProcess(2);
		//Generateuniquedataforeachthread.
		pData->val1=i;
		pData->val2=i+100;
		hThread[i]=CreateThread(
			NULL,//defaultsecurityattributes
			0,//usedefaultstacksize
			ThreadProc,//threadfunction
			pData,//argumenttothreadfunction
			0,//usedefaultcreationflags
			&dwThreadId[i]);//returnsthethreadidentifier
		//Checkthereturnvalueforsuccess.
		if(hThread[i]==NULL)
		{
			ExitProcess(i);
		}
	}
	//Waituntilallthreadshaveterminated.
	WaitForMultipleObjects(MAX_THREADS,hThread,TRUE,INFINITE);
	//Closeallthreadhandlesuponcompletion.
	for(i=0;i<MAX_THREADS;i++)
	{
		CloseHandle(hThread[i]);
	}


	hrenderDC = ::GetDC(_wnd_main_render->m_hWnd);
	if(SetWindowPixelFormat(hrenderDC) == FALSE) {                // 设置hDC的像素格式
		return 0;
	}
	if(CreateViewGLContext(hrenderDC, hrenderRC) == FALSE) {                    // 由hDC转换得到hRC
		return 0;
	}


	//HWND hWnd = GetDlgItem(IDC_RENDER_SEL_CATCH)->m_hWnd;
	//sel_hrenderDC = ::GetDC(hWnd);
	//if(SetWindowPixelFormat(sel_hrenderDC) == FALSE) {                // 设置hDC的像素格式
	//	return 0;
	//}
	//if (CreateViewGLContext(sel_hrenderDC, sel_hrenderRC) == FALSE)
	//{
	//	return 0;
	//}

	//edit_hrenderDC = ::GetDC(GetDlgItem(IDC_RENDER_EDIT)->m_hWnd);
	//if(SetWindowPixelFormat(edit_hrenderDC) == FALSE) {                // 设置hDC的像素格式
	//	return 0;
	//}

	//if (CreateViewGLContext(edit_hrenderDC, edit_hrenderRC) == FALSE)
	//{
	//	return 0;
	//}

	// openGL的初始化设置
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// 设置计时器,10ms刷新一次
	SetTimer(1, 10, 0);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CactioncatchtoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CactioncatchtoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CactioncatchtoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CactioncatchtoolDlg::createThreadSel()
{

}
void CactioncatchtoolDlg::createThreadEdit()
{

}

void CactioncatchtoolDlg::RenderScene() {

	//wglMakeCurrent(hrenderDC, hrenderRC);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();
	SwapBuffers(hrenderDC);    // 使用glFlush()没有显示？
}

//
//void CactioncatchtoolDlg::RenderSelFrameScene()
//{
//	wglMakeCurrent(sel_hrenderDC, sel_hrenderRC);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0, 1.0, 1.0);
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -5.0);
//	glBegin(GL_TRIANGLES);
//	glVertex3f(0.0, 1.0, 0.0);
//	glVertex3f(-1.0, -1.0, 0.0);
//	glVertex3f(1.0, -1.0, 0.0);
//	glEnd();
//	SwapBuffers(sel_hrenderDC); 
//}
//void CactioncatchtoolDlg::RenderEditFrameScene()
//{
//	wglMakeCurrent(edit_hrenderDC, edit_hrenderRC);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0, 1.0, 1.0);
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -5.0);
//	glBegin(GL_TRIANGLES);
//	glVertex3f(0.0, 1.0, 0.0);
//	glVertex3f(-1.0, -1.0, 0.0);
//	glVertex3f(1.0, -1.0, 0.0);
//	glEnd();
//	SwapBuffers(edit_hrenderDC); 
//}


void CactioncatchtoolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	RenderScene();

	CDialogEx::OnTimer(nIDEvent);
}



void CactioncatchtoolDlg::OnBnClickedBtncatchFrame()
{
	// TODO: Add your control notification handler code here
}


void CactioncatchtoolDlg::OnBnClickedBtndeleteFrame()
{
	// TODO: Add your control notification handler code here
}


void CactioncatchtoolDlg::OnLbnSelchangeListCatchFrames()
{


	CString select_string;
	_catch_frames_list.GetText(_catch_frames_list.GetCurSel(), select_string);
	
	// TODO: Add your control notification handler code here
}
