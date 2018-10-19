
/* =====[ MxPad.h ]=========================================================

   Description:

            Interface for MX debug pad.

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  03/09/99  Peter Glen    Initial version.
	  0.00  11/08/05  Peter Glen    Network Version

   ======================================================================= */

#ifndef mxpad_defined
#define mxpad_defined

#ifndef SO_DONTLINGER
#include "winsock2.h"
#endif

#include <afxmt.h>

#pragma comment(lib, "ws2_32.lib")

//////////////////////////////////////////////////////////////////////////

#define CIRC_DEF_SIZE	40960

#define APPNAME "MxPad"
#define mxMBOX(aa)  MessageBox(NULL, aa, "", MB_OK)

#define	MXDUMPLEN	32000
#define	MXOUTLEN	32000

//define	OUTLEN	32		// for testing

#define CHUNK 16

//////////////////////////////////////////////////////////////////////////
// Defines for simplification:

#ifdef _DEBUG

#define P2N		mxpad.printf
#define D2N		mxpad.dump
#define C2N		mxpad.ClearNotepad()

#define AP2N	mxpad.aprintf

//////////////////////////////////////////////////////////////////////////
// Shorthands for misc variables:

#define P2N_RECT(var)											\
	P2N("%s  left=%d top=%d right=%d bottom=%d\r\n", #var,		\
			var.left, var.top, var.right, var.bottom);			\

#define P2N_INT(var)											\
	P2N("%s%d\r\n", #var, var);

//////////////////////////////////////////////////////////////////////////
// Flag macros:

#define P2NLOCAL(flag)	mxpad.local=flag;
#define P2NREMOTE(flag)	mxpad.remote=flag;

#else

#define P2N		
#define D2N	
#define C2N	
#define AP2N
#define P2N_RECT
#define P2N_INT
#define P2NLOCAL
#define P2NREMOTE
#endif

/* Messages we return if there was no error or we didn't have it in our list. */


/// \brief Prints like printf to the debug pad application (%MxPad)
///
/// This little class acts just like TRACE, except it prints to 
/// the Mxpad application.
///
/// Use: mxpad.printf("printf compatible string\r\n", var1, var2 ... ); \n
/// \n
/// Example: mxpad.printf("Hello int var=%d\r\n", var); \n
/// \n
/// The header will automatically define an instance of 'mxpad'\n
/// \n
/// <b>The following defines are available to lessen typing: </b>\n
/// \n
///	P2N -- PrintF to MXPAD ... example P2N("Hello int var=%d\r\n", var); \n 
///	D2N -- Dump (hexdump) to MXPAD ... example C2N(ptr, len); \n 
///	C2N	-- Clear MXPAD ... example C2N(); \n
/// \n
///	AP2N -- Asyncronous output to MXPAD ... example AP2N("Hello int var=%d\r\n", var); \n
// \n
/// A2PN print(f) to memory buffer, and output from a separate thread\n
/// Fast!

#define  MX_RES_PORT	2000
#define  MX_CONN_PORT	2001
#define  MX_DATA_PORT	2002

class MxPad

{
	typedef struct _ERROR_STRUCT 
		{
		int err;
		char *str;
		}	ERROR_STRUCT ;


	static	ERROR_STRUCT MxPad::errlist[];
	static	char msg_no_error[];
	static	char msg_unknown_error[];


	static  HWND    child;
	static	SOCKADDR_IN rec_sin2;
	
	static  HWND    GetChild(HWND  hwndParent);
	static	BOOL	CALLBACK EnumChildProc(HWND  hwnd, LPARAM  lParam);

	static	DWORD	AcceptThreadProc(DWORD *ptp);
	static	void	RunMxThread(void *lpParam);

	static int	constructed;

public:

	CString ascstr;

	// Set this to true if you want release mode debugging
	int force;		
	
/// Support class for %MxPad

/// This class implements a circular buffer for the %MxPad class

class CxCircular  

{

public:

	int IsEmpty();
	int Add(char chh);
	int Get(char *chh);

	CxCircular();
	CxCircular(int bufsize);

	virtual ~CxCircular();

protected:

	int head, tail, size;
	char	*buff;

	CCriticalSection lock;

	int InitVars();
};

protected:

	int		remote, local, trace, handle;

	//char    *szOutString;
	//char	*aszOutString;
	//char	*dump_str;
	
	char    szOutString[MXOUTLEN];
	char	aszOutString[MXOUTLEN];
	char	dump_str[MXDUMPLEN];
	
public:
	int Version();

	MxPad();
	~MxPad();

	int		endthread;

	CxCircular circ;

	void	SetLocal(int flag);
	void	SetRemote(int flag);
	void	ClearNotepad();

	///	Will output to TRACE instead of %Mxpad
	int		SetTrace(int flag);
	
	char	*vkey2keystr(int code);

	void	Detect();

	// See if any agent is running (local, remote)	
	int IsLocalAvail();
	int IsRemoteAvail();

#ifdef CWnd

	// Dump WINDOW Styles
	void DumpExStyles(CWnd *ptr);
	void DumpStyles(CWnd *ptr);	
	void DumpSS(CWnd *ptr);
	void DumpEdS(CWnd *ptr); 

#endif

	// Translate WINDOWs errors to strings
	char *werr2str(int err);

	/// Handle/Convert UNICODE strings
	DWORD   UnicodeToAnsi(LPWSTR pszW, LPSTR* ppszA);
	DWORD   AnsiToUnicode(LPCSTR pszA, LPWSTR* ppszW);

	/// Just like hexdump, but prints to debug pad
	int     dump(const void *mem, int len);

	/// Just like print, but prints to debug pad
	int     printf(const char *Format, ...);

	/// Async version
	int     aprintf(const char *Format, ...);

	/// Convert numeric message number to readable message
	char    *num2msg(int msg);

	/// Convert numeric error number to readable message
	char    *num2err(int msg);

	// Socket error to string
	char *sockerr2str(int err);

	/// Return TRUE if message is a non-client message
	int     is_nonclient(int msg);

	/// Return TRUE if message is async junc (mouse move etc ...)
	int     is_junk(int msg);

	/// Set Output Application Window name
	void	SetAppname(const char *str);


protected:

	/// Actual output done here
	int     ToNotepad(const char  *str);

	// Connectivity related 
	SOCKADDR_IN     dest_sin, local_sin;	

	// Socket decriptors	
	SOCKET			sock, sock2;
	int				acc_sin_len;    /* Accept socket address length */
	SOCKADDR		acc_sin;		/* Accept socket address */
	
	int nd, ndlen, connected, resolved; 

	int			Resolve();
	int			Connect();

	//CString		appname;

	char	appname[255];

};

#ifdef _DEBUG
extern MxPad	mxpad;
#endif


#endif // mxpad_defined

// EOF


