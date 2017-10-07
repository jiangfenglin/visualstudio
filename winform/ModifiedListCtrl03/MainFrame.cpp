/////////////////////////////////////////////////////////////////////////////
// MainFrame.cpp : implementation of the CMainFrame class
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Main.h"
#include "MainFrame.h"
#include "ChildFrame.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction
/////////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame() {
	//*** Main application pointer
	m_pMainApp = reinterpret_cast<CMainApp *>(AfxGetApp());

	if(!m_pMainApp) {
		_M("CMainFrame: Empty object of the CMainApp class!");
		return;
	}

	//*** Saves the current CChildFrame object
	m_pMainApp->m_pMainFrame = this;
}  // CMainFrame

/////////////////////////////////////////////////////////////////////////////
// CMainFrame destruction
/////////////////////////////////////////////////////////////////////////////
CMainFrame::~CMainFrame() {
}  // ~CMainFrame

/////////////////////////////////////////////////////////////////////////////
// OnCreate
/////////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT pCS) {
	if(CMDIFrameWnd::OnCreate(pCS) == -1) {
		_M("CMainFrame: Failed to call CMDIFrameWnd::OnCreate function!");
		
		return -1;
	}
	
	DWORD dwCtrlStyle = TBSTYLE_FLAT;
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|
			CBRS_FLYBY|CBRS_SIZE_DYNAMIC;

	//*** Creates the first toolbar
	if(!m_ToolBar.CreateEx(this, dwCtrlStyle, dwStyle)) {
		_M("CMainFrame: Failed to create main toolbar!");
		
		return -1;
	}

	//*** Loads the first toolbar
	if(!m_ToolBar.LoadToolBar(IDR_MAINFRAME)) {
		_M("CMainFrame: Failed to load main toolbar!");
		
		return -1;
	}

	//*** Creates the second toolbar
	if(!m_ToolBar2.CreateEx(this, dwCtrlStyle, dwStyle)) {
		_M("CMainFrame: Failed to create table toolbar!");
		
		return -1;
	}

	//*** Loads the second toolbar
	if(!m_ToolBar2.LoadToolBar(IDR_TOOLBAR_TABLES)) {
		_M("CMainFrame: Failed to load tables toolbar!");
		
		return -1;
	}

	//*** To enable dockable control bars in the frame window
	EnableDocking(CBRS_ALIGN_ANY);
	
	//*** To enable the control bars to be docked
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	
	//*** Causes the control bar to be docked to the frame window
	DockControlBar(&m_ToolBar);

	//*** Called when the control bars are toggled on or off or when the frame 
	// window is resized
	RecalcLayout();
	
	RECT Rect = {0};
	
	//*** Copies the dimensions of the bounding rectangle of the toolbar to 
	// the structure pointed to by &Rect
	m_ToolBar.GetWindowRect(&Rect);

	//*** Docking the toolbars side by side

	Rect.left++;

	DockControlBar(&m_ToolBar2, AFX_IDW_DOCKBAR_TOP, &Rect);
	
	//*** Creates the status bar
	if(!m_StatusBar.Create(this)) {
		_M("CMainFrame: Failed to create status bar!");
		
		return -1;
	}

	//*** Sets indicators for the status bar
	if(!m_StatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT))) {
		_M("CMainFrame: Failed to set indicators for status bar!");
		
		return -1;
	}

  //*** CMainTabs must be created at last to ensure correct layout!
	m_MainTabs.Create(this);

	return 0;
}  // OnCreate
/*
/////////////////////////////////////////////////////////////////////////////
// PreCreateWindow
/////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &CS) {
	if(!CMDIFrameWnd::PreCreateWindow(CS))
			return FALSE;

	return TRUE;
}  // PreCreateWindow
*/
/////////////////////////////////////////////////////////////////////////////
// OnSize
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSize(UINT nType, int cx, int cy) {
	CMDIFrameWnd::OnSize(nType, cx, cy);

	//*** True sizes of the main frame client
	int nMainWidth = cx - m_pMainApp->m_nMainFrmBorders;
	int nMainHeight = cy - m_pMainApp->m_nClientCtrlsHeight;

	//*** Current child frame rectangle
	RECT ChildRect = {0};  // For safe change a child rectangle
	RECT *pChildRect = NULL;

	//*** Table Id
	ETABLE eTable = m_pMainApp->m_eTable;

	if(!eTable) {
		//_M("CMainFrame: No objects is in the application!");
		return;  // Simply exit
	}

	//*** Current child frame pointer
	CChildFrame **apChildFrame = m_pMainApp->m_apFrame;
	CChildFrame *pChildFrame = NULL;

	//*** The meta table structure
	META_TABLE *aMetaTable = m_pMainApp->m_aMetaTable;

	//*** Sizes of child frames
	int nChildLeft = 0;
	int nChildTop = 0;
	int nChildWidth = 0;
	int nChildHeight = 0;

	//*** Look at the child frame array
	for(UINT i = e_NULL; i < e_MAX; i++) {
		pChildFrame = apChildFrame[i];

		if(!pChildFrame)
				continue;
		
		pChildRect = aMetaTable[i].pFrmRect;

		if(!pChildRect) {
			_M("CChildFrame: Empty a child rectangle!");
			return;
		}

		//*** Sizes of the child frame
		nChildLeft = pChildRect->left;
		nChildTop = pChildRect->top;
		nChildWidth = pChildRect->right - pChildRect->left;
		nChildHeight = pChildRect->bottom - pChildRect->top;

		//*** Changes sizes and locality of the child frame

		if(nChildWidth > nMainWidth) {
			ChildRect.left = 0;
			ChildRect.right = nMainWidth;
		} else if(nChildLeft > nMainWidth - nChildWidth) {
			ChildRect.left = nMainWidth - nChildWidth;
			ChildRect.right = nMainWidth;
		} else {
			ChildRect.left = nChildLeft;
			ChildRect.right = nChildLeft + nChildWidth;
		}

		if(nChildHeight > nMainHeight) {
			ChildRect.top = 0;
			ChildRect.bottom = nMainHeight;
		} else if(nChildTop > nMainHeight - nChildHeight) {
			ChildRect.top = nMainHeight - nChildHeight;
			ChildRect.bottom = nMainHeight;
		} else {
			ChildRect.top = nChildTop;
			ChildRect.bottom = nChildTop + nChildHeight;
		}

		pChildFrame->MoveWindow(&ChildRect);
	}

	pChildFrame = m_pMainApp->m_apFrame[eTable];

	if(pChildFrame) {
		//*** Activates current child frame
		pChildFrame->ActivateFrame();

		//*** Updates tabs
		m_MainTabs.Update();
	}
}  // OnSize

/////////////////////////////////////////////////////////////////////////////
// OnDestroy - to run the debug release application correctly
/////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnDestroy() {
	//*** Current child frame
	CChildFrame *pFrame = NULL;
	
	for(int i = e_NULL; i < e_MAX; i++) {
		pFrame = m_pMainApp->m_apFrame[i];

		if(pFrame) {
			//*** Destroys current child frame
			if(!pFrame->DestroyWindow()) {
				_M("CMainFrame: Failed to call CChildFrame::DestroyWindow function!");
				continue;
			}
		}
	}

	CMDIFrameWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////////////////
	// AssertValid
	/////////////////////////////////////////////////////////////////////////////
	void CMainFrame::AssertValid() const {
		CMDIFrameWnd::AssertValid();
	}  // AssertValid

	/////////////////////////////////////////////////////////////////////////////
	// Dump
	/////////////////////////////////////////////////////////////////////////////
	void CMainFrame::Dump(CDumpContext &dc) const {
		CMDIFrameWnd::Dump(dc);
	}  // Dump
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
