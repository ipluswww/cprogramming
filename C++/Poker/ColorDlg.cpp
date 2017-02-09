// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poker.h"
#include "ColorDlg.h"


// CColorDlg dialog
DWORD dwWPTPID, dwLAPID;

HWND hwndList[50];
int nHwndListCount;

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_tablelist);
	DDX_Control(pDX, IDC_COMBO1, m_colorlist);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CColorDlg::OnLbnSelchangeList1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CColorDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TABLETYPE6, &CColorDlg::OnBnClickedTabletype6)
	ON_BN_CLICKED(IDC_TABLETYPE9, &CColorDlg::OnBnClickedTabletype9)
	ON_BN_CLICKED(IDC_REFRESH1, &CColorDlg::OnBnClickedRefresh1)
	ON_BN_CLICKED(IDC_REFRESH2, &CColorDlg::OnBnClickedRefresh2)
	ON_BN_CLICKED(IDC_REFRESH3, &CColorDlg::OnBnClickedRefresh3)
	ON_BN_CLICKED(IDC_REFRESH4, &CColorDlg::OnBnClickedRefresh4)
	ON_BN_CLICKED(IDC_REFRESH5, &CColorDlg::OnBnClickedRefresh5)
	ON_BN_CLICKED(IDC_REFRESH6, &CColorDlg::OnBnClickedRefresh6)
	ON_BN_CLICKED(IDC_REFRESH7, &CColorDlg::OnBnClickedRefresh7)
	ON_BN_CLICKED(IDC_REFRESH8, &CColorDlg::OnBnClickedRefresh8)
	ON_BN_CLICKED(IDC_REFRESH9, &CColorDlg::OnBnClickedRefresh9)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CColorDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_PLAYERPOS1, &CColorDlg::OnBnClickedPlayerpos1)
	ON_BN_CLICKED(IDC_PLAYERPOS2, &CColorDlg::OnBnClickedPlayerpos2)
	ON_BN_CLICKED(IDC_PLAYERPOS3, &CColorDlg::OnBnClickedPlayerpos3)
	ON_BN_CLICKED(IDC_PLAYERPOS4, &CColorDlg::OnBnClickedPlayerpos4)
	ON_BN_CLICKED(IDC_PLAYERPOS5, &CColorDlg::OnBnClickedPlayerpos5)
	ON_BN_CLICKED(IDC_PLAYERPOS6, &CColorDlg::OnBnClickedPlayerpos6)
	ON_BN_CLICKED(IDC_PLAYERPOS7, &CColorDlg::OnBnClickedPlayerpos7)
	ON_BN_CLICKED(IDC_PLAYERPOS8, &CColorDlg::OnBnClickedPlayerpos8)
	ON_BN_CLICKED(IDC_PLAYERPOS9, &CColorDlg::OnBnClickedPlayerpos9)
	ON_BN_CLICKED(IDC_CHKJOINPOS, &CColorDlg::OnBnClickedChkjoinpos)
	ON_BN_CLICKED(IDC_PLAYER1, &CColorDlg::OnBnClickedPlayer1)
	ON_BN_CLICKED(IDC_PLAYER2, &CColorDlg::OnBnClickedPlayer2)
	ON_BN_CLICKED(IDC_PLAYER3, &CColorDlg::OnBnClickedPlayer3)
	ON_BN_CLICKED(IDC_PLAYER4, &CColorDlg::OnBnClickedPlayer4)
	ON_BN_CLICKED(IDC_PLAYER5, &CColorDlg::OnBnClickedPlayer5)
	ON_BN_CLICKED(IDC_PLAYER6, &CColorDlg::OnBnClickedPlayer6)
	ON_BN_CLICKED(IDC_PLAYER7, &CColorDlg::OnBnClickedPlayer7)
	ON_BN_CLICKED(IDC_PLAYER8, &CColorDlg::OnBnClickedPlayer8)
	ON_BN_CLICKED(IDC_PLAYER9, &CColorDlg::OnBnClickedPlayer9)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS1, &CColorDlg::OnBnClickedEmptyplayerpos1)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS2, &CColorDlg::OnBnClickedEmptyplayerpos2)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS3, &CColorDlg::OnBnClickedEmptyplayerpos3)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS4, &CColorDlg::OnBnClickedEmptyplayerpos4)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS5, &CColorDlg::OnBnClickedEmptyplayerpos5)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS6, &CColorDlg::OnBnClickedEmptyplayerpos6)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS7, &CColorDlg::OnBnClickedEmptyplayerpos7)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS8, &CColorDlg::OnBnClickedEmptyplayerpos8)
	ON_BN_CLICKED(IDC_EMPTYPLAYERPOS9, &CColorDlg::OnBnClickedEmptyplayerpos9)
	ON_BN_CLICKED(IDC_REFRESH10, &CColorDlg::OnBnClickedRefresh10)
	ON_BN_CLICKED(IDC_REFRESH11, &CColorDlg::OnBnClickedRefresh11)
	ON_BN_CLICKED(IDC_REFRESH12, &CColorDlg::OnBnClickedRefresh12)
	ON_BN_CLICKED(IDC_REFRESH13, &CColorDlg::OnBnClickedRefresh13)
	ON_BN_CLICKED(IDC_REFRESH14, &CColorDlg::OnBnClickedRefresh14)
	ON_BN_CLICKED(IDC_REFRESH15, &CColorDlg::OnBnClickedRefresh15)
	ON_BN_CLICKED(IDC_REFRESH16, &CColorDlg::OnBnClickedRefresh16)
	ON_BN_CLICKED(IDC_REFRESH17, &CColorDlg::OnBnClickedRefresh17)
	ON_BN_CLICKED(IDC_REFRESH18, &CColorDlg::OnBnClickedRefresh18)
