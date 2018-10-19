// Resolver.h: interface for the CResolver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOLVER_H__03465E5C_D9B1_48AC_B469_102B1120399B__INCLUDED_)
#define AFX_RESOLVER_H__03465E5C_D9B1_48AC_B469_102B1120399B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResolver  
{
public:
	CResolver();
	virtual ~CResolver();

private:
	int		init_socket(CWnd  hWnd);
	CWnd	hWnd;

};

#endif // !defined(AFX_RESOLVER_H__03465E5C_D9B1_48AC_B469_102B1120399B__INCLUDED_)
