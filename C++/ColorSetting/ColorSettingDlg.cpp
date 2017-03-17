// ColorSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorSetting.h"
#include "ColorSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorSettingDlg dialog

HWND hwndList[50];
int nHwndListCount;


CColorSettingDlg::CColorSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorSettingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_tablelist);
}

BEGIN_MESSAGE_MAP(CColorSettingDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST1, &CColorSettingDlg::OnLbnSelchangeList)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CColorSettingDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TABLETYPE6, &CColorSettingDlg::OnBnClickedTabletype6)
	ON_BN_CLICKED(IDC_TABLETYPE9, &CColorSettingDlg::OnBnClickedTabletype9)
	ON_BN_CLICKED(IDC_TABLETYPE2, &CColorSettingDlg::OnBnClickedTabletype2)
	ON_BN_CLICKED(IDC_REFRESH1, &CColorSettingDlg::OnBnClickedRefresh1)
	ON_BN_CLICKED(IDC_REFRESH2, &CColorSettingDlg::OnBnClickedRefresh2)
	ON_BN_CLICKED(IDC_REFRESH3, &CColorSettingDlg::OnBnClickedRefresh3)
	ON_BN_CLICKED(IDC_REFRESH4, &CColorSettingDlg::OnBnClickedRefresh4)
	ON_BN_CLICKED(IDC_REFRESH5, &CColorSettingDlg::OnBnClickedRefresh5)
	ON_BN_CLICKED(IDC_REFRESH6, &CColorSettingDlg::OnBnClickedRefresh6)
	ON_BN_CLICKED(IDC_REFRESH7, &CColorSettingDlg::OnBnClickedRefresh7)
	ON_BN_CLICKED(IDC_REFRESH8, &CColorSettingDlg::OnBnClickedRefresh8)
	ON_BN_CLICKED(IDC_REFRESH9, &CColorSettingDlg::OnBnClickedRefresh9)
	ON_BN_CLICKED(IDC_REFRESH10, &CColorSettingDlg::OnBnClickedRefresh10)
	ON_BN_CLICKED(IDC_REFRESH11, &CColorSettingDlg::OnBnClickedRefresh11)
	ON_BN_CLICKED(IDC_PLAYERPOS1, &CColorSettingDlg::OnBnClickedPlayerpos1)
	ON_BN_CLICKED(IDC_PLAYERPOS2, &CColorSettingDlg::OnBnClickedPlayerpos2)
	ON_BN_CLICKED(IDC_PLAYERPOS3, &CColorSettingDlg::OnBnClickedPlayerpos3)
	ON_BN_CLICKED(IDC_PLAYERPOS4, &CColorSettingDlg::OnBnClickedPlayerpos4)
	ON_BN_CLICKED(IDC_PLAYERPOS5, &CColorSettingDlg::OnBnClickedPlayerpos5)
	ON_BN_CLICKED(IDC_PLAYERPOS6, &CColorSettingDlg::OnBnClickedPlayerpos6)
	ON_BN_CLICKED(IDC_PLAYERPOS7, &CColorSettingDlg::OnBnClickedPlayerpos7)
	ON_BN_CLICKED(IDC_PLAYERPOS8, &CColorSettingDlg::OnBnClickedPlayerpos8)
	ON_BN_CLICKED(IDC_PLAYERPOS9, &CColorSettingDlg::OnBnClickedPlayerpos9)
	ON_BN_CLICKED(IDC_PLAYER1, &CColorSettingDlg::OnBnClickedPlayer1)
	ON_BN_CLICKED(IDC_PLAYER2, &CColorSettingDlg::OnBnClickedPlayer2)
	ON_BN_CLICKED(IDC_PLAYER3, &CColorSettingDlg::OnBnClickedPlayer3)
	ON_BN_CLICKED(IDC_PLAYER4, &CColorSettingDlg::OnBnClickedPlayer4)
	ON_BN_CLICKED(IDC_PLAYER5, &CColorSettingDlg::OnBnClickedPlayer5)
	ON_BN_CLICKED(IDC_PLAYER6, &CColorSettingDlg::OnBnClickedPlayer6)
	ON_BN_CLICKED(IDC_PLAYER7, &CColorSettingDlg::OnBnClickedPlayer7)
	ON_BN_CLICKED(IDC_PLAYER8, &CColorSettingDlg::OnBnClickedPlayer8)
	ON_BN_CLICKED(IDC_PLAYER9, &CColorSettingDlg::OnBnClickedPlayer9)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS1, &CColorSettingDlg::OnBnClickedEmptyplayerpos1)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS2, &CColorSettingDlg::OnBnClickedEmptyplayerpos2)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS3, &CColorSettingDlg::OnBnClickedEmptyplayerpos3)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS4, &CColorSettingDlg::OnBnClickedEmptyplayerpos4)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS5, &CColorSettingDlg::OnBnClickedEmptyplayerpos5)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS6, &CColorSettingDlg::OnBnClickedEmptyplayerpos6)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS7, &CColorSettingDlg::OnBnClickedEmptyplayerpos7)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS8, &CColorSettingDlg::OnBnClickedEmptyplayerpos8)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS9, &CColorSettingDlg::OnBnClickedEmptyplayerpos9)
	ON_BN_CLICKED(IDCANCEL, &CColorSettingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHKSITTINGOUT, &CColorSettingDlg::OnBnClickedChkSittingOut)
	ON_BN_CLICKED(IDC_CHKACTIVE, &CColorSettingDlg::OnBnClickedChkActive)
