//

#if !defined(AFX_CAM_H__CEE89614_29C8_4C81_BFFB_4596664D05B3__INCLUDED_)
#define AFX_CAM_H__CEE89614_29C8_4C81_BFFB_4596664D05B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "label.h"

#include "numsdef.h"

class CCamDlg: public CDialog
{
public:

	CCamDlg(CWnd* pParent=NULL);
	void DoDataExchange(CDataExchange* pDX);

	void	CCamDlg::SetDisp(const char *text);

	HICON	m_hIcon;
	int m_created;
	int m_nWidth, m_nHeight;

	CBitmap m_bitmap;

	void CCamDlg::SetScroller(const char *text);

	CString m_scroller, m_org;
	int m_prog, m_scrolltresh;

	CLabel m_num1;
	CLabel m_num2;
	CLabel m_num3;
	CLabel m_num4;
	CLabel m_num5;
	CLabel m_num6;
	CLabel m_num7;
	CLabel m_num8;
	CLabel m_num9;
	CLabel m_num10;
	CLabel m_status;

	SOCKET m_socket;

protected:
	void CCamDlg::ReSize(int cx, int cy);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamApp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Dialog Data
	//{{AFX_DATA(CMsgBox)
	enum { IDD = IDD_CAM_DIALOG};
	
	//}}AFX_DATA

	// Generated message map functions
	//{{AFX_MSG(CCamDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif
