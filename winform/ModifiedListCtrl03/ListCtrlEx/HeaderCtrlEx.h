/////////////////////////////////////////////////////////////////////////////
// HeaderCtrlEx.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERCTRLEX_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_HEADERCTRLEX_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif  // _MSC_VER > 1000
	
	#include "..\Main.h"

	/////////////////////////////////////////////////////////////////////////////
	// class CHeaderCtrlEx
	/////////////////////////////////////////////////////////////////////////////
	class CHeaderCtrlEx : public CHeaderCtrl {
		// Construction
		public:
			CHeaderCtrlEx();

		// Attributes
		public:
			//*** The meta table structure
			META_TABLE m_MetaTable;

			//*** The width of defect of displacement of the table header to the left
			UINT m_nHdrWidthDefect;

			//*** The height of defect of the table header
			UINT m_nHdrHeightDefect;

		protected:

		// Operations
		public:

		// Overrides
		public:

		// Implementation
		public:
			virtual ~CHeaderCtrlEx();

		protected:
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

		// Generated message map functions
		protected:
			afx_msg LRESULT OnLayout(WPARAM wparam, LPARAM lparam);

		DECLARE_MESSAGE_MAP()
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HEADERCTRLEX_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