END_MESSAGE_MAP()


// CColorSettingDlg message handlers

BOOL CALLBACK EnumWindowsProc(
							  HWND hwnd, 
							  LPARAM lParam 
							  )
{
	char szText[1024];
	DWORD dwPID;
	LONG nStyle = ::GetWindowLong(hwnd, GWL_STYLE);

	GetWindowText(hwnd, szText, 1024);

	char szClassName[1024];
	GetClassName(hwnd, szClassName, 1024);


	if(strcmp(szClassName, "PokerStarsTableFrameClass") == 0 && 
		strlen(szText) > 0 && 
		nStyle & WS_VISIBLE)
	{
		((CListBox*)lParam)->AddString(szText);
		hwndList[nHwndListCount++] = hwnd;
	}

	return TRUE;
}

BOOL CColorSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	LoadSetting();

	nHwndListCount = 0;

	imagedlg = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&m_tablelist);

	((CButton*)GetDlgItem(IDC_TABLETYPE6))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER1))->SetCheck(BST_CHECKED);

	nType = 0;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 9; j++)
			colorsetting.colorstruct[i].nColorStatus[j] = 0;

	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[0].x, colorsetting.colorstruct[0].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[1].x, colorsetting.colorstruct[0].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[2].x, colorsetting.colorstruct[0].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[3].x, colorsetting.colorstruct[0].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[4].x, colorsetting.colorstruct[0].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[5].x, colorsetting.colorstruct[0].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[0].x, colorsetting.colorstruct[0].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[1].x, colorsetting.colorstruct[0].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[2].x, colorsetting.colorstruct[0].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[3].x, colorsetting.colorstruct[0].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[4].x, colorsetting.colorstruct[0].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[5].x, colorsetting.colorstruct[0].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[0].x, colorsetting.colorstruct[0].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[1].x, colorsetting.colorstruct[0].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[2].x, colorsetting.colorstruct[0].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[3].x, colorsetting.colorstruct[0].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[4].x, colorsetting.colorstruct[0].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[5].x, colorsetting.colorstruct[0].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.ptSittingOutPoint.x, colorsetting.ptSittingOutPoint.y);
	GetDlgItem(IDC_SITTINGOUTPOS)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.ptActivePoint.x, colorsetting.ptActivePoint.y);
	GetDlgItem(IDC_ACTIVEPOS)->SetWindowText(szPos);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int nIndex;
	
	if(((CButton*)GetDlgItem(IDC_TABLETYPE6))->GetCheck() == BST_CHECKED)
		nIndex = 0;
	else if(((CButton*)GetDlgItem(IDC_TABLETYPE9))->GetCheck() == BST_CHECKED)
		nIndex = 1;
	else if(((CButton*)GetDlgItem(IDC_TABLETYPE2))->GetCheck() == BST_CHECKED)
		nIndex = 2;

	GetDlgItem(IDC_COLOR_11)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][0]);
	GetDlgItem(IDC_COLOR_12)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][0]);
	GetDlgItem(IDC_COLOR_13)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][0]);
	GetDlgItem(IDC_COLOR_14)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][0]);
	GetDlgItem(IDC_COLOR_15)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][0]);

	GetDlgItem(IDC_COLOR_21)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][1]);
	GetDlgItem(IDC_COLOR_22)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][1]);
	GetDlgItem(IDC_COLOR_23)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][1]);
	GetDlgItem(IDC_COLOR_24)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][1]);
	GetDlgItem(IDC_COLOR_25)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][1]);

	GetDlgItem(IDC_COLOR_31)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][2]);
	GetDlgItem(IDC_COLOR_32)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][2]);
	GetDlgItem(IDC_COLOR_33)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][2]);
	GetDlgItem(IDC_COLOR_34)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][2]);
	GetDlgItem(IDC_COLOR_35)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][2]);

	GetDlgItem(IDC_COLOR_41)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][3]);
	GetDlgItem(IDC_COLOR_42)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][3]);
	GetDlgItem(IDC_COLOR_43)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][3]);
	GetDlgItem(IDC_COLOR_44)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][3]);
	GetDlgItem(IDC_COLOR_45)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][3]);

	GetDlgItem(IDC_COLOR_51)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][4]);
	GetDlgItem(IDC_COLOR_52)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][4]);
	GetDlgItem(IDC_COLOR_53)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][4]);
	GetDlgItem(IDC_COLOR_54)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][4]);
	GetDlgItem(IDC_COLOR_55)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][4]);

	GetDlgItem(IDC_COLOR_61)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][5]);
	GetDlgItem(IDC_COLOR_62)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][5]);
	GetDlgItem(IDC_COLOR_63)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][5]);
	GetDlgItem(IDC_COLOR_64)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][5]);
	GetDlgItem(IDC_COLOR_65)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][5]);

	GetDlgItem(IDC_COLOR_71)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][6]);
	GetDlgItem(IDC_COLOR_72)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][6]);
	GetDlgItem(IDC_COLOR_73)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][6]);
	GetDlgItem(IDC_COLOR_74)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][6]);
	GetDlgItem(IDC_COLOR_75)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][6]);

	GetDlgItem(IDC_COLOR_81)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][7]);
	GetDlgItem(IDC_COLOR_82)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][7]);
	GetDlgItem(IDC_COLOR_83)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][7]);
	GetDlgItem(IDC_COLOR_84)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][7]);
	GetDlgItem(IDC_COLOR_85)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][7]);

	GetDlgItem(IDC_COLOR_91)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[0][8]);
	GetDlgItem(IDC_COLOR_92)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[1][8]);
	GetDlgItem(IDC_COLOR_93)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[2][8]);
	GetDlgItem(IDC_COLOR_94)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[3][8]);
	GetDlgItem(IDC_COLOR_95)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.colorstruct[nIndex].crColors[4][8]);

	GetDlgItem(IDC_COLOR_SITTINGOUT_01)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.crSO[0]);
	GetDlgItem(IDC_COLOR_SITTINGOUT_02)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.crSO[1]);
	GetDlgItem(IDC_COLOR_ACTIVE_01)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.crActive[0]);
	GetDlgItem(IDC_COLOR_ACTIVE_02)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting.crActive[1]);
}

