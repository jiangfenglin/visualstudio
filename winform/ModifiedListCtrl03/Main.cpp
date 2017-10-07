/////////////////////////////////////////////////////////////////////////////
// Main.cpp : Defines the class behaviors for the application.
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Main.h"
#include "MainFrame.h"
#include "ChildFrame.h"
#include "MainDoc.h"
#include "MainView.h"
#include "About.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainApp
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainApp, CWinApp)
	//{{AFX_MSG_MAP(CMainApp)
	ON_COMMAND_RANGE(ID_TABLE_NULL, ID_TABLE_MAX, OnTable)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*** For all tables ***

/////////////////////////////////////////////////////////////////////////////
// Table header font structure
/////////////////////////////////////////////////////////////////////////////
LOGFONT CMainApp::m_LogHdrFont = {
	-15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 1, 2, 2, FF_DONTCARE, 
	_T("MS Sans Serif")
};

/////////////////////////////////////////////////////////////////////////////
// Table list font structure
/////////////////////////////////////////////////////////////////////////////
LOGFONT CMainApp::m_LogListFont = {
	-15, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 1, 2, 2,	FF_DONTCARE, 
	_T("MS Sans Serif")
};

//*** For Table 1 ***

/////////////////////////////////////////////////////////////////////////////
// Table 1 name
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_szTblName1 = _T("First table");;

/////////////////////////////////////////////////////////////////////////////
// Frame 1 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_FrmRect1 = {-2, -1, 702, 578};

/////////////////////////////////////////////////////////////////////////////
// View 1 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_ViewRect1 = {0, 25, 692, 548};

/////////////////////////////////////////////////////////////////////////////
// The meta table 1 header structure array
/////////////////////////////////////////////////////////////////////////////
META_HEADER CMainApp::m_aMetaHeader1[] = {
	{_T("Ind. No"),		 LVCFMT_RIGHT,		 50},
	{_T("Empl. Id"),	 LVCFMT_RIGHT,		 57},
	{_T("Title"),			 LVCFMT_LEFT,			225},
	{_T("Name"),			 LVCFMT_LEFT,			150},
	{_T("Birthday"),	 LVCFMT_CENTER,		 85},
	{_T("Work Phone"), LVCFMT_CENTER,		105}
};

/////////////////////////////////////////////////////////////////////////////
// The table 1 rows text array
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_apRowText1[] = {
		_T(" 1"),	_T("123"), _T("Sales Representative"),	_T("Andrew Overling"),   _T("01.01.1981"),	_T("555-1111"),
		_T(" 2"),	_T("321"), _T("Vice President, Sales"), _T("Janet Savolio"),	   _T("02.02.1982"),	_T("555-2222"),
		_T(" 3"),	_T("444"), _T("Sales Representative"),	_T("Alex Romb"),		     _T("03.03.1983"),	_T("555-3333"),
		_T(" 4"),	_T("222"), _T("Sales Manager"),					_T("Roy Trix"),				   _T("04.04.1984"),	_T("555-4444"),
		_T(" 5"),	_T("458"), _T("Sales Representative"),	_T("Steven Puller"),		 _T("05.05.1985"),	_T("555-5555"),
		_T(" 6"),	_T("753"), _T("Sales Manager"),					_T("Brad Hamer"),				 _T("06.06.1986"),	_T("555-6666"),
		_T(" 7"),	_T("159"), _T("Sales Manager"),					_T("Margaret Luchanan"), _T("07.07.1987"),	_T("555-7777"),
		_T(" 8"),	_T("111"), _T("Secretary"),							_T("Nancy Kuller"),			 _T("08.08.1988"),	_T("555-8888"),
		_T(" 9"),	_T("777"), _T("Sales Analyst"),					_T("Anatoly Suren"),		 _T("09.09.1989"),	_T("555-9999"),
		_T("10"),	_T("555"), _T("Cleaning Woman"),				_T("Susan Scrub"),			 _T("10.10.1990"),	_T("555-0000")
};

