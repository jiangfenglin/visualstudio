/////////////////////////////////////////////////////////////////////////////
// StdAfx.h : include file for standard system include files
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

	#include <afxwin.h>         // MFC core and standard components
	#include <afxext.h>         // MFC extensions
	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls

	#ifndef _AFX_NO_AFXCMN_SUPPORT
		#include <afxcmn.h>			// MFC support for Windows Common Controls
	#endif  // _AFX_NO_AFXCMN_SUPPORT

	//*** For CMainTabs class
	#include <AFXPRIV.H>
	#include <vector>
	#include <algorithm>

	#define MAXITEMTEXT			256  // The maximum text length

	//*** The meta table header structure
	typedef struct {
			TCHAR *szHdrName;  // Column name
			//TCHAR *szFormat;  // Table list data format
			DWORD nAdjust;  // Text formating
			UINT nWidth;  // Column width
	} META_HEADER;

	//*** The meta table structure
	typedef struct {
			TCHAR *szTblName;  // Table name
			DWORD dwStyle;  // Table style
			DWORD dwExStyle;  // Extended table style
			RECT *pFrmRect;  // Frame rectangle pointer
			RECT *pViewRect;  // View rectangle pointer
			CFont *pHdrFont;  // Table header font pointer
			CFont *pListFont;  // Table list font pointer
			UINT nHdrHeight;  // Table header height
			UINT nListHeight;  // Table list height
			UINT nColCount;  // Table header columns count
			UINT nRowCount;  // Table list row count
			TCHAR **apRowText;  // Table rows text array
			META_HEADER *apMetaHeader;  // Meta table header pointer
	} META_TABLE;

	void _M(int nVal);  // Shows a number
	void _M(CString sStr);  // Shows a CString
	void _M(TCHAR *szStr);  // Shows a Unicode line
	//void _M(wchar_t *szStr);  // Shows a Unicode line

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