void CColorSettingDlg::OnLbnSelchangeList()
{
	CString strTableName;
	m_tablelist.GetText(m_tablelist.GetCurSel(), strTableName);

	if(imagedlg)
	{
// 		imagedlg->DestroyWindow();
// 		delete imagedlg;
		imagedlg->hwnd = hwndList[m_tablelist.GetCurSel()];//::FindWindow(NULL, strTableName);
		return;
	}
	imagedlg = new CImageDialog;
	imagedlg->Create(IDD_IMAGE_DIALOG, this);
	imagedlg->hwnd = hwndList[m_tablelist.GetCurSel()];//::FindWindow(NULL, strTableName);

	RECT hwndrect, rect;
	::GetWindowRect(imagedlg->hwnd, &hwndrect);
	imagedlg->GetWindowRect(&rect);

	int nWidth = hwndrect.right - hwndrect.left;
	int nHeight = hwndrect.bottom - hwndrect.top;

	//SetWindowPos(this, rect.left, rect.top, hwndrect.right - hwndrect.left, hwndrect.bottom - hwndrect.top, SWP_SHOWWINDOW);
	imagedlg->SetWindowPos(NULL, rect.left, rect.top, nWidth, nHeight, SWP_SHOWWINDOW);

	imagedlg->hwndSend = this->m_hWnd;
	imagedlg->ShowWindow(SW_SHOW);

	if(((CButton*)GetDlgItem(IDC_CHKSITTINGOUT))->GetCheck() == BST_CHECKED)
		imagedlg->nMode = 2;

	if(((CButton*)GetDlgItem(IDC_CHKACTIVE))->GetCheck() == BST_CHECKED)
		imagedlg->nMode = 4;

 	if(((CButton*)GetDlgItem(IDC_PLAYERPOS1))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS2))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS3))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS4))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS5))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS6))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS7))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS8))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_PLAYERPOS9))->GetCheck() == BST_CHECKED)
	{
		imagedlg->nMode = 1;
	}
	else if(((CButton*)GetDlgItem(IDC_EMPTYPOS1))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS2))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS3))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS4))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS5))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS6))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS7))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS8))->GetCheck() == BST_CHECKED || 
		((CButton*)GetDlgItem(IDC_EMPTYPOS9))->GetCheck() == BST_CHECKED)
	{
		imagedlg->nMode = 3;
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorSettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CColorSettingDlg::LoadSetting(void)
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

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 5; j++)
			for(int k = 0; k < 9; k++)
				colorsetting.colorstruct[i].crColors[j][k] = RGB(255, 255, 255);

		for(int j = 0; j < 9; j++)
		{
			colorsetting.colorstruct[i].ptPoint[j].x = 0;
			colorsetting.colorstruct[i].ptPoint[j].y = 0;

			colorsetting.colorstruct[i].ptSeatPoint[j].x = 0;
			colorsetting.colorstruct[i].ptSeatPoint[j].y = 0;

			colorsetting.colorstruct[i].ptEmptyPoint[j].x = 0;
			colorsetting.colorstruct[i].ptEmptyPoint[j].y = 0;
		}
	}
	colorsetting.ptSittingOutPoint.x = 0;
	colorsetting.ptSittingOutPoint.y = 0;
	colorsetting.ptActivePoint.x = 0;
	colorsetting.ptActivePoint.y = 0;
	colorsetting.crSO[0] = RGB(255, 255, 255);
	colorsetting.crSO[1] = RGB(255, 255, 255);
	colorsetting.crActive[0] = RGB(255, 255, 255);
	colorsetting.crActive[1] = RGB(255, 255, 255);

	if(hConfigFile != INVALID_HANDLE_VALUE)
	{
		//for(int i = 0; i < SITE_COUNT; i++)
		{
			ReadFile(hConfigFile, &colorsetting, sizeof(COLORSETTING), &dwBytes, NULL);
		}
	}

	CloseHandle(hConfigFile);
}

