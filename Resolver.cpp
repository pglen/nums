// Resolver.cpp: implementation of the CResolver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cam.h"
#include "Resolver.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResolver::CResolver(HWND hWnd)
{
	init_socket(hWnd);
}


CResolver::~CResolver()
{

}

//////////////////////////////////////////////////////////////////////////
// Init networking layer.
//

int     CResolver::init_socket(HWND hWnd)

{
    int ret_val = 0, sin_len = sizeof(gl_sin);

    sock = socket( AF_INET, SOCK_DGRAM, 0);

	if(sock == INVALID_SOCKET)
		{
		TRACE("MxPad: Cannot create socket\r\n");
		}
    

    #ifdef PG_DEBUG
    //TRACE("MxPad: Socket: %d\r\n", sock);
    #endif

    local_sin.sin_addr.s_addr = INADDR_ANY;
    local_sin.sin_port = htons((short)conf.broadcastport);
    local_sin.sin_family = AF_INET;

    if (bind( sock, (struct sockaddr FAR *) &local_sin, sizeof(local_sin))
							== SOCKET_ERROR)
        {
        #ifdef PG_DEBUG
        TRACE("MxPad: Cannot Bind socket\r\n");
        #endif
		ret_val = 1;
        }

    //TRACE("Bind OK\n");

    // Signal interest in reading data:
    ret_val = WSAAsyncSelect(sock, hWnd, WM_MSG1, FD_READ);

    if(ret_val)
        {
        #ifdef PG_DEBUG
        TRACE("MxPad: Cannot async socket\r\n");
        #endif
		ret_val = 1;
        }

    // ----------------------------------------------------------------
    sock2 = socket( AF_INET, SOCK_STREAM, 0);

	if(sock2 == INVALID_SOCKET)
		{
		TRACE("MxPad: Cannot create socket2\r\n");
		ret_val = 1;
		}
    #ifdef PG_DEBUG
    //TRACE("MxPad: Socket2: %d\r\n", sock);
    #endif

    local2_sin.sin_addr.s_addr = INADDR_ANY;
    local2_sin.sin_port = htons((short)conf.dataport);
    local2_sin.sin_family = AF_INET;

    if (bind(sock2, (struct sockaddr FAR *)&local2_sin, sizeof(local2_sin))<0)
        {
        #ifdef PG_DEBUG
        TRACE("MxPad: Cannot Bind socket2\r\n");
        #endif
		ret_val = 1;
        }

    // Signal interest in connect:

    ret_val = WSAAsyncSelect(sock2, hWnd, WM_MSG2,
                                        FD_ACCEPT | FD_READ | FD_CLOSE);

    if(ret_val)
        {
        #ifdef PG_DEBUG
        TRACE("MxPad: Cannot async socket2\r\n");
        #endif
        }

    if (listen( sock2, 4) < 0)
        {
        #ifdef PG_DEBUG
        TRACE("MxPad: Cannot listen.\r\n");
        #endif
		ret_val = 1;
        }

    // ----------------------------------------------------------------

//    enabled = 1; started = 1;
//    date_time(datestr, sizeof(datestr));
//    TRACE("Licence server online %s ... O.K.\n", datestr);

    return(ret_val);
}