//*** For Table 2 ***

/////////////////////////////////////////////////////////////////////////////
// Table 2 name
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_szTblName2 = _T("Second table");;

/////////////////////////////////////////////////////////////////////////////
// Frame 2 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_FrmRect2 = {250, -1, 838, 495+20};

/////////////////////////////////////////////////////////////////////////////
// View 2 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_ViewRect2 = {0, 25, 576, 450};

/////////////////////////////////////////////////////////////////////////////
// The meta table 2 header structure array
/////////////////////////////////////////////////////////////////////////////
META_HEADER CMainApp::m_aMetaHeader2[] = {
	{_T("Ind. No"),		 LVCFMT_RIGHT,		 50},
	{_T("Empl. Id"),	 LVCFMT_RIGHT,		 57},
	{_T("Title"),			 LVCFMT_LEFT,			170},
	{_T("Name"),			 LVCFMT_LEFT,			125},
	{_T("Birthday"),	 LVCFMT_CENTER,		 80},
	{_T("Work Phone"), LVCFMT_CENTER,		 74}
};

/////////////////////////////////////////////////////////////////////////////
// The table 2 rows text array
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_apRowText2[] = {
		_T(" 8"),	_T("111"), _T("Secretary"),							_T("Nancy Kuller"),			 _T("08.08.1988"),	_T("555-8888"),
		_T(" 1"),	_T("123"), _T("Sales Representative"),	_T("Andrew Overling"),   _T("01.01.1981"),	_T("555-1111"),
		_T(" 7"),	_T("159"), _T("Sales Manager"),					_T("Margaret Luchanan"), _T("07.07.1987"),	_T("555-7777"),
		_T(" 4"),	_T("222"), _T("Sales Manager"),					_T("Roy Trix"),				   _T("04.04.1984"),	_T("555-4444"),
		_T(" 2"),	_T("321"), _T("Vice President, Sales"), _T("Janet Savolio"),	   _T("02.02.1982"),	_T("555-2222"),
		_T(" 3"),	_T("444"), _T("Sales Representative"),	_T("Alex Romb"),		     _T("03.03.1983"),	_T("555-3333"),
		_T(" 5"),	_T("458"), _T("Sales Representative"),	_T("Steven Puller"),		 _T("05.05.1985"),	_T("555-5555"),
		_T("10"),	_T("555"), _T("Cleaning Woman"),				_T("Susan Scrub"),			 _T("10.10.1990"),	_T("555-0000"),
		_T(" 6"),	_T("753"), _T("Sales Manager"),					_T("Brad Hamer"),				 _T("06.06.1986"),	_T("555-6666"),
		_T(" 9"),	_T("777"), _T("Sales Analyst"),					_T("Anatoly Suren"),		 _T("09.09.1989"),	_T("555-9999")
};

//*** For Table 3 ***

/////////////////////////////////////////////////////////////////////////////
// Table 3 name
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_szTblName3 = _T("Third table");;

/////////////////////////////////////////////////////////////////////////////
// Frame 3 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_FrmRect3 = {390, 300, 865, 600};

/////////////////////////////////////////////////////////////////////////////
// View 3 rectangle coordinates
/////////////////////////////////////////////////////////////////////////////
RECT CMainApp::m_ViewRect3 = {0, 25, 464, 268};

/////////////////////////////////////////////////////////////////////////////
// The meta table 3 header structure array
/////////////////////////////////////////////////////////////////////////////
META_HEADER CMainApp::m_aMetaHeader3[] = {
	{_T("Ind. No"),		 LVCFMT_RIGHT,		 30},
	{_T("Empl. Id"),	 LVCFMT_RIGHT,		 35},
	{_T("Title"),			 LVCFMT_LEFT,			135},
	{_T("Name"),			 LVCFMT_LEFT,			110},
	{_T("Birthday"),	 LVCFMT_CENTER,		 70},
	{_T("Work Phone"), LVCFMT_CENTER,		 64}
};