void CColorSettingDlg::SaveSetting(void)
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

	//for(int i = 0; i < SITE_COUNT; i++)
	{
		WriteFile(hConfigFile, &colorsetting, sizeof(COLORSETTING), &dwBytes, NULL);
	}

	CloseHandle(hConfigFile);
}

LRESULT CColorSettingDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_SENDPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		COLORREF cr = *(COLORREF*)lParam;
		int nIndex = 0;
		int nTypeIndex = 0;

		if(((CButton*)GetDlgItem(IDC_TABLETYPE6))->GetCheck() == BST_CHECKED)
			nTypeIndex = 0;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE9))->GetCheck() == BST_CHECKED)
			nTypeIndex = 1;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE2))->GetCheck() == BST_CHECKED)
			nTypeIndex = 2;

		if(((CButton*)GetDlgItem(IDC_PLAYER1))->GetCheck() == BST_CHECKED)
		{
			nIndex = 0;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER2))->GetCheck() == BST_CHECKED)
		{
			nIndex = 1;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER3))->GetCheck() == BST_CHECKED)
		{
			nIndex = 2;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER4))->GetCheck() == BST_CHECKED)
		{
			nIndex = 3;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER5))->GetCheck() == BST_CHECKED)
		{
			nIndex = 4;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER6))->GetCheck() == BST_CHECKED)
		{
			nIndex = 5;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER7))->GetCheck() == BST_CHECKED)
		{
			nIndex = 6;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER8))->GetCheck() == BST_CHECKED)
		{
			nIndex = 7;
		}else if(((CButton*)GetDlgItem(IDC_PLAYER9))->GetCheck() == BST_CHECKED)
		{
			nIndex = 8;
		}else 
			return 0;


		colorsetting.colorstruct[nTypeIndex].ptPoint[nIndex] = pt;
		colorsetting.colorstruct[nTypeIndex].crColors[0][nIndex] = cr;

		char szPos[256];
		sprintf(szPos, "%d, %d", pt.x, pt.y);

		switch (nIndex)
		{
		case 0:
			GetDlgItem(IDC_POS1)->SetWindowText(szPos);
			break;
		case 1:
			GetDlgItem(IDC_POS2)->SetWindowText(szPos);
			break;
		case 2:
			GetDlgItem(IDC_POS3)->SetWindowText(szPos);
			break;
		case 3:
			GetDlgItem(IDC_POS4)->SetWindowText(szPos);
			break;
		case 4:
			GetDlgItem(IDC_POS5)->SetWindowText(szPos);
			break;
		case 5:
			GetDlgItem(IDC_POS6)->SetWindowText(szPos);
			break;
		case 6:
			GetDlgItem(IDC_POS7)->SetWindowText(szPos);
			break;
		case 7:
			GetDlgItem(IDC_POS8)->SetWindowText(szPos);
			break;
		case 8:
			GetDlgItem(IDC_POS9)->SetWindowText(szPos);
			break;
		}

		Invalidate(TRUE);

	}

	if(message == WM_SENDCOLOR || message == WM_SEATPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		COLORREF cr = *(COLORREF*)lParam;

		int nIndex = 0;
		int nTypeIndex = 0;

		if(((CButton*)GetDlgItem(IDC_TABLETYPE6))->GetCheck() == BST_CHECKED)
			nTypeIndex = 0;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE9))->GetCheck() == BST_CHECKED)
			nTypeIndex = 1;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE2))->GetCheck() == BST_CHECKED)
			nTypeIndex = 2;

		if(((CButton*)GetDlgItem(IDC_PLAYERPOS1))->GetCheck() == BST_CHECKED)
		{
			nIndex = 0;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS2))->GetCheck() == BST_CHECKED)
		{
			nIndex = 1;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS3))->GetCheck() == BST_CHECKED)
		{
			nIndex = 2;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS4))->GetCheck() == BST_CHECKED)
		{
			nIndex = 3;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS5))->GetCheck() == BST_CHECKED)
		{
			nIndex = 4;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS6))->GetCheck() == BST_CHECKED)
		{
			nIndex = 5;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS7))->GetCheck() == BST_CHECKED)
		{
			nIndex = 6;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS8))->GetCheck() == BST_CHECKED)
		{
			nIndex = 7;
		}else if(((CButton*)GetDlgItem(IDC_PLAYERPOS9))->GetCheck() == BST_CHECKED)
		{
			nIndex = 8;
		}else 
			return 0;

		colorsetting.colorstruct[nTypeIndex].ptSeatPoint[nIndex] = pt;

		if(message == WM_SEATPOSITION)
			colorsetting.colorstruct[nTypeIndex].nColorStatus[nIndex] = 1;
		else if(colorsetting.colorstruct[nTypeIndex].nColorStatus[nIndex] < 4)
			colorsetting.colorstruct[nTypeIndex].nColorStatus[nIndex]++;

		colorsetting.colorstruct[nTypeIndex].crColors[colorsetting.colorstruct[nTypeIndex].nColorStatus[nIndex]][nIndex] = cr;

		char szPos[256];
		sprintf(szPos, "%d, %d", pt.x, pt.y);

		switch (nIndex)
		{
		case 0:
			GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
			break;
		case 1:
			GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
			break;
		case 2:
			GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
			break;
		case 3:
			GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
			break;
		case 4:
			GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
			break;
		case 5:
			GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
			break;
		case 6:
			GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
			break;
		case 7:
			GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
			break;
		case 8:
			GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);
			break;
		}

		Invalidate(TRUE);
	}

	if(message == WM_SENDCOLOR_SITTINGOUT || message == WM_SITTINGOUTPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		COLORREF cr = *(COLORREF*)lParam;
		colorsetting.ptSittingOutPoint = pt;
		
		if(message == WM_SITTINGOUTPOSITION)
			nColorCount = 0;
		else if(nColorCount < 2)
			nColorCount++;

		colorsetting.crSO[nColorCount] = cr;
		
		char szPos[256];
		sprintf(szPos, "%d, %d", colorsetting.ptSittingOutPoint.x, colorsetting.ptSittingOutPoint.y);
		GetDlgItem(IDC_SITTINGOUTPOS)->SetWindowText(szPos);

		Invalidate(TRUE);
	}

	if(message == WM_SENDCOLOR_ACTIVATE || message == WM_ACTIVEPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		COLORREF cr = *(COLORREF*)lParam;
		colorsetting.ptActivePoint = pt;

		if(message == WM_ACTIVEPOSITION)
			nColorCount = 0;
		else if(nColorCount < 2)
			nColorCount++;

		colorsetting.crActive[nColorCount] = cr;

		char szPos[256];
		sprintf(szPos, "%d, %d", colorsetting.ptActivePoint.x, colorsetting.ptActivePoint.y);
		GetDlgItem(IDC_ACTIVEPOS)->SetWindowText(szPos);

		Invalidate(TRUE);
	}

	if(message == WM_EMPTYPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		COLORREF cr = *(COLORREF*)lParam;
		int nIndex = 0;
		int nTypeIndex = 0;

		if(((CButton*)GetDlgItem(IDC_TABLETYPE6))->GetCheck() == BST_CHECKED)
			nTypeIndex = 0;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE9))->GetCheck() == BST_CHECKED)
			nTypeIndex = 1;
		else if(((CButton*)GetDlgItem(IDC_TABLETYPE2))->GetCheck() == BST_CHECKED)
			nTypeIndex = 2;

		if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS1))->GetCheck() == BST_CHECKED)
		{
			nIndex = 0;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS2))->GetCheck() == BST_CHECKED)
		{
			nIndex = 1;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS3))->GetCheck() == BST_CHECKED)
		{
			nIndex = 2;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS4))->GetCheck() == BST_CHECKED)
		{
			nIndex = 3;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS5))->GetCheck() == BST_CHECKED)
		{
			nIndex = 4;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS6))->GetCheck() == BST_CHECKED)
		{
			nIndex = 5;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS7))->GetCheck() == BST_CHECKED)
		{
			nIndex = 6;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS8))->GetCheck() == BST_CHECKED)
		{
			nIndex = 7;
		}else if(((CButton*)GetDlgItem(IDC_EMPTYPLAYERPOS9))->GetCheck() == BST_CHECKED)
		{
			nIndex = 8;
		}else 
			return 0;


		colorsetting.colorstruct[nTypeIndex].ptEmptyPoint[nIndex] = pt;
		colorsetting.colorstruct[nTypeIndex].crColors[4][nIndex] = cr;

		char szPos[256];
		sprintf(szPos, "%d, %d", pt.x, pt.y);

		switch (nIndex)
		{
		case 0:
			GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
			break;
		case 1:
			GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
			break;
		case 2:
			GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
			break;
		case 3:
			GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
			break;
		case 4:
			GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
			break;
		case 5:
			GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
			break;
		case 6:
			GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
			break;
		case 7:
			GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos);
			break;
		case 8:
			GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
			break;
		}

		Invalidate(TRUE);
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CColorSettingDlg::OnBnClickedCancel()
{
	if(imagedlg)
	{
		imagedlg->DestroyWindow();
		delete imagedlg;
		imagedlg = NULL;
	}

	OnCancel();
}

