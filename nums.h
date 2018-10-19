// cam.h : main header file for the CAM application
//

#if !defined(AFX_CAM_H__CEE89614_29C8_4C81_BFFB_4596664D05B4__INCLUDED_)
#define AFX_CAM_H__CEE89614_29C8_4C81_BFFB_4596664D05B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCamApp:
// See cam.cpp for the implementation of this class
//

class CCamApp : public CWinApp
{
public:
	CCamApp();

	void PlaySnd();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCamApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAM_H__CEE89614_29C8_4C81_BFFB_4596664D05B4__INCLUDED_)