END_MESSAGE_MAP()


// CColorDlg message handlers

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

	if(strcmp(szClassName, "PTIODEVICE") == 0 && 
		strlen(szText) > 0 && 
		nStyle & WS_VISIBLE && 
		strcmp(szText, "William Hill Poker") != 0)
	{
		((CListBox*)lParam)->AddString(szText);
		hwndList[nHwndListCount++] = hwnd;
	}

	GetWindowThreadProcessId(hwnd, &dwPID);
	if(dwPID == dwWPTPID && 
		strncmp(szText, "WPT Poker:", strlen("WPT Poker:")) != 0 && 
		nStyle & WS_VISIBLE && 
		strlen(szText) > 0)
	{
		((CListBox*)lParam)->AddString(szText);
		hwndList[nHwndListCount++] = hwnd;
	}

	if(dwPID == dwLAPID && 
		strncmp(szText, "Lobby", strlen("Lobby")) != 0 && 
		nStyle & WS_VISIBLE && 
		strlen(szText) > 0)
	{
		((CListBox*)lParam)->AddString(szText);
		hwndList[nHwndListCount++] = hwnd;
	}
	
	return TRUE;
}
BOOL CColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	dwWPTPID = dwWPTPokerPID;
	dwLAPID = dwLAPokerPID;
	nHwndListCount = 0;

	imagedlg = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&m_tablelist);

	((CButton*)GetDlgItem(IDC_TABLETYPE6))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_PLAYER1))->SetCheck(BST_CHECKED);

	nType = 0;

	for(int i = 0; i < nColorCount ; i++)
		m_colorlist.AddColor(pplayersetting[i].szPlayerName, pcrColor[i]);

	m_colorlist.SetCurSel(0);

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 9; j++)
			colorsetting->colorstruct[i].nColorStatus[j] = 0;

	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[0].x, colorsetting->colorstruct[0].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[1].x, colorsetting->colorstruct[0].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[2].x, colorsetting->colorstruct[0].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[3].x, colorsetting->colorstruct[0].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[4].x, colorsetting->colorstruct[0].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[5].x, colorsetting->colorstruct[0].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[0].x, colorsetting->colorstruct[0].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[1].x, colorsetting->colorstruct[0].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[2].x, colorsetting->colorstruct[0].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[3].x, colorsetting->colorstruct[0].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[4].x, colorsetting->colorstruct[0].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[5].x, colorsetting->colorstruct[0].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[0].x, colorsetting->colorstruct[0].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[1].x, colorsetting->colorstruct[0].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[2].x, colorsetting->colorstruct[0].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[3].x, colorsetting->colorstruct[0].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[4].x, colorsetting->colorstruct[0].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[5].x, colorsetting->colorstruct[0].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->ptJoin.x, colorsetting->ptJoin.y);
	GetDlgItem(IDC_JOINPOS)->SetWindowText(szPos);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CColorDlg::OnLbnSelchangeList1()
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

	if(((CButton*)GetDlgItem(IDC_CHKJOINPOS))->GetCheck() == BST_CHECKED)
		imagedlg->nMode = 2;

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

void CColorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(imagedlg)
	{
		imagedlg->DestroyWindow();
		delete imagedlg;
		imagedlg = NULL;
	}
	CDialog::OnClose();
}

LRESULT CColorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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


		colorsetting->colorstruct[nTypeIndex].ptPoint[nIndex] = pt;
		colorsetting->colorstruct[nTypeIndex].crColors[m_colorlist.GetCurSel()][nIndex] = cr;

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

		colorsetting->colorstruct[nTypeIndex].ptSeatPoint[nIndex] = pt;

		if(message == WM_SEATPOSITION)
			colorsetting->colorstruct[nTypeIndex].nColorStatus[nIndex] = 8;
		else if(colorsetting->colorstruct[nTypeIndex].nColorStatus[nIndex] < 11)
			colorsetting->colorstruct[nTypeIndex].nColorStatus[nIndex]++;

		colorsetting->colorstruct[nTypeIndex].crColors[colorsetting->colorstruct[nTypeIndex].nColorStatus[nIndex]][nIndex] = cr;

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
	if(message == WM_JOINPOSITION)
	{
		POINT pt = *(POINT*)wParam;
		colorsetting->ptJoin = pt;

		char szPos[256];
		sprintf(szPos, "%d, %d", colorsetting->ptJoin.x, colorsetting->ptJoin.y);
		GetDlgItem(IDC_JOINPOS)->SetWindowText(szPos);
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


		colorsetting->colorstruct[nTypeIndex].ptEmptyPoint[nIndex] = pt;
		colorsetting->colorstruct[nTypeIndex].crColors[11][nIndex] = cr;

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

void CColorDlg::RefreshColor(void)
{

}

void CColorDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CColorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int nIndex = m_colorlist.GetCurSel();

	if(((CButton*)GetDlgItem(IDC_TABLETYPE6))->GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_COLOR_11)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][0]);
		GetDlgItem(IDC_COLOR_12)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][0]);
		GetDlgItem(IDC_COLOR_13)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][0]);
		GetDlgItem(IDC_COLOR_14)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][0]);
		GetDlgItem(IDC_COLOR_15)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][0]);

		GetDlgItem(IDC_COLOR_21)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][1]);
		GetDlgItem(IDC_COLOR_22)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][1]);
		GetDlgItem(IDC_COLOR_23)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][1]);
		GetDlgItem(IDC_COLOR_24)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][1]);
		GetDlgItem(IDC_COLOR_25)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][1]);
		
		GetDlgItem(IDC_COLOR_31)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][2]);
		GetDlgItem(IDC_COLOR_32)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][2]);
		GetDlgItem(IDC_COLOR_33)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][2]);
		GetDlgItem(IDC_COLOR_34)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][2]);
		GetDlgItem(IDC_COLOR_35)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][2]);
		
		GetDlgItem(IDC_COLOR_41)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][3]);
		GetDlgItem(IDC_COLOR_42)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][3]);
		GetDlgItem(IDC_COLOR_43)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][3]);
		GetDlgItem(IDC_COLOR_44)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][3]);
		GetDlgItem(IDC_COLOR_45)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][3]);

		GetDlgItem(IDC_COLOR_51)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][4]);
		GetDlgItem(IDC_COLOR_52)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][4]);
		GetDlgItem(IDC_COLOR_53)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][4]);
		GetDlgItem(IDC_COLOR_54)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][4]);
		GetDlgItem(IDC_COLOR_55)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][4]);

		GetDlgItem(IDC_COLOR_61)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][5]);
		GetDlgItem(IDC_COLOR_62)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][5]);
		GetDlgItem(IDC_COLOR_63)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][5]);
		GetDlgItem(IDC_COLOR_64)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][5]);
		GetDlgItem(IDC_COLOR_65)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][5]);

		GetDlgItem(IDC_COLOR_71)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][6]);
		GetDlgItem(IDC_COLOR_72)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][6]);
		GetDlgItem(IDC_COLOR_73)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][6]);
		GetDlgItem(IDC_COLOR_74)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][6]);
		GetDlgItem(IDC_COLOR_75)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][6]);

		GetDlgItem(IDC_COLOR_81)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][7]);
		GetDlgItem(IDC_COLOR_82)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][7]);
		GetDlgItem(IDC_COLOR_83)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][7]);
		GetDlgItem(IDC_COLOR_84)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][7]);
		GetDlgItem(IDC_COLOR_85)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][7]);

		GetDlgItem(IDC_COLOR_91)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[nIndex][8]);
		GetDlgItem(IDC_COLOR_92)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[8][8]);
		GetDlgItem(IDC_COLOR_93)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[9][8]);
		GetDlgItem(IDC_COLOR_94)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[10][8]);
		GetDlgItem(IDC_COLOR_95)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[0].crColors[11][8]);
	
	}else if(((CButton*)GetDlgItem(IDC_TABLETYPE9))->GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_COLOR_11)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][0]);
		GetDlgItem(IDC_COLOR_12)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][0]);
		GetDlgItem(IDC_COLOR_13)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][0]);
		GetDlgItem(IDC_COLOR_14)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][0]);
		GetDlgItem(IDC_COLOR_15)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][0]);

		GetDlgItem(IDC_COLOR_21)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][1]);
		GetDlgItem(IDC_COLOR_22)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][1]);
		GetDlgItem(IDC_COLOR_23)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][1]);
		GetDlgItem(IDC_COLOR_24)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][1]);
		GetDlgItem(IDC_COLOR_25)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][1]);

		GetDlgItem(IDC_COLOR_31)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][2]);
		GetDlgItem(IDC_COLOR_32)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][2]);
		GetDlgItem(IDC_COLOR_33)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][2]);
		GetDlgItem(IDC_COLOR_34)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][2]);
		GetDlgItem(IDC_COLOR_35)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][2]);

		GetDlgItem(IDC_COLOR_41)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][3]);
		GetDlgItem(IDC_COLOR_42)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][3]);
		GetDlgItem(IDC_COLOR_43)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][3]);
		GetDlgItem(IDC_COLOR_44)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][3]);
		GetDlgItem(IDC_COLOR_45)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][3]);

		GetDlgItem(IDC_COLOR_51)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][4]);
		GetDlgItem(IDC_COLOR_52)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][4]);
		GetDlgItem(IDC_COLOR_53)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][4]);
		GetDlgItem(IDC_COLOR_54)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][4]);
		GetDlgItem(IDC_COLOR_55)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][4]);

		GetDlgItem(IDC_COLOR_61)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][5]);
		GetDlgItem(IDC_COLOR_62)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][5]);
		GetDlgItem(IDC_COLOR_63)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][5]);
		GetDlgItem(IDC_COLOR_64)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][5]);
		GetDlgItem(IDC_COLOR_65)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][5]);

		GetDlgItem(IDC_COLOR_71)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][6]);
		GetDlgItem(IDC_COLOR_72)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][6]);
		GetDlgItem(IDC_COLOR_73)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][6]);
		GetDlgItem(IDC_COLOR_74)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][6]);
		GetDlgItem(IDC_COLOR_75)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][6]);

		GetDlgItem(IDC_COLOR_81)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][7]);
		GetDlgItem(IDC_COLOR_82)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][7]);
		GetDlgItem(IDC_COLOR_83)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][7]);
		GetDlgItem(IDC_COLOR_84)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][7]);
		GetDlgItem(IDC_COLOR_85)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][7]);

		GetDlgItem(IDC_COLOR_91)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[nIndex][8]);
		GetDlgItem(IDC_COLOR_92)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[8][8]);
		GetDlgItem(IDC_COLOR_93)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[9][8]);
		GetDlgItem(IDC_COLOR_94)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[10][8]);
		GetDlgItem(IDC_COLOR_95)->GetDC()->FillSolidRect(1, 1, 19, 19, colorsetting->colorstruct[1].crColors[11][8]);
	}
	//delete brush;
}

