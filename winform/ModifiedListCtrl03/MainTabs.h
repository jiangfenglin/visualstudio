/////////////////////////////////////////////////////////////////////////////
// MainTabs.h : interface of the CMainTabs class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINTABS_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINTABS_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	/////////////////////////////////////////////////////////////////////////////
	// MainTabs.h : interface of the CMainTabs class
	/////////////////////////////////////////////////////////////////////////////
	class CMainTabs : public CTabCtrl {
		DECLARE_DYNCREATE(CMainTabs)

		public:
			CMainTabs();

		// Attributes
		public:
			//*** Height of tabs
			UINT m_nHeight;

			//*** Tab vertical offset
			UINT m_nVertOffset;

			//*** Tab horizontal offset
			UINT m_nHorzOffset;

			//*** Handle of Client
			HWND m_hClient;

		// Operations
		public:
			void Create(CFrameWnd *pMainFrame);
			void Update();  // Sync the tab control with all views

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CMainTabs)
			public:
			//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CMainTabs();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext &dc) const;
		#endif

		protected:

		// Generated message map functions
		protected:
			//{{AFX_MSG(CMainTabs)
			afx_msg void OnSelChange(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg LRESULT OnSizeParent(WPARAM, LPARAM lParam);
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINTABS_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
