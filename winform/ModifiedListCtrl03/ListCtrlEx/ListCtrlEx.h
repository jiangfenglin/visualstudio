/////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER >= 1000
		#pragma once
	#endif // _MSC_VER >= 1000

	//#include "..\Main.h"

	/////////////////////////////////////////////////////////////////////////////
	// class CListCtrlEx
	/////////////////////////////////////////////////////////////////////////////
	class CListCtrlEx : public CListCtrl {
		// Construction
		public:
			CListCtrlEx();
			
			//*** The meta yable structure
			META_TABLE m_MetaTable;

		// Operations
		public:

		// Overrides
		public:

		protected:
			virtual void SetColItemText(CDC *pDC, CString &sCellText, CRect &TextRect, 
					UINT nJustify);
			virtual void SetRowText(LPDRAWITEMSTRUCT pDIS);

			virtual void DrawItem(LPDRAWITEMSTRUCT pDIS);

		protected:
			virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, 
					LRESULT *pLResult);

		// Implementation
		public:
			virtual ~CListCtrlEx();

		// Generated message map functions
		protected:
			afx_msg void MeasureItem(LPMEASUREITEMSTRUCT pMIS);

		DECLARE_MESSAGE_MAP()
	};
#endif // !defined(AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
