
// actioncatchtoolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "actioncatchtool.h"
#include "actioncatchtoolDlg.h"
#include "afxdialogex.h"
#include "GL/glut.h"
#include "DlgViewCatch.h"
#include "DlgViewEdit.h"
#include "DlgActionCheck.h"
//#include "GL/glaux.h"    
#include<windows.h>
#include<strsafe.h>//win2003SDK必须安装　要不无此头文件。此文件是为了实现StringCchPrintf，StringCchLength。
#define MAX_THREADS 3
#define BUF_SIZE 255


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

#define GL_WIN_SIZE_X 720
#define GL_WIN_SIZE_Y 480

XnBool g_bPause = false;
XnBool g_bRecord = false;

XnBool g_bQuit = false;

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

void Initial(void)
{
	GLfloat mat_ambient[] = {0.2f,0.2f,0.2f,1.0f};
	GLfloat mat_diffuse[] = {0.8f,0.8f,0.8f,1.0f};
	GLfloat mat_specular[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat mat_shininess[] = {50.0f};


	GLfloat light0_diffuse[] = {0.0f,0.0f,1.0f,1.0f};
	GLfloat light0_position[] = {1.0f,1.0f,1.0f,0.0f};
	GLfloat light1_ambient[] = {0.2f,0.2f,0.2f,1.0f};
	GLfloat light1_diffuse[] = {1.0f,0.0f,0.0f,1.0f};
	GLfloat light1_specular[] = {1.0f,0.6f,0.6f,1.0f};
	GLfloat light1_position[] = {-3.0f,-3.0f,3.0f,1.0f};

	GLfloat spot_direction[] = {1.0f,1.0f,-1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);

	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_POSITION,light0_position);


	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f,1.0f,1.0f,1.0f);

}

void CleanupExit()
{
	g_scriptNode.Release();
	g_DepthGenerator.Release();
	g_UserGenerator.Release();
	g_Player.Release();
	g_Context.Release();

	exit (1);
}

// Callback: New user was detected
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d New User %d\n", epochTime, nId);
	// New user found
	if (g_bNeedPose)
	{
		g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
	}
	else
	{
		g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
}
// Callback: An existing user was lost
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Lost user %d\n", epochTime, nId);	
}
// Callback: Detected a pose
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
	g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
	g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}
// Callback: Started calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Calibration started for user %d\n", epochTime, nId);
}
// Callback: Finished calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& capability, XnUserID nId, XnCalibrationStatus eStatus, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	if (eStatus == XN_CALIBRATION_STATUS_OK)
	{
		// Calibration succeeded
		printf("%d Calibration complete, start tracking user %d\n", epochTime, nId);		
		g_UserGenerator.GetSkeletonCap().StartTracking(nId);
	}
	else
	{
		// Calibration failed
		printf("%d Calibration failed for user %d\n", epochTime, nId);
		if(eStatus==XN_CALIBRATION_STATUS_MANUAL_ABORT)
		{
			printf("Manual abort occured, stop attempting to calibrate!");
			return;
		}
		if (g_bNeedPose)
		{
			g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
		}
		else
		{
			g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}
}

#define XN_CALIBRATION_FILE_NAME "UserCalibration.bin"