/////////////////////////////////////////////////////////////////////////////
// The table 3 rows text array
/////////////////////////////////////////////////////////////////////////////
TCHAR *CMainApp::m_apRowText3[] = {
		_T(" 3"),	_T("444"), _T("Sales Representative"),	_T("Alex Romb"),		     _T("03.03.1983"),	_T("555-3333"),
		_T(" 9"),	_T("777"), _T("Sales Analyst"),					_T("Anatoly Suren"),		 _T("09.09.1989"),	_T("555-9999"),
		_T(" 1"),	_T("123"), _T("Sales Representative"),	_T("Andrew Overling"),   _T("01.01.1981"),	_T("555-1111"),
		_T(" 6"),	_T("753"), _T("Sales Manager"),					_T("Brad Hamer"),				 _T("06.06.1986"),	_T("555-6666"),
		_T(" 2"),	_T("321"), _T("Vice President, Sales"), _T("Janet Savolio"),	   _T("02.02.1982"),	_T("555-2222"),
		_T(" 7"),	_T("159"), _T("Sales Manager"),					_T("Margaret Luchanan"), _T("07.07.1987"),	_T("555-7777"),
		_T(" 8"),	_T("111"), _T("Secretary"),							_T("Nancy Kuller"),			 _T("08.08.1988"),	_T("555-8888"),
		_T(" 4"),	_T("222"), _T("Sales Manager"),					_T("Roy Trix"),				   _T("04.04.1984"),	_T("555-4444"),
		_T(" 5"),	_T("458"), _T("Sales Representative"),	_T("Steven Puller"),		 _T("05.05.1985"),	_T("555-5555"),
		_T("10"),	_T("555"), _T("Cleaning Woman"),				_T("Susan Scrub"),			 _T("10.10.1990"),	_T("555-0000")
};

