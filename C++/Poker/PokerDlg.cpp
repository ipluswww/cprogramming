// PokerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poker.h"
#include "PokerDlg.h"
#include <Vfw.h>
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define POKER_WINDOW_TEXT		
#define POKER_CLASS_TEXT		"PokerStarsTableFrameClass"
// CPokerDlg dialog

HWNDSTRUCT hwndstructs[256];
int nCount;

COLORREF crPlayerColor[3][9] = 
{
	{
		RGB(255,219,48) //Yellow
		,RGB(151,255,48) //Green
		,RGB(128,255,255) //Sky
		//,RGB(48,155,255) 
		,RGB(200,200,200) //Gray
		,RGB(78,48,255) //Blue
		,RGB(215,48,255) //Purple
		,RGB(255,62,48) //Red
		,RGB(255,133,25) //Orange
		,RGB(255,255,255) //White
	},
	{
		RGB(255,62,48) //Red
		,RGB(255,219,48) //Yellow
		,RGB(151,255,48) //Green
		,RGB(128,255,255) //Sky
		,RGB(255,133,25) //Orange
		,RGB(255,255,255) //White
	},
	{
		RGB(255,219,48) //Yellow
		,RGB(151,255,48) //Green
		,RGB(128,255,255) //Sky
		//,RGB(48,155,255) 
		,RGB(78,48,255) //Blue
		,RGB(255,133,25) //Orange
		,RGB(255,62,48) //Red
		,RGB(215,48,255) //Purple
		,RGB(200,200,200) //Gray
		,RGB(255,255,255) //White
	}
};

CPokerDlg::CPokerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPokerDlg::IDD, pParent)
	, m_logs(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPokerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOTKEY, m_hotkeyctrl);
	DDX_Control(pDX, IDC_COLORLIST, m_colorlist);
	DDX_Control(pDX, IDC_HWNDLIST, m_hwndlist);
	DDX_Text(pDX, IDC_LOGS, m_logs);
	DDX_Control(pDX, IDC_CMBSITE, m_sitelist);
}

BEGIN_MESSAGE_MAP(CPokerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_COLORLIST, &CPokerDlg::OnNMCustomdrawColorlist)
	ON_BN_CLICKED(IDC_CAPTURECOLOR, &CPokerDlg::OnBnClickedCapturecolor)
	ON_BN_CLICKED(IDCANCEL, &CPokerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CPokerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LAYOUT, &CPokerDlg::OnBnClickedLayout)
	ON_EN_CHANGE(IDC_LABELNAME, &CPokerDlg::OnEnChangeLabelname)
	ON_NOTIFY(NM_CLICK, IDC_COLORLIST, &CPokerDlg::OnNMClickColorlist)
	ON_BN_CLICKED(IDC_CHKBAD, &CPokerDlg::OnBnClickedChkbad)
	ON_BN_CLICKED(IDC_CHKGOOD, &CPokerDlg::OnBnClickedChkgood)
	ON_NOTIFY(NM_DBLCLK, IDC_HWNDLIST, &CPokerDlg::OnNMDblclkHwndlist)
	ON_WM_HOTKEY()
	ON_NOTIFY(NM_RCLICK, IDC_HWNDLIST, &CPokerDlg::OnNMRClickHwndlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_HWNDLIST, &CPokerDlg::OnLvnItemchangedHwndlist)
	ON_CBN_SELCHANGE(IDC_CMBSITE, &CPokerDlg::OnCbnSelchangeCmbsite)
END_MESSAGE_MAP()


// CPokerDlg message handlers

BOOL CPokerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	dwWPTPokerPID = 0;
	dwLAPokerPID = 0;

	SetTimer(100, 1500, NULL);

	DWORD dwThreadID;

	HANDLE hThread = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		TimerThread,          // thread function 
		this,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadID);   // returns the thread identifier

	UpdateData();

	nSiteIndex = 0;

	m_sitelist.AddString("William Hill Poker");
	m_sitelist.AddString("WPT Poker");
	m_sitelist.AddString("Lucky Ace Poker");
	m_sitelist.SetCurSel(0);

	m_hwndlist.SetExtendedStyle(m_hwndlist.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_hwndlist.InsertColumn(0, "Table Name", LVCFMT_LEFT, 194, 194);
	m_hwndlist.InsertColumn(1, "Site", LVCFMT_LEFT, 50, 50);
	m_hwndlist.InsertColumn(2, "Table Type", LVCFMT_LEFT, 65, 65);
	m_hwndlist.InsertColumn(3, "Free Seats", LVCFMT_LEFT, 65, 65);

	m_colorlist.SetExtendedStyle(m_colorlist.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_colorlist.InsertColumn(0, "Label", LVCFMT_LEFT, 100, 100);
	
	LoadSetting();

	for(int i = 0; i < 9; i++)
		m_colorlist.InsertItem(i, playersetting[nSiteIndex][i].szPlayerName);

	if(playersetting[nSiteIndex][0].bBadOrGood)
		((CButton*)GetDlgItem(IDC_CHKBAD))->SetCheck(BST_CHECKED);
	else
		((CButton*)GetDlgItem(IDC_CHKGOOD))->SetCheck(BST_CHECKED);

	if(pokersetting[nSiteIndex].bMoveToSlot)
		((CButton*)GetDlgItem(IDC_CHKMOVEOUT))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bTakeSeat)
		((CButton*)GetDlgItem(IDC_CHKJESUSSEAT))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bEnableSound)
		((CButton*)GetDlgItem(IDC_CHKALERTSOUND))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bShowMessage)
		((CButton*)GetDlgItem(IDC_CHKMESSAGE))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bCloseFilledTable)
		((CButton*)GetDlgItem(IDC_CHKCLOSTTABLE))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bJoinWaitingList)
		((CButton*)GetDlgItem(IDC_CHKJOINWAITINGLIST))->SetCheck(BST_CHECKED);

	m_hotkeyctrl.SetHotKey(pokersetting[nSiteIndex].wHotKey, pokersetting[nSiteIndex].wModifier);

	m_colorlist.RedrawItems(0, m_colorlist.GetItemCount());

	WORD wKeyCode, wModifier;
	m_hotkeyctrl.GetHotKey(wKeyCode, wModifier);
	RegisterHotKey(this->m_hWnd, 0x321, wModifier, wKeyCode);
	//SetTimer(100, 5000, NULL);
	nCount = 0;
	for(int i = 0; i < SITE_COUNT; i++)
		nIndex4Slot[i] = 0;

	
	HRSRC hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ALARM_MP3), "ALARM_MP3");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(AfxGetApp()->m_hInstance, hResource);

		if (hLoadedResource)
		{
			LPVOID pLockedResource = LockResource(hLoadedResource);

			if (pLockedResource)
			{
				DWORD dwResourceSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);

				if (0 != dwResourceSize)
				{
					char szSoundFileName[256];

					GetTempPath(256, szSoundFileName);

					strcat(szSoundFileName, "\\Winning.mp3");
					DWORD dwBytes;
					HANDLE hSoundFile = CreateFile(szSoundFileName, 
						GENERIC_WRITE, 
						FILE_SHARE_WRITE, 
						NULL,
						CREATE_ALWAYS, 
						FILE_ATTRIBUTE_NORMAL, 
						NULL);

					WriteFile(hSoundFile, hLoadedResource, dwResourceSize, &dwBytes, NULL);
					CloseHandle(hSoundFile);
					hwndPlay = MCIWndCreate(this->m_hWnd,  
						AfxGetApp()->m_hInstance,                      
						WS_CHILD | WS_VISIBLE |  // standard styles
						MCIWNDF_NOPLAYBAR |        // hides toolbar 
						MCIWNDF_NOTIFYMODE,        // notifies of mode changes
						szSoundFileName);
					
				}
			}
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPokerDlg::OnPaint()
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
HCURSOR CPokerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPokerDlg::OnNMCustomdrawColorlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		clrNewTextColor = RGB(0,0,0);		//Set the text to red
		clrNewBkColor = crPlayerColor[nSiteIndex][nItem];		//Set the bkgrnd color to blue

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;


		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;


	}
}

