/////////////////////////////////////////////////////////////////////////////
// MainTabs.cpp : implementation of the CMainTabs class
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Resource.h"
#include "MainTabs.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainTabs
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMainTabs, CTabCtrl)

BEGIN_MESSAGE_MAP(CMainTabs, CTabCtrl)
	//{{AFX_MSG_MAP(CMainTabs)
  ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelChange)
  ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainTabs construction
/////////////////////////////////////////////////////////////////////////////
CMainTabs::CMainTabs() {
	//*** Height of tabs
	m_nHeight = 21;  // See CMainApp::m_nClientCtrlsHeight

	//*** Tab vertical offset
	m_nVertOffset = 2;

	//*** Tab horizontal offset
	m_nHorzOffset = 2;

	//*** Handle of Client
	m_hClient = NULL;
}  // CMainTabs

/////////////////////////////////////////////////////////////////////////////
// CMainTabs destruction
/////////////////////////////////////////////////////////////////////////////
CMainTabs::~CMainTabs() {
}  // ~CMainTabs

/////////////////////////////////////////////////////////////////////////////
// Create
/////////////////////////////////////////////////////////////////////////////
void CMainTabs::Create(CFrameWnd *pMainFrame) {
  //*** Creates the CTabCtrl object
	CTabCtrl::Create(
			TCS_BUTTONS,
			CRect(0, 0, 0, 0),
			pMainFrame,
			ID_MAINTABS
	);
  
	//*** Changes of tab sizes
	SetItemSize(CSize(0, m_nHeight));

	//*** Changes of tab extension style
	ModifyStyleEx(0, WS_EX_OVERLAPPEDWINDOW);

  //*** Sets current tab font
	SendMessage(WM_SETFONT, WPARAM(GetStockObject(DEFAULT_GUI_FONT)), 0);

  //*** Seeks m_hClient for using in Update function
	m_hClient = ::GetTopWindow(*pMainFrame);

	//*** Creates the status bar
	if(!m_hClient) {
		_M("CMainTabs: Failed to get a client window!");
	}
}  // Create

/////////////////////////////////////////////////////////////////////////////
// OnSelChange
/////////////////////////////////////////////////////////////////////////////
void CMainTabs::OnSelChange(NMHDR *pNMHDR, LRESULT *pResult) {
  TCITEM Item;

  Item.mask = TCIF_PARAM;

  GetItem(GetCurSel(), &Item);

	HWND hWnd = HWND(Item.lParam);

  ::BringWindowToTop(hWnd);

  *pResult = 0;
}  // OnSelChange

/////////////////////////////////////////////////////////////////////////////
// OnSizeParent
/////////////////////////////////////////////////////////////////////////////
afx_msg LRESULT CMainTabs::OnSizeParent(WPARAM, LPARAM lParam) {
  AFX_SIZEPARENTPARAMS *pParams = reinterpret_cast<AFX_SIZEPARENTPARAMS *>(lParam);

	//*** Client rectangle
  RECT *pCR = &pParams->rect;
	
	//*** Tab width
  UINT nWidth = pCR->right - pCR->left;

  pCR->left -= m_nHorzOffset;
	pCR->bottom -= m_nHeight;

  MoveWindow(
			pCR->left,
			pCR->bottom - m_nVertOffset,
			nWidth + m_nHorzOffset,
			m_nHeight + m_nVertOffset
	);

  ShowWindow(SW_NORMAL);
  
  return 0;
}  // OnSizeParent

/////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////
void CMainTabs::Update() {
  SetRedraw(false);

  //*** Get active view window (actually the frame of the view)
	HWND active = ::GetTopWindow(m_hClient);

  typedef std::vector<HWND> TWndVec;
  typedef TWndVec::iterator TWndIter;

  //*** Put all child windows in a list (actually a vector)
	TWndVec vChild;
  
	for(HWND child = active; child; child = ::GetNextWindow(child, GW_HWNDNEXT)) {
    vChild.push_back(child);
  }

  TCHAR text[MAXITEMTEXT];
  TCITEM item;

  item.pszText = text;
  int i = 0;
	for(i = GetItemCount(); i--;) {  // For each tab
    item.mask = TCIF_PARAM;
    GetItem(i, &item);

    TWndIter it = std::find(vChild.begin(), vChild.end(), HWND(item.lParam));

    if(it == vChild.end()) {  // Associatete view does no longer exist, so delete the tab
      DeleteItem(i);
    } else {  // Update the tab's text, image and selection state
      item.mask = TCIF_TEXT;
      ::GetWindowText(*it, text, MAXITEMTEXT);

			SetItem(i, &item);
      
			if(*it == active)
					SetCurSel(i);  // Associated view is active => make it the current selection
      
			vChild.erase(it);  // Remove view from list
    }
  }

  //*** All remaining views in vChild have to be added as new tabs
  i = GetItemCount();

  for(TWndIter it = vChild.begin(), end = vChild.end(); it != end; ++it) {
    item.mask = TCIF_TEXT|TCIF_PARAM|TCIF_IMAGE;
    ::GetWindowText(*it, text, MAXITEMTEXT);
  
		item.iImage = i;
    item.lParam = LPARAM(*it);
    InsertItem(i, &item);
    
		if(*it == active)
				SetCurSel(i);
    
		++i;
  }

  static_cast<CMDIFrameWnd *>(FromHandlePermanent(::GetParent(m_hClient)))->RecalcLayout();

  RedrawWindow(NULL, NULL, RDW_FRAME|RDW_INVALIDATE|RDW_ERASE);

  SetRedraw(true);
}  // Update

/////////////////////////////////////////////////////////////////////////////
// CMainTabs diagnostics
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////////////////
	// AssertValid
	/////////////////////////////////////////////////////////////////////////////
	void CMainTabs::AssertValid() const {
		CTabCtrl::AssertValid();
	}  // AssertValid

	/////////////////////////////////////////////////////////////////////////////
	// Dump
	/////////////////////////////////////////////////////////////////////////////
	void CMainTabs::Dump(CDumpContext &dc) const {
		CTabCtrl::Dump(dc);
	}  // Dump
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
