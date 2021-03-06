// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ClientLogic.h"

#include "client_base.h"

#define WM_SHOWTASK (WM_USER + 1986)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(ClientLogic *pClientLogic,CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	m_strMessage = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClientLogic = pClientLogic;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Control(pDX, IDC_MESSAGELIST_EDIT, m_MessageList);
	DDX_Text(pDX, IDC_MESSAGE_EDIT, m_strMessage);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CClientDlg::OnBnClickedSendButton)
	ON_MESSAGE(WM_SHOWTASK, &CClientDlg::OnNotifyIcon)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CClientDlg::OnBnClickedCloseButton)
	ON_COMMAND(ID_FILE_EXIT, &CClientDlg::OnFileExit)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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

	ShowWindow(SW_NORMAL);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MESSAGE_EDIT);
	pEdit->SetFocus();

	// TODO: Add extra initialization here

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else 
	if(nID==SC_CLOSE) 
	{
		ToTray();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CClientDlg::OnBnClickedSendButton()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_strMessage == "")
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MESSAGE_EDIT);
		pEdit->SetFocus();
		return;
	}

	m_pClientLogic->SendChatMessage(m_strMessage);

	/*SendMessagePkt pkt;

	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString str = theApp.m_strName + _T("   ") + t + _T("\r\n") + _T("   ") + m_strMessage;
	char buf[1024] = {0};
	WideCharToMultiByte(CP_UTF8, 0, str, str.GetLength(), pkt.message, sizeof(pkt.message), 0, 0);
	pkt.len = (int)strlen(pkt.message)+1;
	m_pSocket->Send((char *)&pkt,sizeof(SendMessagePkt));*/

	m_strMessage = "";
	UpdateData(FALSE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MESSAGE_EDIT);
	pEdit->SetFocus();
}

BOOL CClientDlg::GetMessage(uint64 iAvatarId, TCHAR* strMessage)
{
	std::vector< std::pair<uint64, CString> >::iterator it = m_AvatarList.begin();
	while (it != m_AvatarList.end())
	{
		if ((*it).first == iAvatarId)
		{
			break;
		}

		++it;
	}

	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString chatMessage = (*it).second + _T("   ") + t + _T("\r\n") + _T("   ") + strMessage;
	chatMessage += _T("\r\n");
	m_MessageList.SetSel(-1);
	m_MessageList.ReplaceSel(chatMessage);

	if (!IsIconic())
	{
		nid.uFlags = NIF_INFO | NIF_ICON | NIF_TIP | NIF_MESSAGE;
		wcscpy_s(nid.szTip, sizeof(nid.szTip)/sizeof(TCHAR), TEXT("Fantuan"));
		if (wcslen(chatMessage) < sizeof(nid.szInfo)/sizeof(TCHAR))
		{
			wcscpy_s(nid.szInfo, sizeof(nid.szInfo)/sizeof(TCHAR), chatMessage);
		}
		
		wcscpy_s(nid.szInfoTitle, sizeof(nid.szInfoTitle)/sizeof(TCHAR), _T("Fantuan Chat"));
		nid.uTimeout = 2000;
		nid.dwState=NIS_SHAREDICON;
		nid.dwStateMask=0;
		nid.dwInfoFlags=NIF_TIP;
		Shell_NotifyIcon(NIM_MODIFY, &nid);
	}
	else
	{
		FlashWindow(TRUE);
	}
	
	return TRUE;
}

void CClientDlg::UpdateUser(uint64 iAvatarId, TCHAR* strAvatarName)
{
	m_AvatarList.push_back( std::pair<uint64, CString>(iAvatarId, strAvatarName) );

	m_UserList.ResetContent();
	for(int j=0; j<int(m_AvatarList.size()); j++)
	{
		m_UserList.AddString(m_AvatarList.at(j).second);
	}
}

void CClientDlg::DeleteUser(uint64 iAvatarId)
{
	std::vector< std::pair<uint64, CString> >::iterator it = m_AvatarList.begin();
	while (it != m_AvatarList.end())
	{
		if ((*it).first == iAvatarId)
		{
			m_AvatarList.erase(it);
			break;
		}

		++it;
	}

	m_UserList.ResetContent();
	for(int j=0; j<int(m_AvatarList.size()); j++)
	{
		m_UserList.AddString(m_AvatarList.at(j).second);
	}
}

void CClientDlg::ToTray()
{
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nid.dwInfoFlags = NIF_INFO;
	nid.uTimeout=2000; 
	wcscpy_s(nid.szTip, sizeof(nid.szTip) / sizeof(TCHAR), _T("Fantuan"));  
	wcscpy_s(nid.szInfo, sizeof(nid.szTip) / sizeof(TCHAR), _T("See you later"));  
	wcscpy_s(nid.szInfoTitle, sizeof(nid.szInfoTitle) / sizeof(TCHAR), _T("Fantuan Chat"));  

	wcscpy_s(nid.szTip, sizeof(nid.szTip) / sizeof(TCHAR), _T("Fantuan notification"));

	Shell_NotifyIcon(NIM_ADD,&nid);
	ShowWindow(SW_HIDE);
}

LRESULT CClientDlg::OnNotifyIcon(WPARAM wParam,LPARAM lParam)    
{         
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{    
	case WM_RBUTTONUP:
		{ 
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);
			CMenu menu; 
			menu.CreatePopupMenu();
			
			menu.AppendMenu(MF_STRING,WM_DESTROY,_T("Close")); 
			
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
			
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); 
			delete lpoint; 
		} 
		break; 
	case WM_LBUTTONDOWN:
		{ 
			Shell_NotifyIcon(NIM_DELETE,&nid);
			this->ShowWindow(SW_SHOW);
		} 
		break; 
	} 
	return 0; 

}

BOOL CClientDlg::PreTranslateMessage(MSG*   pMsg)
{
	if(pMsg->message==WM_KEYDOWN) 
	{ 
		if(pMsg->wParam == VK_RETURN)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				CString strTemp = m_strMessage;
				strTemp += _T("\r\n");
				CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MESSAGE_EDIT);
				pEdit->ReplaceSel(strTemp);
			}
			else
			{
				OnBnClickedSendButton();
			}
			return TRUE;
		}
	} 

	return   CDialog::PreTranslateMessage(pMsg); 
}

void CClientDlg::OnBnClickedCloseButton()
{
	// TODO: Add your control notification handler code here
	m_UserList.ResetContent();
	m_AvatarList.clear();
	m_pClientLogic->Logout();
}

void CClientDlg::OnFileExit()
{
	// TODO: Add your command handler code here
	exit(0);
}