void CPokerDlg::OnBnClickedCapturecolor()
{
	CColorDlg colordlg;
	ShowWindow(SW_HIDE);
	
	COLORSETTING tempcolorsetting;
	memcpy(&tempcolorsetting, &colorsetting[nSiteIndex], sizeof(COLORSETTING));
	colordlg.colorsetting = &tempcolorsetting;
	
	colordlg.pplayersetting = &playersetting[nSiteIndex][0];
	colordlg.pcrColor = &crPlayerColor[nSiteIndex][0];
	colordlg.dwWPTPokerPID = dwWPTPokerPID;
	colordlg.dwLAPokerPID = dwLAPokerPID;
	if(nSiteIndex == 0 || nSiteIndex == 2)
		colordlg.nColorCount = 8;
	else
		colordlg.nColorCount = 5;

	if(colordlg.DoModal() == IDOK)
	{
		memcpy(&colorsetting[nSiteIndex], &tempcolorsetting, sizeof(COLORSETTING));
	}
	ShowWindow(SW_SHOW);
}

void CPokerDlg::OnBnClickedCancel()
{
	SaveSetting();

	UnregisterHotKey(this->m_hWnd, 0x321);

	OnCancel();
}

void CPokerDlg::OnBnClickedOk()
{
	ShowWindow(SW_MINIMIZE);
}

void CPokerDlg::OnBnClickedLayout()
{
	CLayoutDlg layoutdlg;
	ShowWindow(SW_HIDE);
	layoutdlg.playoutsetting = &layoutsetting[nSiteIndex];
	layoutdlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CPokerDlg::OnEnChangeLabelname()
{
	int nIndex = m_colorlist.GetNextItem(-1, LVNI_SELECTED);
	GetDlgItem(IDC_LABELNAME)->GetWindowText(playersetting[nSiteIndex][nIndex].szPlayerName, 256);
	m_colorlist.SetItemText(nIndex, 0, playersetting[nSiteIndex][nIndex].szPlayerName);
}

void CPokerDlg::OnNMClickColorlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	char szText[256];
	int nIndex = m_colorlist.GetNextItem(-1, LVNI_SELECTED);
	m_colorlist.GetItemText(nIndex, 0, szText, 256);
	GetDlgItem(IDC_LABELNAME)->SetWindowText(szText);
	if(playersetting[nSiteIndex][nIndex].bBadOrGood)
	{
		((CButton*)GetDlgItem(IDC_CHKBAD))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_CHKGOOD))->SetCheck(BST_UNCHECKED);
	}else
	{
		((CButton*)GetDlgItem(IDC_CHKGOOD))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_CHKBAD))->SetCheck(BST_UNCHECKED);
	}
}

void CPokerDlg::OnBnClickedChkbad()
{
	int nIndex = m_colorlist.GetNextItem(-1, LVNI_SELECTED);
	playersetting[nSiteIndex][nIndex].bBadOrGood = TRUE;
}

void CPokerDlg::OnBnClickedChkgood()
{
	int nIndex = m_colorlist.GetNextItem(-1, LVNI_SELECTED);
	playersetting[nSiteIndex][nIndex].bBadOrGood = FALSE;
}

