// searchbyteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "searchbyte.h"
#include "searchbyteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define MULTI_SEARCH
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
// CSearchbyteDlg dialog

CSearchbyteDlg::CSearchbyteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchbyteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchbyteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchbyteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchbyteDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchbyteDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchbyteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchbyteDlg message handlers

BOOL CSearchbyteDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSearchbyteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSearchbyteDlg::OnPaint() 
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
HCURSOR CSearchbyteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//#define MULTI_SEARCH

void CSearchbyteDlg::OnOK() 
{
	//BYTE chkbyte[4] = {0x01, 0x34, 0xDF, 0x0A};
	//F6.B5.0A.00
	//BYTE chkbyte[] = {0xF6, 0xB5, 0x0A, 0x00};
	//BYTE chkbyte[] = {0xF5, 0x36, 0x03, 0x00};
	//BYTE chkbyte[] = {0x16, 0x52, 0x7E, 0x3D};
	//3D76F448
	//BYTE chkbyte[] = {0x37, 0x2D, 0x0C, 0x00};
	//BYTE chkbyte[] = {0xF9, 0xB9, 0x2C, 0xB8, 0x5C, 0xD5};
#ifndef MULTI_SEARCH
//	BYTE chkbyte[] = {0xD1, 0xC9, 0x11, 0xC9, 0x20, 0x00, 0x8C, 0xD6, 0x3C, 0xD5};//집중 회피(unicode)
	//BYTE chkbyte[] = {0xD7, 0xF3, 0x06, 0x00};
	//BYTE chkbyte[] = {0x14, 0xD5, 0x83, 0x70};
	BYTE chkbyte[] = {"Potion"};
	//BYTE chkbyte[] = {0xC1, 0xFD, 0xC1, 0xDF, 0x20, 0xC8, 0xB8, 0xC7, 0xC7};//집중 회피(ansi)
#else
	BYTE chkbyte[3][4] = {
		{0x72, 0x1D, 0xD9, 0x44},
		{0x2A, 0x14, 0xD0, 0x44},
		{0x6F, 0xED, 0x79, 0x43}
	};
#endif
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	HANDLE hFile1 = CreateFile(
		"C:\\txt.txt", 
		GENERIC_WRITE,
		FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	hFind = FindFirstFile("D:\\diablo_dump\\*.DAT", &FindFileData);
	BOOL Bresult = TRUE;
	while(Bresult)
	{
		if(stricmp(FindFileData.cFileName, ".") == 0 ||
			stricmp(FindFileData.cFileName, "..") == 0){
			FindNextFile(hFind, &FindFileData);
			continue;
		}
		char szPath[256];
		sprintf(szPath, "D:\\diablo_dump\\%s", FindFileData.cFileName);
		HANDLE hFile = CreateFile(
			szPath, 
			GENERIC_READ,
			FILE_SHARE_READ, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
		DWORD hsize, lsize;
		lsize = GetFileSize(hFile, &hsize);
		char* pszbuffer = (char*)malloc(lsize);
		ReadFile(hFile, pszbuffer, lsize, &lsize, NULL);
		int i;
		int j = 0;
#ifdef MULTI_SEARCH
		if(lsize)
			for(j = 0; j < 3; j++){
				for(i = 0; i < (int)lsize - 14; i++)
					if(memcmp(pszbuffer + i, chkbyte[j], 4) == 0)
					{					
						break;
					}
				int a = 0;
 				if(i == lsize - 14)
					break;
			}
		if(j == 3)
		{
			WriteFile(hFile1, FindFileData.cFileName, strlen(FindFileData.cFileName), &hsize, NULL);
			WriteFile(hFile1, "\r\n", 2, &hsize, NULL);
		}
#else
		if(lsize)
			for(i = 0; i < (int)lsize - 14; i++)
				if(memcmp(pszbuffer + i, chkbyte, sizeof(chkbyte)) == 0)
				//if(wcsicmp((PWCHAR)(pszbuffer + i), (PWCHAR)chkbyte) == 0)
				{					
					WriteFile(hFile1, FindFileData.cFileName, strlen(FindFileData.cFileName), &hsize, NULL);
					WriteFile(hFile1, "\r\n", 2, &hsize, NULL);
					break;
				}
#endif
		free(pszbuffer);
		CloseHandle(hFile);
		Bresult = FindNextFile(hFind, &FindFileData);
		
	}
	CloseHandle(hFile1);
	MessageBox("OK!", "", MB_OK);
}