/////////////////////////////////////////////////////////////////////////////
// CMainApp construction
/////////////////////////////////////////////////////////////////////////////
CMainApp::CMainApp() {
	//*** The CMultiDocTemplate class pointer
	m_pDocTemplate = NULL;

	//*** Common height of main frame tollbar, tab and status line
	m_nClientCtrlsHeight = 68;

	//*** Common width of main frame for border
	m_nMainFrmBorders = 2;
	
	//*** Common offset for child frames
	m_nChildFrmOffset = -1;

	//*** Table Id
	m_eTable = e_NULL;  // Empty Form Index

	//*** Main frame pointer
	m_pMainFrame = NULL;

	//*** Initializes pointer arrays to null
	for(UINT i = e_NULL; i < e_MAX; i++) {
		m_apTable[i] = NULL;  // Table pointers array
		m_apFrame[i] = NULL;  // Child frame pointers array
	}

	//*** For all tables ***

	//*** Table style
	DWORD dwStyle =	0;

	//*** Calls WM_DRAWITEM messages into CListCtrlEx and CHeaderCtrlEx 
	// and WM_MEASUREITEM message into CListCtrlEx
	dwStyle |= LVS_OWNERDRAWFIXED;  // = 1024

	dwStyle |= LVS_REPORT;  // Sets the Report mode (base style)  // = 1
	dwStyle |= LVS_OWNERDATA;  // Sets the Virtual mode  // = 4096
	dwStyle |= WS_CHILD;  // Creates a child window  // = 1073741824
	dwStyle |= WS_BORDER;  // Creates a window that has a border  // = 8388608
	dwStyle |= WS_VISIBLE;  // Makes visible (to don't use ShowWindow)  // = 268435456
	
	//*** Extended table style
	DWORD dwExStyle = 0;

	dwExStyle |= LVS_EX_GRIDLINES;  // Draws grid lines  // = 1
	//dwExStyle |= LVS_EX_DOUBLEBUFFER;

	//*** Initializes the header font structure
	m_HdrFont.CreateFontIndirect(&m_LogHdrFont);

	//*** Initializes the list font structure
	m_ListFont.CreateFontIndirect(&m_LogListFont);
	
	//*** The meta table 0 structure array

	m_aMetaTable[e_NULL].szTblName = NULL;  // Table name
	m_aMetaTable[e_NULL].dwStyle = 0;  // Table style
	m_aMetaTable[e_NULL].dwExStyle = 0;  // Extended table style
	m_aMetaTable[e_NULL].pFrmRect = NULL;  // Frame rectangle pointer
	m_aMetaTable[e_NULL].pViewRect = NULL;  // View rectangle pointer
	m_aMetaTable[e_NULL].pHdrFont = NULL;  // Table header font pointer
	m_aMetaTable[e_NULL].pListFont = NULL;  // Table list font pointer
	m_aMetaTable[e_NULL].nHdrHeight = 0;  // Table header height
	m_aMetaTable[e_NULL].nListHeight = 0;  // Table list height
	m_aMetaTable[e_NULL].nColCount = 0;  // Table header columns count
	m_aMetaTable[e_NULL].nRowCount = 0;  // Table list row count
	m_aMetaTable[e_NULL].apRowText = NULL;  // Table rows text array
	m_aMetaTable[e_NULL].apMetaHeader = NULL;  // Meta table header pointer

	//*** For Table 1 ***

	//*** The table 1 header height
	UINT nHdrHeight1 = 70;

	//*** The table 1 list height
	UINT nListHeight1 = 40;

	//*** The table 1 columns count
	UINT nColCount1 = sizeof(m_aMetaHeader1) / sizeof(m_aMetaHeader1[0]);

	//*** The table 1 rows count
	UINT nRowCount1 = sizeof(m_apRowText1) / sizeof(m_apRowText1[0]);;

	nRowCount1 /= nColCount1;

	m_aMetaTable[e_First].szTblName = m_szTblName1;	 // TCHAR *szTblName;  // Table name
	m_aMetaTable[e_First].dwStyle = dwStyle; 	// DWORD dwStyle;  // Table style
	m_aMetaTable[e_First].dwExStyle = dwExStyle;	// DWORD dwExStyle;  // Extended table style
	m_aMetaTable[e_First].pFrmRect = &m_FrmRect1;	// RECT *pFrmRect;  // Frame rectangle pointer
	m_aMetaTable[e_First].pViewRect = &m_ViewRect1;	// RECT *pViewRect;  // View rectangle pointer
	m_aMetaTable[e_First].pHdrFont = &m_HdrFont;  // CFont *pHdrFont;  // Table header font pointer
	m_aMetaTable[e_First].pListFont = &m_ListFont;  // CFont *pListFont;  // Table list font pointer
	m_aMetaTable[e_First].nHdrHeight = nHdrHeight1;  // UINT nHdrHeight;  // Table header height
	m_aMetaTable[e_First].nListHeight = nListHeight1;  // UINT nListHeight;  // Table list height
	m_aMetaTable[e_First].nColCount = nColCount1;  // UINT nColCount;  // Table header columns count
	m_aMetaTable[e_First].nRowCount = nRowCount1;  // UINT nRowCount;  // Table list row count
	m_aMetaTable[e_First].apRowText = m_apRowText1;  // TCHAR **apRowText;  // Table rows text array
	m_aMetaTable[e_First].apMetaHeader = m_aMetaHeader1;  // HEADER *pMetaHeader;  // Meta table header pointer

	//*** For Table 2 ***

	//*** The table 2 header height
	UINT nHdrHeight2 = 90;

	//*** The table 2 list height
	UINT nListHeight2 = 30;

	//*** The table 2 columns count
	UINT nColCount2 = sizeof(m_aMetaHeader2) / sizeof(m_aMetaHeader2[0]);

	//*** The table 2 rows count
	UINT nRowCount2 = sizeof(m_apRowText2) / sizeof(m_apRowText2[0]);

	nRowCount2 /= nColCount2;

	m_aMetaTable[e_Second].szTblName = m_szTblName2;	 // TCHAR *szTblName;  // Table name
	m_aMetaTable[e_Second].dwStyle = dwStyle; 	// DWORD dwStyle;  // Table style
	m_aMetaTable[e_Second].dwExStyle = dwExStyle;	// DWORD dwExStyle;  // Extended table style
	m_aMetaTable[e_Second].pFrmRect = &m_FrmRect2;	// RECT *pFrmRect;  // Frame rectangle pointer
	m_aMetaTable[e_Second].pViewRect = &m_ViewRect2;	// RECT *pViewRect;  // View rectangle pointer
	m_aMetaTable[e_Second].pHdrFont = &m_HdrFont;  // CFont *pHdrFont;  // Table header font pointer
	m_aMetaTable[e_Second].pListFont = &m_ListFont;  // CFont *pListFont;  // Table list font pointer
	m_aMetaTable[e_Second].nHdrHeight = nHdrHeight2;  // UINT nHdrHeight;  // Table header height
	m_aMetaTable[e_Second].nListHeight = nListHeight2;  // UINT nListHeight;  // Table list height
	m_aMetaTable[e_Second].nColCount = nColCount2;  // UINT nColCount;  // Table header columns count
	m_aMetaTable[e_Second].nRowCount = nRowCount2;  // UINT nRowCount;  // Table list row count
	m_aMetaTable[e_Second].apRowText = m_apRowText2;  // TCHAR **apRowText;  // Table rows text array
	m_aMetaTable[e_Second].apMetaHeader = m_aMetaHeader2;  // HEADER *pMetaHeader;  // Meta table header pointer

	//*** For Table 3 ***

	//*** The table 3 header height
	UINT nHdrHeight3 = 18;

	//*** The table 3 list height
	UINT nListHeight3 = 18;

	//*** The table 3 columns count
	UINT nColCount3 = sizeof(m_aMetaHeader3) / sizeof(m_aMetaHeader3[0]);

	//*** The table 3 rows count
	UINT nRowCount3 = sizeof(m_apRowText3) / sizeof(m_apRowText3[0]);

	nRowCount3 /= nColCount3;

	m_aMetaTable[e_Third].szTblName = m_szTblName3;	 // TCHAR *szTblName;  // Table name
	m_aMetaTable[e_Third].dwStyle = dwStyle; 	// DWORD dwStyle;  // Table style
	m_aMetaTable[e_Third].dwExStyle = dwExStyle;	// DWORD dwExStyle;  // Extended table style
	m_aMetaTable[e_Third].pFrmRect = &m_FrmRect3;	// RECT *pFrmRect;  // Frame rectangle pointer
	m_aMetaTable[e_Third].pViewRect = &m_ViewRect3;	// RECT *pViewRect;  // View rectangle pointer
	m_aMetaTable[e_Third].pHdrFont = &m_HdrFont;  // CFont *pHdrFont;  // Table header font pointer
	m_aMetaTable[e_Third].pListFont = &m_ListFont;  // CFont *pListFont;  // Table list font pointer
	m_aMetaTable[e_Third].nHdrHeight = nHdrHeight3;  // UINT nHdrHeight;  // Table header height
	m_aMetaTable[e_Third].nListHeight = nListHeight3;  // UINT nListHeight;  // Table list height
	m_aMetaTable[e_Third].nColCount = nColCount3;  // UINT nColCount;  // Table header columns count
	m_aMetaTable[e_Third].nRowCount = nRowCount3;  // UINT nRowCount;  // Table list row count
	m_aMetaTable[e_Third].apRowText = m_apRowText3;  // TCHAR **apRowText;  // Table rows text array
	m_aMetaTable[e_Third].apMetaHeader = m_aMetaHeader3;  // HEADER *pMetaHeader;  // Meta table header pointer
}  // CMainApp