int CPokerDlg::SaveSetting(void)
{
	char szFileName[256];
	GetModuleFileName(NULL, szFileName, 256);

	char* ptemp = strrchr(szFileName, '\\');
	if(ptemp)
		strcpy(ptemp, "\\Config.dat");

	DWORD dwBytes;
	HANDLE hConfigFile = CreateFile(szFileName, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL,
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if(((CButton*)GetDlgItem(IDC_CHKMOVEOUT))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bMoveToSlot = TRUE;
	else 
		pokersetting[nSiteIndex].bMoveToSlot = FALSE;
	
	if(((CButton*)GetDlgItem(IDC_CHKJESUSSEAT))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bTakeSeat = TRUE;
	else
		pokersetting[nSiteIndex].bTakeSeat = FALSE;
	
	if(((CButton*)GetDlgItem(IDC_CHKALERTSOUND))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bEnableSound = TRUE;
	else
		pokersetting[nSiteIndex].bEnableSound = FALSE;
	
	if(((CButton*)GetDlgItem(IDC_CHKMESSAGE))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bShowMessage = TRUE;
	else
		pokersetting[nSiteIndex].bShowMessage = FALSE;

	if(((CButton*)GetDlgItem(IDC_CHKCLOSTTABLE))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bCloseFilledTable = TRUE;
	else
		pokersetting[nSiteIndex].bCloseFilledTable = FALSE;

	if(((CButton*)GetDlgItem(IDC_CHKJOINWAITINGLIST))->GetCheck() == BST_CHECKED)
		pokersetting[nSiteIndex].bJoinWaitingList = TRUE;
	else
		pokersetting[nSiteIndex].bJoinWaitingList = FALSE;
	
	m_hotkeyctrl.GetHotKey(pokersetting[nSiteIndex].wHotKey, pokersetting[nSiteIndex].wModifier);

	for(int i = 0; i < SITE_COUNT; i++)
	{
		WriteFile(hConfigFile, &layoutsetting[i], sizeof(LAYOUTSETTING), &dwBytes, NULL);
		WriteFile(hConfigFile, &pokersetting[i], sizeof(POKERSETTING), &dwBytes, NULL);
		WriteFile(hConfigFile, &colorsetting[i], sizeof(COLORSETTING), &dwBytes, NULL);
		WriteFile(hConfigFile, &playersetting[i][0], sizeof(PLAYERSETTING) * 9, &dwBytes, NULL);
	}

	CloseHandle(hConfigFile);
	return 0;
}

int CPokerDlg::LoadSetting(void)
{
	char szFileName[256];
	GetModuleFileName(NULL, szFileName, 256);

	char* ptemp = strrchr(szFileName, '\\');
	if(ptemp)
		strcpy(ptemp, "\\Config.dat");

	DWORD dwBytes;
	HANDLE hConfigFile = CreateFile(szFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if(hConfigFile != INVALID_HANDLE_VALUE)
	{
		for(int i = 0; i < SITE_COUNT; i++)
		{
			ReadFile(hConfigFile, &layoutsetting[i], sizeof(LAYOUTSETTING), &dwBytes, NULL);
			ReadFile(hConfigFile, &pokersetting[i], sizeof(POKERSETTING), &dwBytes, NULL);
			ReadFile(hConfigFile, &colorsetting[i], sizeof(COLORSETTING), &dwBytes, NULL);
			ReadFile(hConfigFile, &playersetting[i][0], sizeof(PLAYERSETTING) * 9, &dwBytes, NULL);
		}
	}
	else
	{
		int nSite = 0;
		{
			layoutsetting[nSite].nStackNumber = 1;
			layoutsetting[nSite].observationrect.left = 0;
			layoutsetting[nSite].observationrect.top = 374;
			layoutsetting[nSite].observationrect.right = 494;
			layoutsetting[nSite].observationrect.bottom = 374;

			for(int i = 0; i < 10; i++)
			{
				layoutsetting[nSite].activerect[i].left = 0;
				layoutsetting[nSite].activerect[i].top = 0;
				layoutsetting[nSite].activerect[i].right = 494;
				layoutsetting[nSite].activerect[i].bottom = 374;
			}

			for(int i = 0; i < 8; i++)
			{
				playersetting[nSite][i].bBadOrGood = TRUE;
				sprintf(playersetting[nSite][i].szPlayerName, "Player %d", i);
				//strcpy(playersetting[i].szPlayerName, "");
			}
			playersetting[nSite][8].bBadOrGood = TRUE;
			sprintf(playersetting[nSite][8].szPlayerName, "Unknown Player");

			pokersetting[nSite].bCloseFilledTable = TRUE;
			pokersetting[nSite].bEnableSound = TRUE;
			pokersetting[nSite].bMoveToSlot = TRUE;
			pokersetting[nSite].bShowMessage = TRUE;
			pokersetting[nSite].bTakeSeat = TRUE;
			pokersetting[nSite].wHotKey = 0;
			pokersetting[nSite].wModifier = 0;

			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 12; j++)
					for(int k = 0; k < 9; k++)
						colorsetting[nSite].colorstruct[i].crColors[j][k] = RGB(0,0,0);

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].y = 0;
				}

				colorsetting[nSite].ptJoin.x = 0;
				colorsetting[nSite].ptJoin.y = 0;
			}
		}
		nSite = 1;
		{
			layoutsetting[nSite].nStackNumber = 1;
			layoutsetting[nSite].observationrect.left = 0;
			layoutsetting[nSite].observationrect.top = 355;
			layoutsetting[nSite].observationrect.right = 486;
			layoutsetting[nSite].observationrect.bottom = 355;

			for(int i = 0; i < 10; i++)
			{
				layoutsetting[nSite].activerect[i].left = 0;
				layoutsetting[nSite].activerect[i].top = 0;
				layoutsetting[nSite].activerect[i].right = 486;
				layoutsetting[nSite].activerect[i].bottom = 355;
			}

			for(int i = 0; i < 5; i++)
			{
				playersetting[nSite][i].bBadOrGood = TRUE;
				sprintf(playersetting[nSite][i].szPlayerName, "Player %d", i);
				//strcpy(playersetting[i].szPlayerName, "");
			}
			playersetting[nSite][5].bBadOrGood = TRUE;
			sprintf(playersetting[nSite][5].szPlayerName, "Unknown Player");

			pokersetting[nSite].bCloseFilledTable = TRUE;
			pokersetting[nSite].bEnableSound = TRUE;
			pokersetting[nSite].bMoveToSlot = TRUE;
			pokersetting[nSite].bShowMessage = TRUE;
			pokersetting[nSite].bTakeSeat = TRUE;
			pokersetting[nSite].wHotKey = 0;
			pokersetting[nSite].wModifier = 0;

			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 12; j++)
					for(int k = 0; k < 9; k++)
						colorsetting[nSite].colorstruct[i].crColors[j][k] = RGB(0,0,0);

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].y = 0;
				}

				colorsetting[nSite].ptJoin.x = 0;
				colorsetting[nSite].ptJoin.y = 0;
			}
		}
		nSite = 2;
		{
			layoutsetting[nSite].nStackNumber = 1;
			layoutsetting[nSite].observationrect.left = 0;
			layoutsetting[nSite].observationrect.top = 362;
			layoutsetting[nSite].observationrect.right = 502;
			layoutsetting[nSite].observationrect.bottom = 362;

			for(int i = 0; i < 10; i++)
			{
				layoutsetting[nSite].activerect[i].left = 0;
				layoutsetting[nSite].activerect[i].top = 0;
				layoutsetting[nSite].activerect[i].right = 502;
				layoutsetting[nSite].activerect[i].bottom = 362;
			}

			for(int i = 0; i < 8; i++)
			{
				playersetting[nSite][i].bBadOrGood = TRUE;
				sprintf(playersetting[nSite][i].szPlayerName, "Player %d", i);
			}
			playersetting[nSite][8].bBadOrGood = TRUE;
			sprintf(playersetting[nSite][8].szPlayerName, "Unknown Player");

			pokersetting[nSite].bCloseFilledTable = TRUE;
			pokersetting[nSite].bEnableSound = TRUE;
			pokersetting[nSite].bMoveToSlot = TRUE;
			pokersetting[nSite].bShowMessage = TRUE;
			pokersetting[nSite].bTakeSeat = TRUE;
			pokersetting[nSite].wHotKey = 0;
			pokersetting[nSite].wModifier = 0;

			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 12; j++)
					for(int k = 0; k < 9; k++)
						colorsetting[nSite].colorstruct[i].crColors[j][k] = RGB(0,0,0);

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptSeatPoint[j].y = 0;
				}

				for(int j = 0; j < 9; j++)
				{
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].x = 0;
					colorsetting[nSite].colorstruct[i].ptEmptyPoint[j].y = 0;
				}

				colorsetting[nSite].ptJoin.x = 0;
				colorsetting[nSite].ptJoin.y = 0;
			}
		}
	}

	CloseHandle(hConfigFile);
	return 0;
}

