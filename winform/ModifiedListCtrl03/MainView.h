/////////////////////////////////////////////////////////////////////////////
// MainView.h : interface of the CMainView class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#include "ListCtrlEx\ListCtrlEx.h"
	#include "ListCtrlEx\HeaderCtrlEx.h"

	/////////////////////////////////////////////////////////////////////////////
	// Class CMainView
	/////////////////////////////////////////////////////////////////////////////
	class CMainView : public CFormView {
		DECLARE_DYNCREATE(CMainView)

		protected:  // Create from serialization only
			CMainView();

		public:
			//*** Main application pointer
			CMainApp *m_pMainApp;

			//*** Table Id
			ETABLE m_eTable;

			//*** The meta table structure
			META_TABLE m_MetaTable;

		public:
			//{{AFX_DATA(CMainView)
			enum{ IDD = IDD_MAIN_FORM };
				// NOTE: the ClassWizard will add data members here
			//}}AFX_DATA
		
		// Attributes
		public:
			//CMainDoc *GetDocument();

		// Operations
		public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMainView)
		public:
			//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		
		protected:
			//virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
			virtual void OnInitialUpdate();  // Called first time after construct
		//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CMainView();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
		#endif

		// Generated message map functions
		protected:
			//{{AFX_MSG(CMainView)
			afx_msg int OnCreate(LPCREATESTRUCT pCS);
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};  // class CMainView : public CFormView
	/*
	#ifndef _DEBUG  // debug version in MainView.cpp
		inline CMainDoc* CMainView::GetDocument()
			 {return (CMainDoc *) m_pDocument;}
	#endif
	*/
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