/////////////////////////////////////////////////////////////////////////////
// CMainApp initialization
/////////////////////////////////////////////////////////////////////////////
BOOL CMainApp::InitInstance() {
	//*** Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need.

	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif

	//*** Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("The Modified ListCtrl"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	//*** Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.

	//*** Saves the CMultiDocTemplate class pointer
	m_pDocTemplate = new CMultiDocTemplate(
			IDR_MAINTYPE,
			RUNTIME_CLASS(CMainDoc),
			RUNTIME_CLASS(CChildFrame),  // Custom MDI child frame
			RUNTIME_CLASS(CMainView)
			);

	//*** It's need for CWinApp::OnFileNew function into CMainApp::OnTable handler
	AddDocTemplate(m_pDocTemplate);
	
	//*** Create main MDI frame window
	CMainFrame *pMainFrame = new CMainFrame;

	if(!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;

	m_pMainWnd = pMainFrame;

	//*** Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//*** Dispatch commands specified on the command line
	//if(!ProcessShellCommand(cmdInfo))
			//return FALSE;

	//*** The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}  // InitInstance

/////////////////////////////////////////////////////////////////////////////
// OnTable
/////////////////////////////////////////////////////////////////////////////
void CMainApp::OnTable(UINT nTable) {
	//*** Calculates m_eTable
	m_eTable = (ETABLE) (nTable - ID_TABLE_NULL);

	if(m_eTable <= e_NULL || m_eTable >= e_MAX) {
		_M("No data is for this table!");
		return;
	}

	//*** Current child frame pointer
	CChildFrame *pChildFrame = m_apFrame[m_eTable];

	if(pChildFrame) {
		//*** Activates current child frame
		pChildFrame->ActivateFrame();

		//*** Checks the pointer before to call m_MainTabs.Update()
		if(!m_pMainFrame) {
			_M("CMainApp: Empty a CMainFrame object!");
			return;
		}

		//*** Updates tabs
		m_pMainFrame->m_MainTabs.Update();

		return;
	}

	//*** Creates a new child frame with a document
	//*
	CWinApp::OnFileNew();
	//*
	//*** Creates a new child frame with a document

	//*** Creates a new child frame without a document
	//*** Doesn't call CMainView::OnInitialUpdate() and ignores a call of
	//* CMainView::SetScaleToFitSize function 
	//*
	/*if(!m_pDocTemplate) {
		_M("CMainApp: Empty a CMultiDocTemplate object!");
		return;
	}
	
	pChildFrame = reinterpret_cast<CChildFrame *>(
			m_pDocTemplate->CreateNewFrame(NULL, NULL)
	);

	//*** Current meta table static structure
	META_TABLE MetaTable = m_aMetaTable[m_eTable];

	//*** Sets a title of child frame
	pChildFrame->SetTitle(MetaTable.szTblName);

	//*** Activates current child frame
	pChildFrame->ActivateFrame();*/
	//*
	//*** Creates a new child frame without a document

	//*** Checks the pointer before to call m_MainTabs.Update()
	if(!m_pMainFrame) {
		_M("CMainApp: Empty a CMainFrame object!");
		return;
	}

	//*** Updates tabs
	m_pMainFrame->m_MainTabs.Update();
}  // OnTable

/////////////////////////////////////////////////////////////////////////////
// OnAppAbout : App command to run the dialog
/////////////////////////////////////////////////////////////////////////////
void CMainApp::OnAppAbout() {
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}  // OnAppAbout
/*
/////////////////////////////////////////////////////////////////////////////
// ExitInstance
/////////////////////////////////////////////////////////////////////////////
int CMainApp::ExitInstance() {
	return CWinApp::ExitInstance();
}  // ExitInstance
*/
/////////////////////////////////////////////////////////////////////////////
// The one and only CMainApp object
/////////////////////////////////////////////////////////////////////////////
CMainApp theApp;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