void CColorSettingDlg::OnBnClickedOk()
{
	SaveSetting();
	CDialog::OnOK();
}

void CColorSettingDlg::OnBnClickedTabletype6()
{
	Invalidate(TRUE);
	nType = 0;
	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[0].x, colorsetting.colorstruct[0].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[1].x, colorsetting.colorstruct[0].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[2].x, colorsetting.colorstruct[0].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[3].x, colorsetting.colorstruct[0].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[4].x, colorsetting.colorstruct[0].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptPoint[5].x, colorsetting.colorstruct[0].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[0].x, colorsetting.colorstruct[0].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[1].x, colorsetting.colorstruct[0].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[2].x, colorsetting.colorstruct[0].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[3].x, colorsetting.colorstruct[0].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[4].x, colorsetting.colorstruct[0].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptSeatPoint[5].x, colorsetting.colorstruct[0].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[0].x, colorsetting.colorstruct[0].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[1].x, colorsetting.colorstruct[0].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[2].x, colorsetting.colorstruct[0].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[3].x, colorsetting.colorstruct[0].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[4].x, colorsetting.colorstruct[0].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[0].ptEmptyPoint[5].x, colorsetting.colorstruct[0].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
}

void CColorSettingDlg::OnBnClickedTabletype9()
{
	Invalidate(TRUE);
	nType = 1;
	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[0].x, colorsetting.colorstruct[1].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[1].x, colorsetting.colorstruct[1].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[2].x, colorsetting.colorstruct[1].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[3].x, colorsetting.colorstruct[1].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[4].x, colorsetting.colorstruct[1].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[5].x, colorsetting.colorstruct[1].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[6].x, colorsetting.colorstruct[1].ptPoint[6].y);
	GetDlgItem(IDC_POS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[7].x, colorsetting.colorstruct[1].ptPoint[7].y);
	GetDlgItem(IDC_POS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptPoint[8].x, colorsetting.colorstruct[1].ptPoint[8].y);
	GetDlgItem(IDC_POS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[0].x, colorsetting.colorstruct[1].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[1].x, colorsetting.colorstruct[1].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[2].x, colorsetting.colorstruct[1].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[3].x, colorsetting.colorstruct[1].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[4].x, colorsetting.colorstruct[1].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[5].x, colorsetting.colorstruct[1].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[6].x, colorsetting.colorstruct[1].ptSeatPoint[6].y);
	GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[7].x, colorsetting.colorstruct[1].ptSeatPoint[7].y);
	GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptSeatPoint[8].x, colorsetting.colorstruct[1].ptSeatPoint[8].y);
	GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[0].x, colorsetting.colorstruct[1].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[1].x, colorsetting.colorstruct[1].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[2].x, colorsetting.colorstruct[1].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[3].x, colorsetting.colorstruct[1].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[4].x, colorsetting.colorstruct[1].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[5].x, colorsetting.colorstruct[1].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[6].x, colorsetting.colorstruct[1].ptEmptyPoint[6].y);
	GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[7].x, colorsetting.colorstruct[1].ptEmptyPoint[7].y);
	GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[1].ptEmptyPoint[8].x, colorsetting.colorstruct[1].ptEmptyPoint[8].y);
	GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
}

