
/* =====[ numcli.c ]======================================================

    MAIN description.

        
    Revisions:

      REV     DATE		    BY            DESCRIPTION
      ----  -----------	   ----------    ----------------------------------
      0.00  jul/28/2015    Peter Glen    Initial version.

*/

// numcliDlg.cpp : implementation file
//

#include "stdafx.h"
#include "numcli.h"
#include "numcliDlg.h"
#include "myedit.h"

//#include "mxpad.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "../numsdef.h"


// This global contains the resolved serve address
SOCKADDR_IN		rec_sin2;
int rec_sin_len = sizeof(rec_sin2);
    
/*
 * Only one of these will run, no access control needed.
 */

DWORD	AcceptThreadProc( DWORD *ptp )

{
    SOCKET sock2, sock3;
	
    char	nd  = 1;
	int		ndlen  = sizeof(char);
    int     ret_val;

    // -------------------------------------------------------------------
    // Listen for server answer back:

    sock2 = socket( AF_INET, SOCK_STREAM, 0);
    //TRACE("After sock2.\n");

    ret_val = setsockopt (sock2, SOL_SOCKET, SO_DONTLINGER, &nd, sizeof(int));    
    //ret_val = getsockopt (sock2, SOL_SOCKET, SO_DONTLINGER, &nd, &ndlen);
    
    SOCKADDR_IN rec_sin;
	rec_sin.sin_addr.s_addr = INADDR_ANY;
    rec_sin.sin_port = htons(CAM_NAME_PORT);
    rec_sin.sin_family = AF_INET;

    if (bind( sock2, (struct sockaddr FAR *) &rec_sin, sizeof(rec_sin))
        == SOCKET_ERROR)
        {
    	TRACE(":AcceptThreadProc -- Cannot Bind socket\r\n");
		}

    if (listen( sock2, 1) < 0)
        {
        TRACE(":AcceptThreadProc Cannot listen on socket2\r\n");
        }
   
	memset(&rec_sin2, 0, sizeof(rec_sin2));

    rec_sin_len = sizeof(rec_sin2);
    sock3 = accept( sock2,(struct sockaddr FAR *) &rec_sin2,
            (int FAR *) &rec_sin_len );

    char *str = inet_ntoa( *((struct in_addr*) &rec_sin2.sin_addr.s_addr));
	TRACE("Got name from server %s\n", str);

    closesocket(sock3); closesocket(sock2);
    
    *ptp = 1;
    return(333); 
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CnumcliDlg dialog

CnumcliDlg::CnumcliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CnumcliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CnumcliDlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_resolved = 0;

}

void CnumcliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CnumcliDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//DDX_Control
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CnumcliDlg, CDialog)
	//{{AFX_MSG_MAP(CnumcliDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CnumcliDlg message handlers

BOOL CnumcliDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


		// TODO: Add extra initialization here
	WORD wVersionRequested;   WSADATA wsaData;
	int	err;

	wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );

    if ( err != 0 )
        {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        AfxMessageBox ("Cannot initialize Windows Socket, networking functions will not be available.");
        //return;
        }

    //P2N("Winsock Ver %d.%d %s \r\n", HIBYTE(wsaData.wVersion), LOBYTE(wsaData.wVersion), wsaData.szDescription);
    //Exception();

	//P2N("Started cli\n");
	TRACE("numCLI");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CnumcliDlg::OnSysCommand(UINT nID, LPARAM lParam)

