/////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ListCtrlEx.h"

#include "..\MainView.h"

/////////////////////////////////////////////////////////////////////////////
// MESSAGE MAP
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_MEASUREITEM_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::CListCtrlEx() {
	//*** Main Application Pointer
	CMainApp *pMainApp = reinterpret_cast<CMainApp *>(AfxGetApp());

	if(!pMainApp) {
		_M("CListCtrlEx: Empty object of the CMainApp class!");
		return;
	}

	//*** Table Id
	ETABLE eTable = pMainApp->m_eTable;

	//*** The Meta Table Structure
	m_MetaTable = pMainApp->m_aMetaTable[eTable];
}  // CListCtrlEx

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::~CListCtrlEx() {
}  // ~CListCtrlEx

/////////////////////////////////////////////////////////////////////////////
// MeasureItem
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT pMIS) {
	//*** The table list height
	pMIS->itemHeight = m_MetaTable.nListHeight;
}  // MeasureItem

/////////////////////////////////////////////////////////////////////////////
// OnChildNotify
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult) {
	NMHDR *pNMHdr = reinterpret_cast<NMHDR *>(lParam);

	LV_DISPINFO *pLVDI = reinterpret_cast<LV_DISPINFO *>(lParam);
	LV_ITEM *pItem = &pLVDI->item;

	if(message == WM_NOTIFY) {
		switch(pNMHdr->code) {
			case LVN_GETDISPINFO: {
				if(pItem->mask & LVIF_TEXT) {
					UINT nRow = pItem->iItem;
					UINT nCol = pItem->iSubItem;

					UINT nColCount = m_MetaTable.nColCount;
					UINT nRowCount = m_MetaTable.nRowCount;
					UINT i = nRow*nColCount + nCol;

					if(i < 0) {
						_M("CListCtrlEx::OnChildNotify : Index i < 0!");
						return FALSE;
					}

					if(i < nColCount*nRowCount) {
						wcscpy((wchar_t *)(pItem->pszText), m_MetaTable.apRowText[i]);
					} else {
						wcscpy((wchar_t *)(pItem->pszText), _T("***"));
					}
				}

				break;
			}
		}
	}

	return CListCtrl::OnChildNotify(message, wParam, lParam, pResult);
}  // OnChildNotify

/////////////////////////////////////////////////////////////////////////////
// SetColItemText
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SetColItemText(CDC *pDC, CString& stColText, 
			CRect& TextRect, UINT nJustify) {
	int x = 0;  // x-coordinate of reference point
	int y = 0;  // y-coordinate of reference point
	UINT nOptions = 0;  // Text-output options ETO_CLIPPED|ETO_OPAQUE

	int nTextLen = stColText.GetLength();
	HDC hDC = pDC->m_hDC;
	SIZE Size = {0};

	if(!GetTextExtentPoint(hDC, stColText, nTextLen, &Size)) {
		_M("Failed to call GetTextExtentPoint for table list!");
		return;
	}

	//*** Align the text in the whole table
	CRect TmpRect(TextRect);

	//*** x-coordinate of reference point
	x = (TextRect.left + TextRect.right - Size.cx)/2 - 1;
	x = (x < TextRect.left + 2) ? TextRect.left + 2 : x;

	//*** y-coordinate of reference point
	y = (TextRect.bottom - TextRect.top - Size.cy)/2 - 1;
	
	//*** Specifies that the current background color fills the rectangle
	nOptions |= ETO_OPAQUE;

	//*** Draw the background fast
	pDC->ExtTextOut(TextRect.left, TextRect.top, nOptions, TextRect, NULL, 0, NULL);

	TmpRect.left++;  // Cosmetic
	TmpRect.top += y;	 // y-coordinate of reference point
	TmpRect.InflateRect(-3, 0);	 // Text does not touch borders
	
	UINT nFormat = 0;

	switch(nJustify & LVCFMT_JUSTIFYMASK) {
		case LVCFMT_LEFT:
			nFormat = DT_LEFT;
			break;
		case LVCFMT_RIGHT:
			nFormat = DT_RIGHT;
			break;
		case LVCFMT_CENTER:
			nFormat = DT_CENTER;
			break;
		default:
			_M("CListCtrlEx: Error of the text formatting!");
			return;
	}

	//*** Writes the text in the TmpRect
	::DrawText(hDC, stColText, nTextLen, TmpRect, nFormat);
}  // SetColItemText

/////////////////////////////////////////////////////////////////////////////
// SetRowText
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SetRowText(LPDRAWITEMSTRUCT pDIS) {
	CString sItemText;

	//*** Retrieve the item rectangle size. 
	CRect TextRect = pDIS->rcItem;

	//*** You should get the pointer to the device context from the "pDIS" ptr.
	CDC *pDC = CDC::FromHandle(pDIS->hDC);
	
	//*** Selects necessary font
	pDC->SelectObject(m_MetaTable.pListFont);

	UINT nColumn = 0;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;

	while(nColumn < m_MetaTable.nColCount && GetColumn(nColumn, &lvc)) {
		//*** Get the text to be drawn and calculate its bounding rectangle
		sItemText = GetItemText(pDIS->itemID, nColumn);
		TextRect.right = TextRect.left + GetColumnWidth(nColumn);

		if(pDC->RectVisible(TextRect))
				SetColItemText(pDC, sItemText, TextRect, lvc.fmt);

		//*** Move the left side of the previous rect already forward to be good
		// for the next Text. The right of the previous bounding rect is the
		// left of the following
		TextRect.left = TextRect.right;
		
		nColumn++;
	}

	//*** Back to the old state
	pDIS->rcItem.right = TextRect.right;
	pDIS->rcItem.bottom = TextRect.bottom;

	//*** Restore system font
	pDC->SelectStockObject(SYSTEM_FONT);
}  // SetRowText

/////////////////////////////////////////////////////////////////////////////
// DrawItem
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT pDIS) {
	if(pDIS->itemID == -1)
			return;

	//*** You should get the pointer to the device context from the "pDIS" ptr.
	CDC *pDC = CDC::FromHandle(pDIS->hDC);

	switch(pDIS->itemAction) {	
		case ODA_DRAWENTIRE: {
			//*** Populate the listview with column text
			SetRowText(pDIS);
			break;
		} 
		default: {
			TCHAR szStr[MAXITEMTEXT];

			swprintf(
					szStr, 
					_T("CGridListEx::DrawItem : Unexpected case in switch : %i"),
					pDIS->itemAction
					);

			_M(szStr);
		}
	}
}  // DrawItem

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