void CColorDlg::OnBnClickedTabletype6()
{
	Invalidate(TRUE);
	nType = 0;
	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[0].x, colorsetting->colorstruct[0].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[1].x, colorsetting->colorstruct[0].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[2].x, colorsetting->colorstruct[0].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[3].x, colorsetting->colorstruct[0].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[4].x, colorsetting->colorstruct[0].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptPoint[5].x, colorsetting->colorstruct[0].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_POS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[0].x, colorsetting->colorstruct[0].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[1].x, colorsetting->colorstruct[0].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[2].x, colorsetting->colorstruct[0].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[3].x, colorsetting->colorstruct[0].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[4].x, colorsetting->colorstruct[0].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptSeatPoint[5].x, colorsetting->colorstruct[0].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[0].x, colorsetting->colorstruct[0].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[1].x, colorsetting->colorstruct[0].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[2].x, colorsetting->colorstruct[0].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[3].x, colorsetting->colorstruct[0].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[4].x, colorsetting->colorstruct[0].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[0].ptEmptyPoint[5].x, colorsetting->colorstruct[0].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos);
	strcpy(szPos, "");
	GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
}

void CColorDlg::OnBnClickedTabletype9()
{
	Invalidate(TRUE);
	nType = 1;
	char szPos[256];
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[0].x, colorsetting->colorstruct[1].ptPoint[0].y);
	GetDlgItem(IDC_POS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[1].x, colorsetting->colorstruct[1].ptPoint[1].y);
	GetDlgItem(IDC_POS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[2].x, colorsetting->colorstruct[1].ptPoint[2].y);
	GetDlgItem(IDC_POS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[3].x, colorsetting->colorstruct[1].ptPoint[3].y);
	GetDlgItem(IDC_POS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[4].x, colorsetting->colorstruct[1].ptPoint[4].y);
	GetDlgItem(IDC_POS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[5].x, colorsetting->colorstruct[1].ptPoint[5].y);
	GetDlgItem(IDC_POS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[6].x, colorsetting->colorstruct[1].ptPoint[6].y);
	GetDlgItem(IDC_POS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[7].x, colorsetting->colorstruct[1].ptPoint[7].y);
	GetDlgItem(IDC_POS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptPoint[8].x, colorsetting->colorstruct[1].ptPoint[8].y);
	GetDlgItem(IDC_POS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[0].x, colorsetting->colorstruct[1].ptSeatPoint[0].y);
	GetDlgItem(IDC_SEATPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[1].x, colorsetting->colorstruct[1].ptSeatPoint[1].y);
	GetDlgItem(IDC_SEATPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[2].x, colorsetting->colorstruct[1].ptSeatPoint[2].y);
	GetDlgItem(IDC_SEATPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[3].x, colorsetting->colorstruct[1].ptSeatPoint[3].y);
	GetDlgItem(IDC_SEATPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[4].x, colorsetting->colorstruct[1].ptSeatPoint[4].y);
	GetDlgItem(IDC_SEATPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[5].x, colorsetting->colorstruct[1].ptSeatPoint[5].y);
	GetDlgItem(IDC_SEATPOS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[6].x, colorsetting->colorstruct[1].ptSeatPoint[6].y);
	GetDlgItem(IDC_SEATPOS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[7].x, colorsetting->colorstruct[1].ptSeatPoint[7].y);
	GetDlgItem(IDC_SEATPOS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptSeatPoint[8].x, colorsetting->colorstruct[1].ptSeatPoint[8].y);
	GetDlgItem(IDC_SEATPOS9)->SetWindowText(szPos);

	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[0].x, colorsetting->colorstruct[1].ptEmptyPoint[0].y);
	GetDlgItem(IDC_EMPTYPOS1)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[1].x, colorsetting->colorstruct[1].ptEmptyPoint[1].y);
	GetDlgItem(IDC_EMPTYPOS2)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[2].x, colorsetting->colorstruct[1].ptEmptyPoint[2].y);
	GetDlgItem(IDC_EMPTYPOS3)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[3].x, colorsetting->colorstruct[1].ptEmptyPoint[3].y);
	GetDlgItem(IDC_EMPTYPOS4)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[4].x, colorsetting->colorstruct[1].ptEmptyPoint[4].y);
	GetDlgItem(IDC_EMPTYPOS5)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[5].x, colorsetting->colorstruct[1].ptEmptyPoint[5].y);
	GetDlgItem(IDC_EMPTYPOS6)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[6].x, colorsetting->colorstruct[1].ptEmptyPoint[6].y);
	GetDlgItem(IDC_EMPTYPOS7)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[7].x, colorsetting->colorstruct[1].ptEmptyPoint[7].y);
	GetDlgItem(IDC_EMPTYPOS8)->SetWindowText(szPos);
	sprintf(szPos, "%d, %d", colorsetting->colorstruct[1].ptEmptyPoint[8].x, colorsetting->colorstruct[1].ptEmptyPoint[8].y);
	GetDlgItem(IDC_EMPTYPOS9)->SetWindowText(szPos);
}