// Save calibration to file
void SaveCalibration()
{
	XnUserID aUserIDs[20] = {0};
	XnUInt16 nUsers = 20;
	g_UserGenerator.GetUsers(aUserIDs, nUsers);
	for (int i = 0; i < nUsers; ++i)
	{
		// Find a user who is already calibrated
		if (g_UserGenerator.GetSkeletonCap().IsCalibrated(aUserIDs[i]))
		{
			// Save user's calibration to file
			g_UserGenerator.GetSkeletonCap().SaveCalibrationDataToFile(aUserIDs[i], XN_CALIBRATION_FILE_NAME);
			break;
		}
	}
}
// Load calibration from file
void LoadCalibration()
{
	XnUserID aUserIDs[20] = {0};
	XnUInt16 nUsers = 20;
	g_UserGenerator.GetUsers(aUserIDs, nUsers);
	for (int i = 0; i < nUsers; ++i)
	{
		// Find a user who isn't calibrated or currently in pose
		if (g_UserGenerator.GetSkeletonCap().IsCalibrated(aUserIDs[i])) continue;
		if (g_UserGenerator.GetSkeletonCap().IsCalibrating(aUserIDs[i])) continue;

		// Load user's calibration from file
		XnStatus rc = g_UserGenerator.GetSkeletonCap().LoadCalibrationDataFromFile(aUserIDs[i], XN_CALIBRATION_FILE_NAME);
		if (rc == XN_STATUS_OK)
		{
			// Make sure state is coherent
			g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(aUserIDs[i]);
			g_UserGenerator.GetSkeletonCap().StartTracking(aUserIDs[i]);
		}
		break;
	}
}

// this function is called each frame
void glutDisplay (void)
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the OpenGL viewpoint
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	xn::SceneMetaData sceneMD;
	xn::DepthMetaData depthMD;
	g_DepthGenerator.GetMetaData(depthMD);
#ifndef USE_GLES
	glOrtho(0, depthMD.XRes(), depthMD.YRes(), 0, -1.0, 1.0);
#else
	glOrthof(0, depthMD.XRes(), depthMD.YRes(), 0, -1.0, 1.0);
#endif

	glDisable(GL_TEXTURE_2D);

	if (!g_bPause)
	{
		// Read next available data
		g_Context.WaitOneUpdateAll(g_UserGenerator);
	}

	// Process the data
	g_DepthGenerator.GetMetaData(depthMD);
	g_UserGenerator.GetUserPixels(0, sceneMD);
	DrawDepthMap(depthMD, sceneMD);

#ifndef USE_GLES
	;//glutSwapBuffers();
#endif
}

#ifndef USE_GLES
void glutIdle (void)
{
	if (g_bQuit) {
		CleanupExit();
	}

	// Display the frame
	glutPostRedisplay();
}

void glutKeyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		CleanupExit();
	case 'b':
		// Draw background?
		g_bDrawBackground = !g_bDrawBackground;
		break;
	case 'x':
		// Draw pixels at all?
		g_bDrawPixels = !g_bDrawPixels;
		break;
	case 's':
		// Draw Skeleton?
		g_bDrawSkeleton = !g_bDrawSkeleton;
		break;
	case 'i':
		// Print label?
		g_bPrintID = !g_bPrintID;
		break;
	case 'l':
		// Print ID & state as label, or only ID?
		g_bPrintState = !g_bPrintState;
		break;
	case'p':
		g_bPause = !g_bPause;
		break;
	case 'S':
		SaveCalibration();
		break;
	case 'L':
		LoadCalibration();
		break;
	}
}
void glInit (int * pargc, char ** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	glutCreateWindow ("User Tracker Viewer");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(glutKeyboard);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutIdle);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
#endif // USE_GLES

#define SAMPLE_XML_PATH "SamplesConfig.xml"

#define CHECK_RC(nRetVal, what)										\
	if (nRetVal != XN_STATUS_OK)									\
{																\
	printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));\
	return nRetVal;												\
}




//////////////////////////////////////////////////////////////////////////

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
	_page_view_edit = NULL;
	_page_view_catch = NULL;
	_opennni_create_successful = false;

}

void CactioncatchtoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_ANIMATION_MAIN, _animate_main);
	//DDX_Control(pDX, IDC_LIST_CATCH_FRAMES, _catch_frames_list);
	DDX_Control(pDX, IDC_TAB_MAIN, _tab_status);
}



BEGIN_MESSAGE_MAP(CactioncatchtoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CactioncatchtoolDlg::OnTcnSelchangeTabMain)
	ON_WM_MOVE()
END_MESSAGE_MAP()

