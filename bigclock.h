// bigclock.h : main header file for the BIGCLOCK application
//

#if !defined(AFX_BIGCLOCK_H__257661D0_11B9_464F_BEF9_F79060E5C2EC__INCLUDED_)
#define AFX_BIGCLOCK_H__257661D0_11B9_464F_BEF9_F79060E5C2EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBigclockApp:
// See bigclock.cpp for the implementation of this class
//

class CBigclockApp : public CWinApp
{
public:
	CBigclockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigclockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBigclockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGCLOCK_H__257661D0_11B9_464F_BEF9_F79060E5C2EC__INCLUDED_)
