/////////////////////////////////////////////////////////////////////////////
// MainFrame.h : interface of the CMainFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#include "Main.h"
	#include "MainTabs.h"

	/////////////////////////////////////////////////////////////////////////////
	// Class CMainFrame
	/////////////////////////////////////////////////////////////////////////////
	class CMainFrame : public CMDIFrameWnd {
		DECLARE_DYNAMIC(CMainFrame)

		public:
			CMainFrame();

		// Attributes
		public:
			//*** Main application pointer
			CMainApp *m_pMainApp;
			
			//*** The main tabs object
			CMainTabs m_MainTabs;

		// Operations
		public:

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CMainFrame)
		public:
			//virtual BOOL PreCreateWindow(CREATESTRUCT &CS);
			//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CMainFrame();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
		#endif

		protected:  // Control bar embedded members
			CStatusBar m_StatusBar;
			CToolBar m_ToolBar;
			CToolBar m_ToolBar2;

		// Generated message map functions
		protected:
			//{{AFX_MSG(CMainFrame)
			afx_msg int OnCreate(LPCREATESTRUCT pCS);
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnDestroy();
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