void CColorDlg::OnBnClickedRefresh1()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS1))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[0]), 0);
}

void CColorDlg::OnBnClickedRefresh2()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS2))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[1]), 0);
}

void CColorDlg::OnBnClickedRefresh3()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS3))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[2]), 0);
}

void CColorDlg::OnBnClickedRefresh4()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS4))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[3]), 0);
}

void CColorDlg::OnBnClickedRefresh5()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS5))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[4]), 0);
}

void CColorDlg::OnBnClickedRefresh6()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS6))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[5]), 0);
}

void CColorDlg::OnBnClickedRefresh7()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS7))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[6]), 0);
}

void CColorDlg::OnBnClickedRefresh8()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS8))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[7]), 0);
}

void CColorDlg::OnBnClickedRefresh9()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYERPOS9))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[8]), 0);
}

void CColorDlg::OnCbnSelchangeCombo1()
{
	Invalidate(TRUE);
}

void CColorDlg::ClearSelection(void)
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
}

void CColorDlg::OnBnClickedPlayerpos1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[0]), 1);
}

void CColorDlg::OnBnClickedPlayerpos2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[1]), 1);
}

void CColorDlg::OnBnClickedPlayerpos3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[2]), 1);
}

void CColorDlg::OnBnClickedPlayerpos4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[3]), 1);
}