BOOL CALLBACK EnumPokerWindowsProc(
							  HWND hwnd, 
							  LPARAM lParam 
							  )
{
	CPokerDlg* pThis = (CPokerDlg*) lParam;
	char szText[1024];
	DWORD dwPID;

	GetWindowText(hwnd, szText, 1024);

	char szClassName[1024];
	GetClassName(hwnd, szClassName, 1024);

	LONG nStyle = ::GetWindowLong(hwnd, GWL_STYLE);

	if(strcmp(szClassName, "PTIODEVICE") == 0 && 
		strlen(szText) > 0 && 
		nStyle & WS_VISIBLE &&
		(nStyle == 0x16040000) &&
		strcmp(szText, "William Hill Poker") != 0)
	{
		int i;
		BOOL bExist = FALSE;
		for(i = 0; i < nCount; i++)
		{
			if(hwndstructs[i].hwnd == hwnd)
			{
				bExist = TRUE;
			}
		}

		if(bExist == FALSE)
		{
			pThis->AddItem(hwnd, 0);
			return TRUE;
		}
	}

	GetWindowThreadProcessId(hwnd, &dwPID);
	if(dwPID == pThis->dwWPTPokerPID && 
		strncmp(szText, "WPT Poker", strlen("WPT Poker")) != 0 && 
		nStyle == 0x940B0044 && 
		strstr(strupr(szText), "LOADING") == 0 && 
		nStyle & WS_VISIBLE && 
		strlen(szText) > 0)
	{
		int i;
		BOOL bExist = FALSE;
		for(i = 0; i < nCount; i++)
		{
			if(hwndstructs[i].hwnd == hwnd)
			{
				bExist = TRUE;
			}
		}

		if(bExist == FALSE)
		{
			pThis->AddItem(hwnd, 1);
		}
	}

	if(dwPID == pThis->dwLAPokerPID && 
		strncmp(szText, "Lobby", strlen("Lobby")) != 0 && 
		nStyle == 0x96CF004C && 
		strlen(szText) > 0 && 
		szText[strlen(szText) - 3] != ':')
	{
		int i;
		BOOL bExist = FALSE;
		for(i = 0; i < nCount; i++)
		{
			if(hwndstructs[i].hwnd == hwnd)
			{
				bExist = TRUE;
			}
		}

		if(bExist == FALSE)
		{
			pThis->AddItem(hwnd, 2);
		}
	}

	return TRUE;
}

