////////////////////////////////////////////////////////////////////////////
// HeaderCtrlEx.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "HeaderCtrlEx.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MESSAGE MAP
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx
/////////////////////////////////////////////////////////////////////////////
CHeaderCtrlEx::CHeaderCtrlEx() {
	//*** Main Application Pointer
	CMainApp *pMainApp = reinterpret_cast<CMainApp *>(AfxGetApp());

	if(!pMainApp) {
		_M("CHeaderCtrlEx: Empty object of the CMainApp class!");
		return;
	}

	//*** Table Id
	ETABLE eTable = pMainApp->m_eTable;

	//*** The Meta Table Structure
	m_MetaTable = pMainApp->m_aMetaTable[eTable];

	//*** The width of defect of displacement of the table header to the left
	m_nHdrWidthDefect = 1;

	//*** The height of defect of the table header
	m_nHdrHeightDefect = 2;
}  // CHeaderCtrlEx

/////////////////////////////////////////////////////////////////////////////
// ~CHeaderCtrlEx
/////////////////////////////////////////////////////////////////////////////
CHeaderCtrlEx::~CHeaderCtrlEx() {
}  // ~CHeaderCtrlEx

///////////////////////////////////////////////////////////////////////////////
// OnLayout
///////////////////////////////////////////////////////////////////////////////
LRESULT CHeaderCtrlEx::OnLayout(WPARAM, LPARAM lParam) {
	LPHDLAYOUT pHL = reinterpret_cast<LPHDLAYOUT>(lParam);
	
	//*** The table list rectangle
	RECT *pRect = pHL->prc;

	//*** The table header rectangle
	WINDOWPOS *pWPos = pHL->pwpos;

	//*** Here's equivalent code for the code which follows after
	/*
	pWPos->hwndInsertAfter = NULL;

	//*** Moves the table header to the righ
	pWPos->x = pRect->left + m_nHdrWidthDefect;
	pWPos->y = pRect->top;
	pWPos->cx = pRect->right - pRect->left;

	//*** New table header height
	pWPos->cy = m_nHdrHeight + m_nHdrHeightDefect;

	pWPos->flags = SWP_NOACTIVATE|SWP_NOZORDER;

	//*** Decreases the table list height on the table header height
	pRect->top += m_nHdrHeight;

	return TRUE;
	*/
	//***
	
	//*** Sends HDM_LAYOUT message to the base class
	int nRet = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

	//*** Moves the table header to the right
	pWPos->x += m_nHdrWidthDefect;

	// Table header height
	UINT nHdrHeight = m_MetaTable.nHdrHeight;

	//*** New table header height
	pWPos->cy = nHdrHeight + m_nHdrHeightDefect;

	//*** Decreases the table list height on the table header height
	pRect->top = nHdrHeight;

	return nRet;
}  // OnLayout

/////////////////////////////////////////////////////////////////////////////
// DrawItem
/////////////////////////////////////////////////////////////////////////////
void CHeaderCtrlEx::DrawItem(LPDRAWITEMSTRUCT pDIS) {
	HDITEM hDI;
	TCHAR szBuf[MAXITEMTEXT];

	hDI.mask = HDI_TEXT;
	hDI.pszText = szBuf;
	hDI.cchTextMax = MAXITEMTEXT;

	GetItem(pDIS->itemID, &hDI);

	CDC *pDC;
	HDC hDC = pDIS->hDC;  // Handle to device context
	pDC = CDC::FromHandle(hDC);

	//*** Selects necessary font
	pDC->SelectObject(m_MetaTable.pHdrFont);
	//pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

	int x = 0;  // x-coordinate of reference point
	int y = 0;  // y-coordinate of reference point
	UINT nOptions = 0;  // Text-output options ETO_CLIPPED|ETO_OPAQUE
	RECT *pIRect = NULL;  // Optional clipping and/or opaquing rectangle

	pIRect = &pDIS->rcItem;
	SIZE Size = {0};

	//*** Gets the header cell sizes
	if(!GetTextExtentPoint(hDC, szBuf, wcslen(szBuf), &Size)) {
		_M("Failed to call GetTextExtentPoint for table header!");
		return;
	}

	//*** x-coordinate of reference point
	x = (pIRect->left + pIRect->right - Size.cx)/2 - 1;
	x = (x < pIRect->left + 2) ? pIRect->left + 2 : x;

	//*** y-coordinate of reference point
	y = (pIRect->bottom - pIRect->top - Size.cy)/2 - 1;
	
	//*** Specifies that text is clipped to the rectangle pIRect
	nOptions |= ETO_CLIPPED;

	//*** Specifies that the current background color fills the rectangle pIRect
	nOptions |= ETO_OPAQUE;

	//*** Decreases the text border to the right
	pIRect->right -= 4;

	//*** Writes the text in the (x, y) - coordinates
	pDC->ExtTextOut(x, y, nOptions, pIRect, szBuf, wcslen(szBuf), NULL);

	//*** Restores system font
	pDC->SelectStockObject(SYSTEM_FONT);
}  // DrawItem

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
