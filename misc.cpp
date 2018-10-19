
/* =====[ misc.cpp ]========================================== 
                                                                             
   Description:     The xraynotes project, implementation of the misc.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  6/11/2007  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"

#define COMPILE_MULTIMON_STUBS
#include "multimon.h"

#include "mxpad.h"
#include "misc.h"

#pragma comment(lib, "rpcrt4.lib")

CMisc misc;


long	CMisc::hash_string(const char  *name)

{
    unsigned long    ret_val = 0;

    while(*name != '\0')
        {
        ret_val ^= (long)*name;
        ret_val  = ROTATE_LONG_RIGHT(ret_val, 3);          /* rotate right */
        *name++;
        }
    return((long)ret_val);
}

//////////////////////////////////////////////////////////////////////////
// Return true if a key is down

bool	CMisc::IsCtrlDown()

{
	return ((GetKeyState(VK_CONTROL) & 0x80) != false);
}

bool	CMisc::IsShiftDown()

{
	return ((GetKeyState(VK_SHIFT) & 0x80) != false);
}


bool	CMisc::IsAltDown()

{
	return ((GetKeyState(VK_MENU) & 0x80) != false);
}

void CMisc::CurrentMonRect(POINT pt, RECT *rc)

{
	HMONITOR mon = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi; memset(&mi, 0, sizeof(mi));	mi.cbSize = sizeof(mi);
	
	int ret = GetMonitorInfo(mon, &mi);

	//P2N("GetMonitorInfo ret=%d left=%d right=%d top=%d bottom=%d\r\n", ret, mi.rcMonitor.left, 
	//						mi.rcMonitor.right, mi.rcMonitor.top, mi.rcMonitor.bottom);
	
	// Output results
	rc->left = mi.rcMonitor.left;	
	rc->top = mi.rcMonitor.top;	
	rc->right = mi.rcMonitor.right;	
	rc->bottom = mi.rcMonitor.bottom;	
}

//////////////////////////////////////////////////////////////////////////

CString		CMisc::uuid2str(UUID *id)

{
	CString str;

	unsigned char	*ustr;
	RPC_STATUS ret =  UuidToString(id, &ustr);

	if(ret != RPC_S_OK)
		str = "Insufficent Memory in uuid2str";
	else
		str = ustr;
	RpcStringFree(&ustr);

	return str;
}

//////////////////////////////////////////////////////////////////////////

UUID CMisc::str2uuid(CString &str)

{
	UUID	uid;
	unsigned char *ptr = (unsigned char *)str.GetBuffer(_MAX_PATH);
	RPC_STATUS ret =  UuidFromString(ptr, &uid);
	str.ReleaseBuffer();

	if(ret != RPC_S_OK)
		{
		P2N("CMisc::str2uuid %s RPC_S_INVALID_STRING_UUID\r\n", str);
		}

	return uid;
}