DWORD WINAPI CPokerDlg::TimerThread( LPVOID lpParam ) 
{
	CPokerDlg* pThis = (CPokerDlg*)lpParam;

	while(TRUE)
	{
		if(((CButton*)pThis->GetDlgItem(IDC_CHKAUTOSCAN))->GetCheck() == BST_CHECKED)
			EnumWindows(EnumPokerWindowsProc, (LPARAM)pThis);

		int i;
		for(i = 0; i < nCount; i++)
		{
			DWORD dwProcessId = 0;
			//if(!IsWindow(hwndstructs[i].hwnd))
			GetWindowThreadProcessId(hwndstructs[i].hwnd, &dwProcessId);
			if(dwProcessId == 0)
			{
				pThis->RemoveItem(i--, TRUE);
				continue;
			}

			if(hwndstructs[i].bSeated)
			{
				continue;
			}

			HWNDSTRUCT tempstruct = hwndstructs[i];

			pThis->UpdateItem(hwndstructs[i].hwnd, i);

			if(((CButton*)(pThis->GetDlgItem(IDC_CHKCLOSTTABLE)))->GetCheck() == BST_CHECKED)
			{
				if(hwndstructs[i].nEmptySeat == 0)
				{
					::SendMessage(hwndstructs[i].hwnd, WM_CLOSE, 0, 0);
					pThis->RemoveItem(i--, TRUE);
				}
			}

			if(((CButton*)(pThis->GetDlgItem(IDC_CHKCLOSEEMPTYTABLE)))->GetCheck() == BST_CHECKED)
			{
				if((hwndstructs[i].bTableType == 0 && hwndstructs[i].nEmptySeat == 9) || 
					(hwndstructs[i].bTableType == 1 && hwndstructs[i].nEmptySeat == 6))
				{
					::SendMessage(hwndstructs[i].hwnd, WM_CLOSE, 0, 0);
					pThis->RemoveItem(i--, TRUE);
				}
			}

			if(hwndstructs[i].nEmptySeat > 0)
			{
				int nLimit = hwndstructs[i].bTableType ? 6 : 9;
				BOOL bExit = FALSE;
				for(int j = 1; j < nLimit && !bExit; j++)
					for(int k = 0; k < nLimit && !bExit; k++)
// 						if((hwndstructs[i].nSeat[k] == 1 || (hwndstructs[i].nSeat[k] == 2  && pThis->playersetting[8].bBadOrGood)) && 
// 							hwndstructs[i].nSeat[(k + j) % nLimit] == 3)
						if((hwndstructs[i].nSeat[k] == 1 || (hwndstructs[i].nSeat[k] == 2  && pThis->playersetting[hwndstructs[i].nTableSite][8].bBadOrGood)) && 
							hwndstructs[i].nSeat[(k + j) % nLimit] == 3 && 
							tempstruct.nSeat[k] == 3 && 
							tempstruct.nEmptySeat == hwndstructs[i].nEmptySeat + 1 && 
							hwndstructs[i].bSeated == FALSE)
						{
							if(((CButton*)(pThis->GetDlgItem(IDC_CHKJESUSSEAT)))->GetCheck() == BST_CHECKED)
							{
								if(hwndstructs[i].nTableSite == 0 || hwndstructs[i].nTableSite == 2)
								{
									POINT ptClick = pThis->colorsetting[hwndstructs[i].nTableSite].colorstruct[hwndstructs[i].bTableType? 0 : 1].ptEmptyPoint[(k + j) % nLimit];
									::PostMessage(hwndstructs[i].hwnd, 
										WM_LBUTTONDOWN, 
										MK_LBUTTON, 
										MAKELPARAM(ptClick.x, ptClick.y));
									Sleep(200);
									::PostMessage(hwndstructs[i].hwnd, 
										WM_LBUTTONUP, 
										0, 
										MAKELPARAM(ptClick.x, ptClick.y));
								}
								else if(hwndstructs[i].nTableSite == 1)
								{
									POINT ptClick = pThis->colorsetting[hwndstructs[i].nTableSite].colorstruct[hwndstructs[i].bTableType? 0 : 1].ptEmptyPoint[(k + j) % nLimit];
									HWND hwnd = ::ChildWindowFromPoint(hwndstructs[i].hwnd, ptClick);
									::SendMessage(hwnd, 
										WM_LBUTTONDOWN, 
										MK_LBUTTON, 
										MAKELPARAM(1, 1));
									Sleep(200);
									::SendMessage(hwnd, 
										WM_LBUTTONUP, 
										0, 
										MAKELPARAM(1, 1));
								}
							}

							::MoveWindow(hwndstructs[i].hwnd, 
								pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].left, 
								pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].top, 
								pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].right, 
								pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].bottom, 
								TRUE);

							pThis->nIndex4Slot[hwndstructs[i].nTableSite] = (pThis->nIndex4Slot[hwndstructs[i].nTableSite] + 1) % pThis->layoutsetting[hwndstructs[i].nTableSite].nStackNumber;

							if(((CButton*)(pThis->GetDlgItem(IDC_CHKALERTSOUND)))->GetCheck() == BST_CHECKED)
							{
								MCIWndPlay(pThis->hwndPlay);
							}

							pThis->RemoveItem(i, FALSE);
							bExit = TRUE;
						}
				
			}else
			{
				int nLimit = hwndstructs[i].bTableType ? 6 : 9;
				int j = 0;
				for(j = 0; j < nLimit; j++)
					if((hwndstructs[i].nSeat[j] == 1 || (hwndstructs[i].nSeat[j] == 2 && pThis->playersetting[hwndstructs[i].nTableSite][8].bBadOrGood)) && 
						tempstruct.nSeat[j] == 3 && 
						tempstruct.nEmptySeat == hwndstructs[i].nEmptySeat + 1 && 
						hwndstructs[i].bSeated == FALSE)
						break;

				if(j != nLimit)
				{
					if(((CButton*)(pThis->GetDlgItem(IDC_CHKJOINWAITINGLIST)))->GetCheck() == BST_CHECKED)
					{
						if(hwndstructs[i].nTableSite == 0 || hwndstructs[i].nTableSite == 2)
						{
							POINT ptClick = pThis->colorsetting[hwndstructs[i].nTableSite].ptJoin;
							::PostMessage(hwndstructs[i].hwnd, 
								WM_LBUTTONDOWN, 
								MK_LBUTTON, 
								MAKELPARAM(ptClick.x, ptClick.y));
							Sleep(200);
							::PostMessage(hwndstructs[i].hwnd, 
								WM_LBUTTONUP, 
								0, 
								MAKELPARAM(ptClick.x, ptClick.y));
						}
						else if(hwndstructs[i].nTableSite == 1)
						{
							POINT ptClick = pThis->colorsetting[hwndstructs[i].nTableSite].ptJoin;
							HWND hwnd = ::ChildWindowFromPoint(hwndstructs[i].hwnd, ptClick);
							::SendMessage(hwnd, 
								WM_LBUTTONDOWN, 
								MK_LBUTTON, 
								MAKELPARAM(1, 1));
							Sleep(200);
							::SendMessage(hwnd, 
								WM_LBUTTONUP, 
								0, 
								MAKELPARAM(1, 1));
						}
					}
					
					::MoveWindow(hwndstructs[i].hwnd, 
						pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].left, 
						pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].top, 
						pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].right, 
						pThis->layoutsetting[hwndstructs[i].nTableSite].activerect[pThis->nIndex4Slot[hwndstructs[i].nTableSite]].bottom, 
						TRUE);

					pThis->nIndex4Slot[hwndstructs[i].nTableSite] = (pThis->nIndex4Slot[hwndstructs[i].nTableSite] + 1) % pThis->layoutsetting[hwndstructs[i].nTableSite].nStackNumber;

					if(((CButton*)(pThis->GetDlgItem(IDC_CHKALERTSOUND)))->GetCheck() == BST_CHECKED)
						MCIWndPlay(pThis->hwndPlay);

					pThis->RemoveItem(i, FALSE);
				}
			}
		}
		Sleep(100);
	}
	return 0;
}

void CPokerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 100)
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;

		hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if( hProcessSnap == INVALID_HANDLE_VALUE )
		{
			return;
		}

		pe32.dwSize = sizeof( PROCESSENTRY32 );

		if( !Process32First( hProcessSnap, &pe32 ) )
		{
			CloseHandle( hProcessSnap );    // Must clean up the
			return;
		}

		do
		{
			if(stricmp(pe32.szExeFile, "WPT.exe") == 0)
				dwWPTPokerPID = pe32.th32ProcessID;

			if(stricmp(pe32.szExeFile, "POKER.exe") == 0)
				dwLAPokerPID = pe32.th32ProcessID;
			
		} while( Process32Next( hProcessSnap, &pe32 ) );

		CloseHandle( hProcessSnap );

	}
	CDialog::OnTimer(nIDEvent);
}

void CPokerDlg::AddItem(HWND hwnd, int nTableSite)
{
	char szTemp[256];
 	::GetWindowText(hwnd, szTemp, 256);
	char szWindowName[256];
	if(strstr(szTemp, "welcome to ") == 0)
		strcpy(szWindowName, szTemp);
	else
		strcpy(szWindowName, strstr(szTemp, "welcome to ") + strlen("welcome to "));

	::MoveWindow(hwnd, 
		layoutsetting[nTableSite].observationrect.left, 
		layoutsetting[nTableSite].observationrect.top, 
		layoutsetting[nTableSite].observationrect.right, 
		layoutsetting[nTableSite].observationrect.bottom, 
		TRUE);

	Sleep(100);
	hwndstructs[nCount].hwnd = hwnd;
	hwndstructs[nCount].nTableSite = nTableSite;

	BOOL bType6Or9 = FALSE;
	int nErr46 = 0, nErr49 = 0;
	int i, j, k;

	HDC hdc = ::GetDC(hwnd);
	for(i = 0; i < 6; i++)
	{
		COLORREF cr1 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptPoint[i].y);
		for(j = 0; j < 8; j++)
			if(cr1 == colorsetting[nTableSite].colorstruct[0].crColors[j][i])
				break;

		if(j != 8)
			continue;

		cr1 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptSeatPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptSeatPoint[i].y);
		for(; j < 11; j++)			
			if(cr1 == colorsetting[nTableSite].colorstruct[0].crColors[j][i])
				break;


		if(j == 11)
		{
			COLORREF cr2 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptEmptyPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptEmptyPoint[i].y);
			if(cr2 != colorsetting[nTableSite].colorstruct[0].crColors[11][i])
				nErr46++;
		}	
	}

	for(i = 0; i < 9; i++)
	{
		COLORREF cr1 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptPoint[i].y);
		for(j = 0; j < 8; j++)
			if(cr1 == colorsetting[nTableSite].colorstruct[1].crColors[j][i])
				break;

		if(j != 8)
			continue;

		cr1 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptSeatPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptSeatPoint[i].y);
		for(; j < 11; j++)			
			if(cr1 == colorsetting[nTableSite].colorstruct[1].crColors[j][i])
				break;


		if(j == 11)
		{
			COLORREF cr2 = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptEmptyPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptEmptyPoint[i].y);
			if(cr2 != colorsetting[nTableSite].colorstruct[1].crColors[11][i])
				nErr49++;
		}	
	}

	bType6Or9 = nErr46 > nErr49 ? FALSE : TRUE;

	if(nErr46 == 0 && nErr49 == 0)
		bType6Or9 = FALSE;

	if(nErr46 == 6 && nErr49 == 9)
		return;

	hwndstructs[nCount].bTableType = bType6Or9;

	
	hwndstructs[nCount].nEmptySeat = 0;

	if(bType6Or9 == TRUE) // 6 handed table
	{
		for(i = 0; i < 6; i++)
		{
			hwndstructs[nCount].nSeat[i] = 2;
			COLORREF cr;
			for(j = 0; j < 12; j++)
			{
				if(j == 0)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptPoint[i].y);
				else if(j == 8)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptSeatPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptSeatPoint[i].y);
				else if(j == 11)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[0].ptEmptyPoint[i].x, colorsetting[nTableSite].colorstruct[0].ptEmptyPoint[i].y);

				if(cr == colorsetting[nTableSite].colorstruct[0].crColors[j][i])
				{
					if(j < 8)
						hwndstructs[nCount].nSeat[i] = playersetting[nTableSite][j].bBadOrGood;
					else if(j < 11)
						hwndstructs[nCount].nSeat[i] = 2;
					else
						hwndstructs[nCount].nSeat[i] = 3;
					break;
				}
			}

			if(hwndstructs[nCount].nSeat[i] == 3)
				hwndstructs[nCount].nEmptySeat++;
		}
	}else if(bType6Or9 == FALSE) // 9 handed table
	{
		for(i = 0; i < 9; i++)
		{
			hwndstructs[nCount].nSeat[i] = 2;
			COLORREF cr;
			for(j = 0; j < 12; j++)
			{
				if(j == 0)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptPoint[i].y);
				else if(j == 8)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptSeatPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptSeatPoint[i].y);
				else if(j == 11)
					cr = ::GetPixel(hdc, colorsetting[nTableSite].colorstruct[1].ptEmptyPoint[i].x, colorsetting[nTableSite].colorstruct[1].ptEmptyPoint[i].y);

				if(cr == colorsetting[nTableSite].colorstruct[1].crColors[j][i])
				{
					if(j < 8)
						hwndstructs[nCount].nSeat[i] = playersetting[nTableSite][j].bBadOrGood;
					else if(j < 11)
						hwndstructs[nCount].nSeat[i] = 2;
					else
						hwndstructs[nCount].nSeat[i] = 3;
					break;
				}
			}

			if(hwndstructs[nCount].nSeat[i] == 3)
				hwndstructs[nCount].nEmptySeat++;
		}
	}
	::ReleaseDC(hwnd, hdc);

	hwndstructs[nCount].bSeated = FALSE;
	if(hwndstructs[nCount].nEmptySeat == 0 && ((CButton*)(GetDlgItem(IDC_CHKCLOSTTABLE)))->GetCheck() == BST_CHECKED)
	{
		::SendMessage(hwnd, WM_CLOSE, 0, 0);
		return;
	}

	m_hwndlist.InsertItem(nCount, szWindowName);

	if(hwndstructs[nCount].bTableType == TRUE)
		m_hwndlist.SetItemText(nCount, 2, "6 Hands");
	else
		m_hwndlist.SetItemText(nCount, 2, "9 Hands");

	char szText[256];
	sprintf(szText, "%d", hwndstructs[nCount].nEmptySeat);
	m_hwndlist.SetItemText(nCount, 3, szText);
	if(nTableSite == 0)
		m_hwndlist.SetItemText(nCount, 1, "WH");
	else if(nTableSite == 1)
		m_hwndlist.SetItemText(nCount, 1, "WPT");
	else if(nTableSite == 2)
		m_hwndlist.SetItemText(nCount, 1, "LA");

	m_hwndlist.SetCheck(nCount, TRUE);

	char szLog[1024];
	sprintf(szLog, "Open table detected : %s", szWindowName);
	AddLog(szLog);

	nCount++;
}