BOOL CactioncatchtoolDlg::CreateViewGLContext(HDC hDC, HGLRC& hGLRC) {
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

	//glutMainLoop();
	// 设置计时器,10ms刷新一次
	SetTimer(1, 10, 0);
	// TODO: Add extra initialization here


	_tab_status.InsertItem(0 ,(LPCTSTR)"骨骼捕捉");//InsertItem(0," 呵呵，茂叶工作室 ");
	_tab_status.InsertItem(1 ,(LPCTSTR)"骨骼编辑");
	_tab_status.InsertItem(2, (LPCTSTR)"动作匹配");

	_page_view_catch = new DlgViewCatch(this);
	_page_view_catch->Create(IDD_DIALOG_TAB_Catch, this);

	_page_view_edit = new DlgViewEdit(this);
	_page_view_edit->Create(IDD_DIALOG_TAB_Edit, this);

	_page_view_action = new DlgActionCheck(this);
	_page_view_action->Create(IDD_DIALOG_TAB_EDIT_ACTION, this);
	CRect rect;
	_tab_status.GetClientRect(&rect);
	CRect temp_rect;
	_tab_status.GetWindowRect(&temp_rect);
	CRect temp_rect_main;
	this->GetClientRect(temp_rect_main);
	temp_rect.top = temp_rect.top + 20;
	temp_rect.left = temp_rect.left + 2;
	temp_rect.right = temp_rect.right - 4;
	temp_rect.bottom = temp_rect.bottom - 4;



	_page_view_catch->MoveWindow(&temp_rect);

	_page_view_edit->MoveWindow(&temp_rect);

	_page_view_action->MoveWindow(&temp_rect);
	g_tab_view_type = tab_view_catch;
	table_update();
	g_frameCatch.load();
	g_frameStorage.load();
	g_actionCheckStorage.load();
	//_tab_status.InsertItem();
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	//glutFullScreen();



	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	// openGL的初始化设置
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

	
	//Initial();
	glLoadIdentity();
	
	XnStatus nRetVal = XN_STATUS_OK;
	xn::EnumerationErrors errors;
	nRetVal = g_Context.InitFromXmlFile(SAMPLE_XML_PATH, g_scriptNode, &errors);
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (nRetVal);
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
		return (nRetVal);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		printf("No depth generator found. Using a default one...");
		xn::MockDepthGenerator mockDepth;
		nRetVal = mockDepth.Create(g_Context);
		CHECK_RC(nRetVal, "Create mock depth");

		// set some defaults
		XnMapOutputMode defaultMode;
		defaultMode.nXRes = 320;
		defaultMode.nYRes = 240;
		defaultMode.nFPS = 30;
		nRetVal = mockDepth.SetMapOutputMode(defaultMode);
		CHECK_RC(nRetVal, "set default mode");

		// set FOV
		XnFieldOfView fov;
		fov.fHFOV = 1.0225999419141749;
		fov.fVFOV = 0.79661567681716894;
		nRetVal = mockDepth.SetGeneralProperty(XN_PROP_FIELD_OF_VIEW, sizeof(fov), &fov);
		CHECK_RC(nRetVal, "set FOV");

		XnUInt32 nDataSize = defaultMode.nXRes * defaultMode.nYRes * sizeof(XnDepthPixel);
		XnDepthPixel* pData = (XnDepthPixel*)xnOSCallocAligned(nDataSize, 1, XN_DEFAULT_MEM_ALIGN);

		nRetVal = mockDepth.SetData(1, 0, nDataSize, pData);
		CHECK_RC(nRetVal, "set empty depth map");

		g_DepthGenerator = mockDepth;
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected, hCalibrationInProgress, hPoseInProgress;
	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
	{
		printf("Supplied user generator doesn't support skeleton\n");
		return 1;
	}
	nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
	CHECK_RC(nRetVal, "Register to user callbacks");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart, NULL, hCalibrationStart);
	CHECK_RC(nRetVal, "Register to calibration start");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(UserCalibration_CalibrationComplete, NULL, hCalibrationComplete);
	CHECK_RC(nRetVal, "Register to calibration complete");

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
	{
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
		{
			printf("Pose required, but not supported\n");
			return 1;
		}
		nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseDetected(UserPose_PoseDetected, NULL, hPoseDetected);
		CHECK_RC(nRetVal, "Register to Pose Detected");
		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationInProgress(MyCalibrationInProgress, NULL, hCalibrationInProgress);
	CHECK_RC(nRetVal, "Register to calibration in progress");

	nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseInProgress(MyPoseInProgress, NULL, hPoseInProgress);
	CHECK_RC(nRetVal, "Register to pose in progress");

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");
	_opennni_create_successful = true;

	
	//_page_view_catch->ShowWindow(TRUE);

	//_tab_status.InsertItem(1,(LPCTSTR)" 嘻嘻 ");
	//_tab_status.InsertItem(2,(LPCTSTR)" 哈哈，www.maoyeah.com ");
	////建立属性页各页
	//page0.Create(IDD_DIALOG0,GetDlgItem(IDC_TAB1));
	//page1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
	//page2.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB1));
	////设置页面的位置在m_tab控件范围内
	//CRect rect;
	//_tab_status.GetClientRect(&rect);
	//rect.top+=20;
	//rect.bottom-=5;
	//rect.left+=5;
	//rect.right-=5;
	//page0.MoveWindow(&rect);
	//page1.MoveWindow(&rect);
	//page2.MoveWindow(&rect);
	//page1.ShowWindow(TRUE);
	//m_tab.SetCurSel(1);

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


void CactioncatchtoolDlg::DrawLine(XnVector3D pos_1, XnVector3D pos_2)
{
	glVertex3f(pos_1.X, pos_1.Y, 0);
	glVertex3f(pos_2.X, pos_2.Y, 0);

}

void CactioncatchtoolDlg::RenderPerson(XnVector3D frame_point[XN_SKEL_MAX])
{
	glBegin(GL_LINES);
	DrawLine( frame_point[XN_SKEL_HEAD], frame_point[XN_SKEL_NECK]);
	DrawLine( frame_point[XN_SKEL_NECK], frame_point[XN_SKEL_LEFT_SHOULDER]);
	DrawLine( frame_point[XN_SKEL_LEFT_SHOULDER], frame_point[XN_SKEL_LEFT_ELBOW]);
	DrawLine( frame_point[XN_SKEL_LEFT_ELBOW], frame_point[XN_SKEL_LEFT_HAND]);

	DrawLine( frame_point[XN_SKEL_NECK], frame_point[XN_SKEL_RIGHT_SHOULDER]);
	DrawLine( frame_point[XN_SKEL_RIGHT_SHOULDER], frame_point[XN_SKEL_RIGHT_ELBOW]);
	DrawLine( frame_point[XN_SKEL_RIGHT_ELBOW], frame_point[XN_SKEL_RIGHT_HAND]);

	DrawLine( frame_point[XN_SKEL_LEFT_SHOULDER], frame_point[XN_SKEL_TORSO]);
	DrawLine( frame_point[XN_SKEL_RIGHT_SHOULDER], frame_point[XN_SKEL_TORSO]);

	DrawLine( frame_point[XN_SKEL_TORSO], frame_point[XN_SKEL_LEFT_HIP]);
	DrawLine( frame_point[XN_SKEL_LEFT_HIP], frame_point[XN_SKEL_LEFT_KNEE]);
	DrawLine( frame_point[XN_SKEL_LEFT_KNEE], frame_point[XN_SKEL_LEFT_FOOT]);

	DrawLine( frame_point[XN_SKEL_TORSO], frame_point[XN_SKEL_RIGHT_HIP]);
	DrawLine( frame_point[XN_SKEL_RIGHT_HIP], frame_point[XN_SKEL_RIGHT_KNEE]);
	DrawLine( frame_point[XN_SKEL_RIGHT_KNEE], frame_point[XN_SKEL_RIGHT_FOOT]);
	DrawLine( frame_point[XN_SKEL_LEFT_HIP], frame_point[XN_SKEL_RIGHT_HIP]);
	glEnd();

}


void CactioncatchtoolDlg::RenderScene() {

	wglMakeCurrent(hrenderDC,hrenderRC );
	//glutDisplay();
	//SwapBuffers(hrenderDC);

	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	//glLoadIdentity();
	//glTranslatef(0.0, 0.0, -5.0);
	//glBegin(GL_LINES);
	//glVertex3i(0.0, 1.0, 0.0);
	//glVertex3i(-1.0, -1.0, 0.0);
	//glVertex3i(-1.0, -1.0, 0.0);
	//glVertex3i(1.0, -1.0, 0.0);
	//glVertex3i(1.0, -1.0, 0.0);
	//glVertex3i(0.0, 1.0, 0.0);

	//glVertex3i(pt[1].X, pt[1].Y, 0)
	//////////////////////////////////////////////////////////////////////////
	//glPushMatrix();
	//glTranslated(-3.0f,-3.0f,3.0f);
	//glPopMatrix();
	//glutSolidSphere(2.0f,50,50);

	//////////////////////////////////////////////////////////////////////////


	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the OpenGL viewpoint
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	

	switch(g_tab_view_type)
	{
	case tab_view_catch:
		{


			switch(g_catch_view_type)
			{
			case catch_view_catch:
				if (_opennni_create_successful)
				{
					xn::SceneMetaData sceneMD;
					xn::DepthMetaData depthMD;
					g_DepthGenerator.GetMetaData(depthMD);

					GLdouble right_temp = depthMD.XRes();
					GLdouble bottom_temp = depthMD.YRes();
								#ifndef USE_GLES
					glOrtho(0, right_temp, bottom_temp, 0, -1.0, 1.0);
			#else
					glOrthof(0, right_temp, bottom_temp, 0, -1.0, 1.0);
			#endif
					glDisable(GL_TEXTURE_2D);
					if (!g_bPause)
					{
						// Read next available data
						g_Context.WaitOneUpdateAll(g_UserGenerator);
					}
					// Process the data
					g_DepthGenerator.GetMetaData(depthMD);
					g_UserGenerator.GetUserPixels(0, sceneMD);
					DrawDepthMap(depthMD, sceneMD);
					glEnd();

				}


				/*		glBegin(GL_LINES);
				glVertex3i(29.161575,62.882469, 0.0);
				glVertex3i(19.128357, 60.578716, 0.0);
				glEnd()*/;
				break;
			case catch_view_select:
				framedata* temp = g_frameCatch.get_cur_select();
				if (temp)
				{
		#ifndef USE_GLES
					glOrtho(0, temp->right_temp, temp->bottom_temp, 0, -1.0, 1.0);
		#else
					glOrthof(0, temp->right_temp, temp->bottom_temp, 0, -1.0, 1.0);
		#endif
					RenderPerson(temp->frame_point);

				}
				break;
			}
			

		}
		break;

	case tab_view_edit:
		{
			CString temp_entry;
			int cur_sel = _page_view_edit->_edit_frames.GetCurSel();
			if (cur_sel >= 0)
			{
				_page_view_edit->_edit_frames.GetText(cur_sel, temp_entry);
				frame_check* temp_check_frame = g_frameStorage.get_frame_check(temp_entry);
				if (temp_check_frame)
				{
					//framedata* temp_check_frame = g_frameCatch.get_cur_select();
					if (temp_check_frame)
					{
#ifndef USE_GLES
						glOrtho(0, temp_check_frame->right_temp, temp_check_frame->bottom_temp, 0, -1.0, 1.0);
#else
						glOrthof(0, temp_check_frame->right_temp, temp_check_frame->bottom_temp, 0, -1.0, 1.0);
#endif
						RenderPerson(temp_check_frame->frame_point);

					}
					//temp_check_frame
				}
			}

		}
		break;
	case  tab_view_action:
		{
			CString temp_entry;
			int cur_sel = _page_view_action->_list_frame_source.GetCurSel();
			if (cur_sel >= 0)
			{
				_page_view_action->_list_frame_source.GetText(cur_sel, temp_entry);
				frame_check* temp_check_frame = g_frameStorage.get_frame_check(temp_entry);
				if (temp_check_frame)
				{
					//framedata* temp_check_frame = g_frameCatch.get_cur_select();
					if (temp_check_frame)
					{
#ifndef USE_GLES
						glOrtho(0, temp_check_frame->right_temp, temp_check_frame->bottom_temp, 0, -1.0, 1.0);
#else
						glOrthof(0, temp_check_frame->right_temp, temp_check_frame->bottom_temp, 0, -1.0, 1.0);
#endif
						RenderPerson(temp_check_frame->frame_point);

					}
					//temp_check_frame
				}
			}


		}
		break;
	}
	SwapBuffers(hrenderDC);    // 使用glFlush()没有显示？
//	switch(g_catch_view_type)
//	{
//	case catch_view_catch:
//
//#ifndef USE_GLES
//		glOrtho(0, right_temp, bottom_temp, 0, -1.0, 1.0);
//#else
//		glOrthof(0, right_temp, bottom_temp, 0, -1.0, 1.0);
//#endif
//		glDisable(GL_TEXTURE_2D);
//		if (!g_bPause)
//		{
//			// Read next available data
//			g_Context.WaitOneUpdateAll(g_UserGenerator);
//		}
//		// Process the data
//		g_DepthGenerator.GetMetaData(depthMD);
//		g_UserGenerator.GetUserPixels(0, sceneMD);
//		DrawDepthMap(depthMD, sceneMD);
//		glEnd();
//		/*		glBegin(GL_LINES);
//		glVertex3i(29.161575,62.882469, 0.0);
//		glVertex3i(19.128357, 60.578716, 0.0);
//		glEnd()*/;
//		break;
//	case catch_view_select:
//		framedata* temp = g_frameCatch.get_cur_select();
//		if (temp)
//		{
//#ifndef USE_GLES
//			glOrtho(0, temp->right_temp, temp->bottom_temp, 0, -1.0, 1.0);
//#else
//			glOrthof(0, temp->right_temp, temp->bottom_temp, 0, -1.0, 1.0);
//#endif
//			RenderPerson(temp->frame_point);
//
//		}
//		break;
	//}


	
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


	//CString select_string;
	//_catch_frames_list.GetText(_catch_frames_list.GetCurSel(), select_string);
	
	// TODO: Add your control notification handler code here
}

void CactioncatchtoolDlg::table_update()
{
	switch(g_tab_view_type)
	{
	case tab_view_catch:
		_page_view_catch->ShowWindow(TRUE);
		_page_view_edit->ShowWindow(FALSE);
		_page_view_action->ShowWindow(FALSE);
		break;
	case tab_view_edit:
		_page_view_catch->ShowWindow(FALSE);
		_page_view_edit->ShowWindow(TRUE);
		_page_view_action->ShowWindow(FALSE);
		break;
	case tab_view_action:
		_page_view_catch->ShowWindow(FALSE);
		_page_view_edit->ShowWindow(FALSE);
		_page_view_action->ShowWindow(TRUE);
		break;
	}
}


void CactioncatchtoolDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int CurSel;
	CurSel=_tab_status.GetCurSel();
	g_tab_view_type = (tab_view_type)CurSel;
	table_update();

}


void CactioncatchtoolDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if (_page_view_catch&& _page_view_edit)
	{
		CRect temp_rect;
		_tab_status.GetWindowRect(&temp_rect);	
		temp_rect.top = temp_rect.top + 20;
		temp_rect.left = temp_rect.left + 2;
		temp_rect.right = temp_rect.right - 4;
		temp_rect.bottom = temp_rect.bottom - 4;
		_page_view_catch->MoveWindow(&temp_rect);
		_page_view_edit->MoveWindow(&temp_rect);
		_page_view_action->MoveWindow(&temp_rect);
	}

	// TODO: Add your message handler code here
}
