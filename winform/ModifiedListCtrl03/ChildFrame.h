/////////////////////////////////////////////////////////////////////////////
// ChildFrame.h : interface of the CChildFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRAME_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_CHILDFRAME_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif  // _MSC_VER > 1000

	#include "Main.h"

	/////////////////////////////////////////////////////////////////////////////
	// Class CChildFrame
	/////////////////////////////////////////////////////////////////////////////
	class CChildFrame : public CMDIChildWnd {
		DECLARE_DYNCREATE(CChildFrame)

		public:
			CChildFrame();

		// Attributes
		public:
			//*** Main application pointer
			CMainApp *m_pMainApp;

			//*** Main frame pointer
			CMainFrame *m_pMainFrame;

			//*** Table Id
			ETABLE m_eTable;

			//*** The meta table structure
			META_TABLE m_MetaTable;

			//*** Current table
			CListCtrlEx *m_pTable;

		// Operations
		public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CChildFrame)
			virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CChildFrame();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
		#endif

		// Generated message map functions
		protected:
			//{{AFX_MSG(CChildFrame)
			//afx_msg int OnCreate(LPCREATESTRUCT pCS);
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnChildActivate();
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_CHILDFRAME_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