{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CnumcliDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CnumcliDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CnumcliDlg::SendStr(const char *str)

{
	SOCKADDR_IN     dest_sin;                 /* Local socket - internet style */

	char nd = 1;
	int ret_val;
	//AfxMessageBox(m_edit1);	

	Resolve();

	if (!m_resolved)
	{
		AfxMessageBox("Cannot resolve num server");
		return;
	}

	SOCKET sock2 = socket(AF_INET, SOCK_STREAM, 0);
    //TRACE("After sock2.\n");

    ret_val = setsockopt (sock2, SOL_SOCKET, SO_REUSEADDR, &nd, sizeof(int));
    //TRACE("After sockoption ret_val=%d\r\n", ret_val);
    
	//ret_val = getsockopt (sock2, SOL_SOCKET, SO_REUSEADDR, &nd, &ndlen);    
	//TRACE("After getsockoption ret_val=%d ---  nd=%d\r\n", ret_val, nd);

	memset(&dest_sin, 0, sizeof(dest_sin));

	dest_sin.sin_family = AF_INET;
	dest_sin.sin_port = htons(CAM_DATA_PORT);

	//dest_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	dest_sin.sin_addr.s_addr = rec_sin2.sin_addr.s_addr;
	
	if (connect(sock2, (PSOCKADDR) &dest_sin, sizeof(dest_sin)) < 0)
		{
		TRACE("Cannot connect\r\n");
		
		//P2N("Cannot connect\n");
		AfxMessageBox("Cannot connect to num display");
		return;
		}

	if(send(sock2, str, strlen(str), 0) < 0)
		{
		AfxMessageBox("Cannot send");
		//P2N("Cannot send\n");
		}

	closesocket(sock2);

}

void CnumcliDlg::OnButton1() 
{

	UpdateData();	
	SendStr("1 " + m_edit1);
	
}

void CnumcliDlg::OnButton2() 
{
	UpdateData();	
	SendStr("2 " + m_edit2);	
}

void CnumcliDlg::OnButton3() 
{
	UpdateData();	
	SendStr("3 " + m_edit3);	
}

void CnumcliDlg::OnButton4() 
{
	UpdateData();	
	SendStr("4 " + m_edit4);
	
}

//////////////////////////////////////////////////////////////////////////

int		CnumcliDlg::Resolve()

{
	char	bc  = 1;
	int		bclen  = sizeof(char);
	int     res2 = 0;
	unsigned int     tme;
	unsigned long     res;
	
	if(m_resolved)
		return m_resolved;

	SOCKET sock = socket( AF_INET, SOCK_DGRAM, 0);
	//TRACE("After sock %d\n",sock);

	int ret_val = setsockopt (sock, SOL_SOCKET, SO_BROADCAST, &bc, sizeof(int));
	//TRACE("After sockoption %d\n", ret_val);

	//ret_val = getsockopt (sock, SOL_SOCKET, SO_BROADCAST, &bc, &bclen);
	//TRACE("After getsockoption %d ---  %d\n", ret_val, bc);

	CreateThread(NULL, 0, 
			(LPTHREAD_START_ROUTINE) AcceptThreadProc, &res2, 0, &res);

	SOCKADDR_IN local_sin;

	local_sin.sin_addr.s_addr = INADDR_BROADCAST;
	local_sin.sin_port = htons(CAM_BCAST_PORT);
	local_sin.sin_family = AF_INET;
	int acc_sin_len = sizeof(local_sin);

	ret_val = sendto(sock, "num", 3, 0, (struct sockaddr *)&local_sin, acc_sin_len);
	//TRACE("After sendto %d \n", ret_val);

	tme = GetTickCount() + 1000;

	while(1)
		{
		MSG  msg;

		if(tme < GetTickCount())		// Timeout
			break;

		if(res2)                        // Done
			break;

		// Let windows do its thing ...

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
			TranslateMessage(&msg), DispatchMessage(&msg);
			}
		}

	if(res2)
		{
		// Address in rec_sin2
		m_resolved = true;
		}
	return m_resolved;
}

void CnumcliDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	TRACE("change\n");
	char linex[128];
	CMyEdit *ed = (CMyEdit*)GetDlgItem(IDC_EDIT1);
	ASSERT(ed);
	memset(linex, sizeof(linex), 0);
	ed->GetWindowText(linex, sizeof(linex));
	TRACE(linex);
	TRACE("\nend change\n");
	
}

void CnumcliDlg::OnButton5() 
{
	EndDialog(0);	
}

void	CnumcliDlg::OnOK()
{	
	CString str;
	CWnd *ww = GetDlgItem(IDC_EDIT1);
	CWnd *foc = GetFocus();

	if (ww->m_hWnd == *foc)
		{
		ww->GetWindowText(str);
		SendStr("1 " + str);
		}

	ww = GetDlgItem(IDC_EDIT2);
	if (ww->m_hWnd == *foc )
		{
		ww->GetWindowText(str);
		SendStr("2 " + str);
		}

	ww = GetDlgItem(IDC_EDIT3);
	if (ww->m_hWnd == *foc )
		{
		ww->GetWindowText(str);
		SendStr("3 " + str);
		}

	ww = GetDlgItem(IDC_EDIT4);
	if (ww->m_hWnd == *foc )
		{
		ww->GetWindowText(str);
		SendStr("4 " + str);
		}

}