void CPokerDlg::OnNMDblclkHwndlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_hwndlist.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex != -1)
	{
		::ShowWindow(hwndstructs[nIndex].hwnd, SW_HIDE);
		::ShowWindow(hwndstructs[nIndex].hwnd, SW_SHOW);
		::SetForegroundWindow(hwndstructs[nIndex].hwnd);
	}
}

void CPokerDlg::UpdateItem(HWND hwnd, int nIndex)
{
	int i, j, k;

	::MoveWindow(hwnd, 
		layoutsetting[hwndstructs[nIndex].nTableSite].observationrect.left, 
		layoutsetting[hwndstructs[nIndex].nTableSite].observationrect.top, 
		layoutsetting[hwndstructs[nIndex].nTableSite].observationrect.right, 
		layoutsetting[hwndstructs[nIndex].nTableSite].observationrect.bottom, 
		TRUE);

	HDC hdc = ::GetDC(hwnd);

	hwndstructs[nIndex].nEmptySeat = 0;

	if(hwndstructs[nIndex].bTableType == TRUE) // 6 handed table
	{
		for(i = 0; i < 6; i++)
		{
			hwndstructs[nIndex].nSeat[i] = 2;
			COLORREF cr;
			for(j = 0; j < 12; j++)
			{
				if(j == 0)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptPoint[i].y);
				else if(j == 8)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptSeatPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptSeatPoint[i].y);
				else if(j == 11)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptEmptyPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].ptEmptyPoint[i].y);

				if(cr == colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[0].crColors[j][i])
				{
					if(j < 8)
						hwndstructs[nIndex].nSeat[i] = playersetting[hwndstructs[nIndex].nTableSite][j].bBadOrGood;
					else if(j < 11)
						hwndstructs[nIndex].nSeat[i] = 2;
					else
						hwndstructs[nIndex].nSeat[i] = 3;
					break;
				}
			}

			if(hwndstructs[nIndex].nSeat[i] == 3)
				hwndstructs[nIndex].nEmptySeat++;
		}
	}else // 9 handed table
	{
		for(i = 0; i < 9; i++)
		{
			hwndstructs[nIndex].nSeat[i] = 2;
			COLORREF cr;
			for(j = 0; j < 12; j++)
			{
				if(j == 0)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptPoint[i].y);
				else if(j == 8)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptSeatPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptSeatPoint[i].y);
				else if(j == 11)
					cr = ::GetPixel(hdc, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptEmptyPoint[i].x, colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].ptEmptyPoint[i].y);

				if(cr == colorsetting[hwndstructs[nIndex].nTableSite].colorstruct[1].crColors[j][i])
				{
					if(j < 8)
						hwndstructs[nIndex].nSeat[i] = playersetting[hwndstructs[nIndex].nTableSite][j].bBadOrGood;
					else if(j < 11)
						hwndstructs[nIndex].nSeat[i] = 2;
					else
						hwndstructs[nIndex].nSeat[i] = 3;
					break;
				}
			}

			if(hwndstructs[nIndex].nSeat[i] == 3)
				hwndstructs[nIndex].nEmptySeat++;
		}
	}

	char szText[256];
	sprintf(szText, "%d", hwndstructs[nIndex].nEmptySeat);
	m_hwndlist.SetItemText(nIndex, 3, szText);

	::ReleaseDC(hwnd, hdc);
	return;
}

int CPokerDlg::RemoveItem(int nIndex, BOOL bClear)
{
	if(bClear)
	{
		m_hwndlist.DeleteItem(nIndex);

		for(int i = nIndex + 1; i < nCount; i++)
		{
			hwndstructs[i - 1] = hwndstructs[i];
		}
		nCount--;
	}
	else
	{
		hwndstructs[nIndex].bSeated = TRUE;
		m_hwndlist.SetCheck(nIndex, FALSE);
		m_hwndlist.SetItemText(nIndex, 3, "#");
	}

	return 0;
}

int CPokerDlg::AddLog(char* pszLog)
{
	if(((CButton*)GetDlgItem(IDC_CHKMESSAGE))->GetCheck() != BST_CHECKED)
		return 0;
	int nLen = GetDlgItem(IDC_LOGS)->GetWindowTextLength();
	char* pszText = (char*)malloc(nLen + 1024);

	GetDlgItem(IDC_LOGS)->GetWindowText(pszText, nLen + 1);

	strcat(pszText, pszLog);
	strcat(pszText, "\r\n");

	GetDlgItem(IDC_LOGS)->SetWindowText(pszText);

	((CEdit*)GetDlgItem(IDC_LOGS))->SetSel(0xFFFF, 0xFFFF);
	free(pszText);
	return 0;
}