void CColorSettingDlg::OnBnClickedTabletype2()
{
	Invalidate(TRUE);
	nType = 2;
	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptPoint[0].x, colorsetting.colorstruct[2].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptPoint[1].x, colorsetting.colorstruct[2].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptSeatPoint[0].x, colorsetting.colorstruct[2].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptSeatPoint[1].x, colorsetting.colorstruct[2].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptEmptyPoint[0].x, colorsetting.colorstruct[2].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting.colorstruct[2].ptEmptyPoint[1].x, colorsetting.colorstruct[2].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos); 
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
}

void CColorSettingDlg::OnBnClickedRefresh1()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS1))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[0]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh2()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS2))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[1]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh3()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS3))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[2]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh4()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS4))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[3]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh5()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS5))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[4]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh6()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS6))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[5]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh7()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS7))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[6]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh8()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS8))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[7]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh9()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS9))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[8]), 0);
}

void CColorSettingDlg::OnBnClickedRefresh10()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_CHKSITTINGOUT))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SITTINGOUTPOSITION, (WPARAM)&(colorsetting.ptSittingOutPoint), 0);
}

void CColorSettingDlg::OnBnClickedRefresh11()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_CHKACTIVE))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_ACTIVEPOSITION, (WPARAM)&(colorsetting.ptActivePoint), 0);
}