void CColorDlg::OnBnClickedPlayerpos5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[4]), 1);
}

void CColorDlg::OnBnClickedPlayerpos6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[5]), 1);
}

void CColorDlg::OnBnClickedPlayerpos7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[6]), 1);
}

void CColorDlg::OnBnClickedPlayerpos8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[7]), 1);
}

void CColorDlg::OnBnClickedPlayerpos9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SEATPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptSeatPoint[8]), 1);
}

void CColorDlg::OnBnClickedChkjoinpos()
{
	if(((CButton*)GetDlgItem(IDC_CHKJOINPOS))->GetCheck() == BST_CHECKED)
	{
		if(imagedlg != NULL)
			::SendMessage(imagedlg->m_hWnd, WM_JOINPOSITION, 0, 0);
	}
}

void CColorDlg::OnBnClickedPlayer1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[0]), 1);
}

void CColorDlg::OnBnClickedPlayer2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[1]), 1);
}

void CColorDlg::OnBnClickedPlayer3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[2]), 1);
}

void CColorDlg::OnBnClickedPlayer4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[3]), 1);
}

void CColorDlg::OnBnClickedPlayer5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[4]), 1);
}

void CColorDlg::OnBnClickedPlayer6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[5]), 1);
}

void CColorDlg::OnBnClickedPlayer7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[6]), 1);
}

void CColorDlg::OnBnClickedPlayer8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[7]), 1);
}

void CColorDlg::OnBnClickedPlayer9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[8]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos1()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[0]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos2()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[1]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos3()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[2]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos4()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[3]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos5()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[4]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos6()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[5]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos7()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[6]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos8()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[7]), 1);
}

void CColorDlg::OnBnClickedEmptyplayerpos9()
{
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_EMPTYPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptEmptyPoint[8]), 1);
}

void CColorDlg::OnBnClickedRefresh10()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER1))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[0]), 0);
}

void CColorDlg::OnBnClickedRefresh11()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER2))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[1]), 0);
}

void CColorDlg::OnBnClickedRefresh12()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER3))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[2]), 0);
}

void CColorDlg::OnBnClickedRefresh13()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER4))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[3]), 0);
}

void CColorDlg::OnBnClickedRefresh14()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER5))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[4]), 0);
}

void CColorDlg::OnBnClickedRefresh15()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER6))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[5]), 0);
}

void CColorDlg::OnBnClickedRefresh16()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER7))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[6]), 0);
}

void CColorDlg::OnBnClickedRefresh17()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER8))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[7]), 0);
}

void CColorDlg::OnBnClickedRefresh18()
{
	ClearSelection();
	((CButton*)GetDlgItem(IDC_PLAYER9))->SetCheck(BST_CHECKED);
	if(imagedlg != NULL)
		::SendMessage(imagedlg->m_hWnd, WM_SENDPOSITION, (WPARAM)&(colorsetting->colorstruct[nType].ptPoint[8]), 0);
}