BOOL CPokerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(LOWORD(wParam) == IDC_HOTKEY)
	{
		UnregisterHotKey(this->m_hWnd, 0x321);
		WORD wKeyCode, wModifier;
		m_hotkeyctrl.GetHotKey(wKeyCode, wModifier);
		RegisterHotKey(this->m_hWnd, 0x321, wModifier, wKeyCode);
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CPokerDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if(nHotKeyId == 0x321)
	{
		HWND hwnd = ::GetForegroundWindow();
		//CPokerDlg* pThis = (CPokerDlg*) lParam;
		char szClassname[256];
		char szWindowsname[256];

		::GetClassName(hwnd, szClassname, 256);
		::GetWindowText(hwnd, szWindowsname, 256);

		if(strcmp(szClassname, "PTIODEVICE") == 0 && strlen(szWindowsname) > 0)
		{
			int i;
			BOOL bExist = FALSE;
			for(i = 0; i < nCount; i++)
			{
				if(hwndstructs[i].hwnd == hwnd)
				{
					bExist = TRUE;

					ChangeStatus(i);
				}
			}

			if(bExist == FALSE)
			{
				AddItem(hwnd, 0);
			}
		}

		else if(strncmp(szWindowsname, "WPT Poker", strlen("WPT Poker")) != 0 && 
			strlen(szWindowsname) > 0)
		{
			int i;
			BOOL bExist = FALSE;
			for(i = 0; i < nCount; i++)
			{
				if(hwndstructs[i].hwnd == hwnd)
				{
					bExist = TRUE;

					ChangeStatus(i);
				}
			}

			if(bExist == FALSE)
			{
				AddItem(hwnd, 1);
			}
		}

		else if(strncmp(szWindowsname, "Lobby", strlen("Lobby")) != 0 && 
			strlen(szWindowsname) > 0)
		{
			int i;
			BOOL bExist = FALSE;
			for(i = 0; i < nCount; i++)
			{
				if(hwndstructs[i].hwnd == hwnd)
				{
					bExist = TRUE;
					
					ChangeStatus(i);
				}
			}

			if(bExist == FALSE)
			{
				AddItem(hwnd, 2);
			}
		}

	}
	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CPokerDlg::ChangeStatus(int nIndex)
{
	if(hwndstructs[nIndex].bSeated)
		m_hwndlist.SetCheck(nIndex, TRUE);
	else
	{
		RemoveItem(nIndex, FALSE);

		::ShowWindow(hwndstructs[nIndex].hwnd, SW_HIDE);
		::ShowWindow(hwndstructs[nIndex].hwnd, SW_SHOW);
		::SetForegroundWindow(hwndstructs[nIndex].hwnd);

		::MoveWindow(hwndstructs[nIndex].hwnd, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].left, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].top, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].right, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].bottom, 
			TRUE);
	}
}

void CPokerDlg::OnNMRClickHwndlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_hwndlist.GetNextItem(-1, LVNI_SELECTED);
	::SendMessage(hwndstructs[nIndex].hwnd, WM_CLOSE, 0, 0);
	//RemoveItem(nIndex, TRUE);
}

void CPokerDlg::OnLvnItemchangedHwndlist(NMHDR *pNMHDR, LRESULT *pResult)
{
// 	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
// 	// TODO: Add your control notification handler code here
// 	*pResult = 0;
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int ns = pNMListView->uNewState & LVIS_STATEIMAGEMASK;

	int nIndex = pNMListView->iItem;

	if((ns & 0x2000) != 0)
	{//Check
		hwndstructs[nIndex].bSeated = FALSE;
	}
	else if((ns & 0x1000) != 0)
	{//Uncheck
		hwndstructs[nIndex].bSeated = TRUE;
		m_hwndlist.SetItemText(nIndex, 3, "#");

		::ShowWindow(hwndstructs[nIndex].hwnd, SW_HIDE);
		::ShowWindow(hwndstructs[nIndex].hwnd, SW_SHOW);
		::SetForegroundWindow(hwndstructs[nIndex].hwnd);

		::MoveWindow(hwndstructs[nIndex].hwnd, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].left, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].top, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].right, 
			layoutsetting[hwndstructs[nIndex].nTableSite].activerect[0].bottom, 
			TRUE);
	}
}

void CPokerDlg::OnCbnSelchangeCmbsite()
{
	nSiteIndex = m_sitelist.GetCurSel();
	
	m_colorlist.DeleteAllItems();

	int nColorListCount = 0;

	SaveSetting();
	LoadSetting();

	if(nSiteIndex == 0 || nSiteIndex == 2)
		nColorListCount = 9;
	else
		nColorListCount = 6;

	for(int i = 0; i < nColorListCount; i++)
		m_colorlist.InsertItem(i, playersetting[nSiteIndex][i].szPlayerName);


	if(playersetting[nSiteIndex][0].bBadOrGood)
		((CButton*)GetDlgItem(IDC_CHKBAD))->SetCheck(BST_CHECKED);
	else
		((CButton*)GetDlgItem(IDC_CHKGOOD))->SetCheck(BST_CHECKED);

	if(pokersetting[nSiteIndex].bMoveToSlot)
		((CButton*)GetDlgItem(IDC_CHKMOVEOUT))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bTakeSeat)
		((CButton*)GetDlgItem(IDC_CHKJESUSSEAT))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bEnableSound)
		((CButton*)GetDlgItem(IDC_CHKALERTSOUND))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bShowMessage)
		((CButton*)GetDlgItem(IDC_CHKMESSAGE))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bCloseFilledTable)
		((CButton*)GetDlgItem(IDC_CHKCLOSTTABLE))->SetCheck(BST_CHECKED);
	if(pokersetting[nSiteIndex].bJoinWaitingList)
		((CButton*)GetDlgItem(IDC_CHKJOINWAITINGLIST))->SetCheck(BST_CHECKED);

	m_hotkeyctrl.SetHotKey(pokersetting[nSiteIndex].wHotKey, pokersetting[nSiteIndex].wModifier);

	m_colorlist.RedrawItems(0, m_colorlist.GetItemCount());

	WORD wKeyCode, wModifier;
	m_hotkeyctrl.GetHotKey(wKeyCode, wModifier);
	RegisterHotKey(this->m_hWnd, 0x321, wModifier, wKeyCode);

}
