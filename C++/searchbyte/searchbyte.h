// searchbyte.h : main header file for the SEARCHBYTE application
//

#if !defined(AFX_SEARCHBYTE_H__3BB169E3_1026_4069_AA03_C4D9824160AA__INCLUDED_)
#define AFX_SEARCHBYTE_H__3BB169E3_1026_4069_AA03_C4D9824160AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSearchbyteApp:
// See searchbyte.cpp for the implementation of this class
//

class CSearchbyteApp : public CWinApp
{
public:
	CSearchbyteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchbyteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSearchbyteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHBYTE_H__3BB169E3_1026_4069_AA03_C4D9824160AA__INCLUDED_)
