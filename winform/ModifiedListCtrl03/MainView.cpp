/////////////////////////////////////////////////////////////////////////////
// MainView.cpp : implementation of the CMainView class
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Main.h"
#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainView
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMainView, CFormView)

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	//{{AFX_MSG_MAP(CMainView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView construction
/////////////////////////////////////////////////////////////////////////////
CMainView::CMainView() : CFormView(CMainView::IDD) {
	//*** Main application pointer
	m_pMainApp = reinterpret_cast<CMainApp *>(AfxGetApp());

	if(!m_pMainApp) {
		_M("CMainView: Empty object of the CMainApp class!");
		return;
	}

	//*** Table Id
	m_eTable = m_pMainApp->m_eTable;

	//*** The meta table structure
	m_MetaTable = m_pMainApp->m_aMetaTable[m_eTable];
}

/////////////////////////////////////////////////////////////////////////////
// CMainView destruction
/////////////////////////////////////////////////////////////////////////////
CMainView::~CMainView() {
}

/////////////////////////////////////////////////////////////////////////////
// OnInitialUpdate
/////////////////////////////////////////////////////////////////////////////
void CMainView::OnInitialUpdate() {
	CFormView::OnInitialUpdate();

	//*** Don't set the Size to {0} else the debug version of the program 
	// will be wrong!
	SIZE Size = {1, 1};

	//*** Turns off scroll bars of the Form
	SetScaleToFitSize(Size);

}  // OnInitialUpdate

/////////////////////////////////////////////////////////////////////////////
// OnCreate
/////////////////////////////////////////////////////////////////////////////
int CMainView::OnCreate(LPCREATESTRUCT pCS) {
	if(CFormView::OnCreate(pCS) == -1) {
		_M("CMainView: Failed to call CFormView::OnCreate function!");

		return -1;
	}

	//*** Creates table
	CListCtrlEx *pTable = new CListCtrlEx;
	
	if(!pTable) {
		_M("CMainView: Empty a CListCtrlEx object!");
		return -1;
	}

	//*** CListCtrlEx initialization
	if(!pTable->Create(m_MetaTable.dwStyle, *m_MetaTable.pViewRect, this, m_eTable)) {
		_M("Failed to create a CListCtrlEx object!");
		return - 1;
	}

	//*** Sets extended table style
	pTable->SetExtendedStyle(m_MetaTable.dwExStyle);

	//*** Creates a table header
	CHeaderCtrlEx *pHeader = new CHeaderCtrlEx;
	
	if(!pHeader) {
		_M("Empty CHeaderCtrlEx object!");
		return -1;
	}
	
	//*** The CHeaderCtrlEx handle
	HWND hHeader = pHeader->m_hWnd;
	//HWND hHeader = pHeader->GetSafeHwnd();

	CHeaderCtrl *pOldHeader = pTable->GetHeaderCtrl();

	if(!pOldHeader) {
		_M("Empty CHeaderCtrl object!");
		return -1;
	}
	
	//*** The CHeaderCtrl handle
	HWND hOldHeader = pOldHeader->m_hWnd; 
	//HWND hOldHeader = pOldHeader->GetSafeHwnd();

	//*** The table header subclassing
	if(!pHeader->SubclassWindow(hOldHeader)) {
		_M("Failed to Subclass a table header!");
		return -1;
	}

	//*** The structure of a table header cell
	HDITEM HDItem = {0};

	HDItem.mask |= HDI_FORMAT;  // The fmt member is valid
	HDItem.mask |= HDI_TEXT;  // The pszText and cchTextMax members are valid
	HDItem.mask |= HDI_WIDTH;  // The cxy member is valid and specifies the item's width

	HDItem.cchTextMax = MAXITEMTEXT;

	META_HEADER *apMetaHeader = m_MetaTable.apMetaHeader;

	//*** Creates table columns
	for(UINT i = 0; i < m_MetaTable.nColCount; i++) {
		HDItem.pszText = (LPTSTR) apMetaHeader[i].szHdrName;
		HDItem.fmt = apMetaHeader[i].nAdjust;
		HDItem.cxy = apMetaHeader[i].nWidth;
		
		//*** Calls CHeaderCtrlEx::DrawItem
		HDItem.fmt |= HDF_OWNERDRAW;

		//*** Sends too message HDM_LAYOUT
		pTable->InsertColumn(
				i, 
				HDItem.pszText,	
				HDItem.fmt, 
				HDItem.cxy
		);
	
		//*** Reset the first column
		if(i == 0)
				pHeader->SetItem(i, &HDItem);
	}

	//*** Sets the table rows count in the virtual mode (LVS_OWNERDATA)
	//*** Send messages LVN_GETDISPINFOW & HDM_LAYOUT
	//*** Calls the CListCtrlEx::DrawItem
	pTable->SetItemCount(2*m_MetaTable.nRowCount);  // REALLY MUST BE m_MetaTable.nRowCount

	//*** Shows the vertical scroll bar always
	pTable->ShowScrollBar(SB_VERT);

	//*** Saves the current CListCtrlEx object
	m_pMainApp->m_apTable[m_eTable] = pTable;

	return 0;
}  // OnCreate

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////////////////
	// AssertValid
	/////////////////////////////////////////////////////////////////////////////
	void CMainView::AssertValid() const {
		CFormView::AssertValid();
	}  // AssertValid

	/////////////////////////////////////////////////////////////////////////////
	// Dump
	/////////////////////////////////////////////////////////////////////////////
	void CMainView::Dump(CDumpContext &dc) const {
		CFormView::Dump(dc);
	}  // Dump
	/*
	/////////////////////////////////////////////////////////////////////////////
	// GetDocument : Non-debug version is inline
	/////////////////////////////////////////////////////////////////////////////
	CMainDoc *CMainView::GetDocument() {
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));

		return (CMainDoc *) m_pDocument;
	}  // GetDocument
	*/
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
