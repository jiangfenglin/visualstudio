/////////////////////////////////////////////////////////////////////////////
// Main.h : main header file for the MAIN application
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAIN_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAIN_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#ifndef __AFXWIN_H__
		#error include 'stdafx.h' before including this file for PCH
	#endif

	#include "ListCtrlEx\ListCtrlEx.h"
	#include "Resource.h"  // Main symbols

	class CMainFrame;
	class CChildFrame;
	
	/////////////////////////////////////////////////////////////////////////////
	// ETABLE - Insert new Ids between e_NULL and e_MAX
	/////////////////////////////////////////////////////////////////////////////
	enum ETABLE {
		e_NULL = E_NULL,  // Empty Form Index
		e_First = E_FIRST,
		e_Second = E_SECOND,
		e_Third = E_THIRD,
		e_MAX = E_MAX
	}; 
	
	/////////////////////////////////////////////////////////////////////////////
	// CMainApp: See Main.cpp for the implementation of this class
	/////////////////////////////////////////////////////////////////////////////
	class CMainApp : public CWinApp {
		public:
			CMainApp();

			//*** Saves the CMultiDocTemplate class pointer
			CMultiDocTemplate *m_pDocTemplate;

			//*** Common height of main frame tollbar, tab and status line
			UINT m_nClientCtrlsHeight;

			//*** Common width of main frame for border
			UINT m_nMainFrmBorders;

			//*** Common offset for child frames
			int m_nChildFrmOffset;

			//*** Table Id
			ETABLE m_eTable;

			//*** Table pointers array
			CListCtrlEx *m_apTable[e_MAX];

			//*** Main frame pointer
			CMainFrame *m_pMainFrame;

			//*** Child frame pointers array
			CChildFrame *m_apFrame[e_MAX];

			//*** For all tables ***

			//*** Table header font structure
			static LOGFONT m_LogHdrFont;
			//*** Table header font
			CFont m_HdrFont;
			//*** Table list font structure
			static LOGFONT m_LogListFont;
			//*** Table list font
			CFont m_ListFont;
			//*** Meta table structures array
			META_TABLE m_aMetaTable[e_MAX];

			//*** For Table 1 ***

			//*** Table 1 name
			static TCHAR *m_szTblName1;
			//*** Frame 1 rectangle coordinates
			static RECT m_FrmRect1;
			//*** View 1 rectangle coordinates
			static RECT m_ViewRect1;
			//*** Meta table 1 header structure array
			static META_HEADER m_aMetaHeader1[];
			//*** Table 1 rows text array
			static TCHAR *m_apRowText1[];

			//*** For Table 2 ***

			//*** Table 2 name
			static TCHAR *m_szTblName2;
			//*** Frame 2 rectangle coordinates
			static RECT m_FrmRect2;
			//*** View 2 rectangle coordinates
			static RECT m_ViewRect2;
			//*** Meta table 2 header structure array
			static META_HEADER m_aMetaHeader2[];
			//*** Table 2 rows text array
			static TCHAR *m_apRowText2[];
			
			//*** For Table 3 ***

			//*** Table 3 name
			static TCHAR *m_szTblName3;
			//*** Frame 3 rectangle coordinates
			static RECT m_FrmRect3;
			//*** View 3 rectangle coordinates
			static RECT m_ViewRect3;
			//*** Meta table 3 header structure array
			static META_HEADER m_aMetaHeader3[];
			//*** Table 3 rows text array
			static TCHAR *m_apRowText3[];
			
			
		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMainApp)
		public:
			virtual BOOL InitInstance();
			//virtual int ExitInstance();
		//}}AFX_VIRTUAL

		// Implementation
		//{{AFX_MSG(CMainApp)
		//afx_msg void OnFileNew();
		afx_msg void OnTable(UINT eTable);
		afx_msg void OnAppAbout();
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAIN_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
