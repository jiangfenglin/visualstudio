/////////////////////////////////////////////////////////////////////////////
// StdAfx.cpp : source file that includes just the standard includes
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if defined(_UNICODE)
	#pragma comment(linker, "/entry:wWinMainCRTStartup")
#endif  // _UNICODE

/////////////////////////////////////////////////////////////////////////////
// _M - Shows an int nVal with AfxMessageBox
/////////////////////////////////////////////////////////////////////////////
void _M(int nVal) {
	TCHAR szVal[MAXITEMTEXT];

	swprintf(szVal, _T("%d"), nVal);
	AfxMessageBox(szVal);
}

/////////////////////////////////////////////////////////////////////////////
// _M - Shows an CString sStr with AfxMessageBox
/////////////////////////////////////////////////////////////////////////////
void _M(CString sStr) {
	TCHAR szVal[MAXITEMTEXT];

	swprintf(szVal, _T("%s"), sStr);
	AfxMessageBox(szVal);
}

/////////////////////////////////////////////////////////////////////////////
// _M - Shows an TCHAR *szStr with AfxMessageBox
/////////////////////////////////////////////////////////////////////////////
void _M(TCHAR *szStr) {
	TCHAR szVal[MAXITEMTEXT];

	swprintf(szVal, _T("%s"), szStr);
	AfxMessageBox(szVal);
}
/*
/////////////////////////////////////////////////////////////////////////////
// _M - Shows an wchar_t *szStr with AfxMessageBox
/////////////////////////////////////////////////////////////////////////////
void _M(wchar_t *szStr) {
	TCHAR szVal[MAXITEMTEXT];

	swprintf(szVal, _T("%s"), szStr);
	AfxMessageBox(szVal);
}
*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