void CColorSettingDlg::ClearSelection(void)
{
	((CButton*)GetDlgItem(IDC_PLAYER1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER4))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER5))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER6))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER7))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER8))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER9))->SetCheck(BST_UNCHECKED);

	((CButton*)GetDlgItem(IDC_PLAYERPOS1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS4))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS5))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS6))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS7))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS8))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_PLAYERPOS9))->SetCheck(BST_UNCHECKED);

	((CButton*)GetDlgItem(IDC_EMPTYPOS1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS4))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS5))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS6))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS7))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS8))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_EMPTYPOS9))->SetCheck(BST_UNCHECKED);

	((CButton*)GetDlgItem(IDC_CHKSITTINGOUT))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHKACTIVE))->SetCheck(BST_UNCHECKED);
}

void CColorSettingDlg::OnBnClickedPlayerpos1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[0]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[1]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[2]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[3]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[4]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[5]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[6]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[7]), 1);
}

void CColorSettingDlg::OnBnClickedPlayerpos9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptSeatPoint[8]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[0]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[1]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[2]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[3]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[4]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[5]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[6]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[7]), 1);
}

void CColorSettingDlg::OnBnClickedPlayer9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptPoint[8]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[0]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[1]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[2]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[3]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[4]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[5]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[6]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[7]), 1);
}

void CColorSettingDlg::OnBnClickedEmptyplayerpos9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting.colorstruct[nType].ptEmptyPoint[8]), 1);
}

void CColorSettingDlg::OnBnClickedChkSittingOut()
{
	if(((CButton*)GetDlgItem(IDC_CHKSITTINGOUT))->GetCheck() == BST_CHECKED)
	{
		if(imagedlg != NULL)
			::SendMessage(imagedlg->m_hWnd, WM_SITTINGOUTPOSITION, (WPARAM)&(colorsetting.ptSittingOutPoint), 1);
	}
}

void CColorSettingDlg::OnBnClickedChkActive()
{
	if(((CButton*)GetDlgItem(IDC_CHKACTIVE))->GetCheck() == BST_CHECKED)
	{
		if(imagedlg != NULL)
			::SendMessage(imagedlg->m_hWnd, WM_ACTIVEPOSITION, (WPARAM)&(colorsetting.ptActivePoint), 1);
	}
}

