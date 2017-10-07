/////////////////////////////////////////////////////////////////////////////
// ChildFrame.cpp : implementation of the CChildFrame class
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "MainFrame.h"
#include "ChildFrame.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CHILDACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction
/////////////////////////////////////////////////////////////////////////////
CChildFrame::CChildFrame() {
	//*** Main application pointer
	m_pMainApp = reinterpret_cast<CMainApp *>(AfxGetApp());

	if(!m_pMainApp) {
		_M("CChildFrame: Empty object of the CMainApp class!");
		return;
	}

	//*** Main frame pointer
	m_pMainFrame = m_pMainApp->m_pMainFrame;

	if(!m_pMainFrame) {
		_M("CChildFrame: Empty object of the CMainFrame class!");
		return;
	}

	//*** Table Id
	m_eTable = m_pMainApp->m_eTable;

	if(!m_eTable) {
		_M("CChildFrame: No objects is in the application!");
		return;
	}

	//*** The meta table structure
	m_MetaTable = m_pMainApp->m_aMetaTable[m_eTable];

	//*** Saves the current CChildFrame object
	m_pMainApp->m_apFrame[m_eTable] = this;
}  // CChildFrame

/////////////////////////////////////////////////////////////////////////////
// CChildFrame destruction
/////////////////////////////////////////////////////////////////////////////
CChildFrame::~CChildFrame() {
	//*** Initializes pointers to null
	m_pMainApp->m_apTable[m_eTable] = NULL;  // Table pointers array
	m_pMainApp->m_apFrame[m_eTable] = NULL;  // Child frame pointers array

	//*** Updates tabs
	m_pMainFrame->m_MainTabs.Update();
}  // ~CChildFrame

/////////////////////////////////////////////////////////////////////////////
// CChildFrame
/////////////////////////////////////////////////////////////////////////////
BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs) {
	if(!CMDIChildWnd::PreCreateWindow(cs)) {
		_M("CChildFrame: Failed to call CMDIChildWnd::PreCreateWindow function!");
		
		return FALSE;
	}
	
	//*** Current main frame rectangle
	RECT MainRect = {0};

	//*** Get sizes of the client rectangle
	m_pMainFrame->GetClientRect(&MainRect);

	//*** True sizes of the main frame client
	int nMainWidth = MainRect.right - m_pMainApp->m_nMainFrmBorders - MainRect.left;
	int nMainHeight = MainRect.bottom - m_pMainApp->m_nClientCtrlsHeight - MainRect.top;

	//RECT ChildRect = {0};  // For safe change a child rectangle
	RECT *pChildRect = m_MetaTable.pFrmRect;

	if(!pChildRect) {
		_M("CChildFrame: Empty a child rectangle!");
		return FALSE;
	}

	//*** Sizes of the child frame
	int nChildLeft = pChildRect->left;
	int nChildTop = pChildRect->top;
	int nChildWidth = pChildRect->right - pChildRect->left;
	int nChildHeight = pChildRect->bottom - pChildRect->top;

	//*** Changes size and locality of child frame

	if(nChildWidth > nMainWidth) {
		cs.x = 0;
		cs.cx = nMainWidth;
	} else {
		if(nChildLeft > nMainWidth - nChildWidth) {
			cs.x = nMainWidth - nChildWidth;
			cs.cx = nChildWidth;
		} else {
			cs.x = nChildLeft;
			cs.cx = nChildWidth;
		}
	}

	if(nChildHeight > nMainHeight) {
		cs.y = 0;
		cs.cy = nMainHeight;
	} else if(nChildTop > nMainHeight - nChildHeight) {
		cs.y = nMainHeight - nChildHeight;
		cs.cy = nChildHeight;
	} else {
		cs.y = nChildTop;
		cs.cy = nChildHeight;
	}

	//return CMDIChildWnd::PreCreateWindow(cs);
	return TRUE;
}  // PreCreateWindow
/*
/////////////////////////////////////////////////////////////////////////////
// OnCreate
/////////////////////////////////////////////////////////////////////////////
int CChildFrame::OnCreate(LPCREATESTRUCT pCS) {
	if(CMDIChildWnd::OnCreate(pCS) == -1)
			return -1;

	return 0;
}  // OnCreate
*/
/////////////////////////////////////////////////////////////////////////////
// OnSize
/////////////////////////////////////////////////////////////////////////////
void CChildFrame::OnSize(UINT nType, int cx, int cy) {
	CMDIChildWnd::OnSize(nType, cx, cy);

	//*** Common offset for child frames
	int m_nChildFrmOffset = m_pMainApp->m_nChildFrmOffset;

	//*** Common width of main frame for border
	UINT m_nMainFrmBorders = m_pMainApp->m_nMainFrmBorders;

	//*** Current table pointer
	m_pTable = m_pMainApp->m_apTable[m_eTable];

	if(!m_pTable) {
		_M("CChildFrame: Empty a CListCtrlEx object!");
		return;
	}
	
	//*** Offset & Border size
	cx = cx - m_nMainFrmBorders + m_nChildFrmOffset;
	cy = cy - m_nMainFrmBorders + m_nChildFrmOffset;

	//*** Uses suitable sizes
	RECT Rect = {m_nChildFrmOffset, m_nChildFrmOffset, cx, cy};
	
	//*** Changes a window sizes
	m_pTable->MoveWindow(&Rect);

	//*** Shows the vertical scroll bar always
	m_pTable->ShowScrollBar(SB_VERT);
}  // OnSize

/////////////////////////////////////////////////////////////////////////////
// OnChildActivate
/////////////////////////////////////////////////////////////////////////////
void CChildFrame::OnChildActivate() {
	CMDIChildWnd::OnChildActivate();

	//*** Saves current table Id in the main application
	m_pMainApp->m_eTable = m_eTable;

	//*** Updates tabs
	m_pMainFrame->m_MainTabs.Update();
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////////////////
	// AssertValid
	/////////////////////////////////////////////////////////////////////////////
	void CChildFrame::AssertValid() const {
		CMDIChildWnd::AssertValid();
	}  // AssertValid

	/////////////////////////////////////////////////////////////////////////////
	// Dump
	/////////////////////////////////////////////////////////////////////////////
	void CChildFrame::Dump(CDumpContext &dc) const {
		CMDIChildWnd::Dump(dc);
	}  // Dump
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
