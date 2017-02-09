// TempDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poker.h"
#include "TempDlg.h"


// CTempDlg dialog

IMPLEMENT_DYNAMIC(CTempDlg, CDialog)

CTempDlg::CTempDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTempDlg::IDD, pParent)
{

}

CTempDlg::~CTempDlg()
{
}

void CTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTempDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CTempDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CTempDlg::OnBnClickedOk)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CTempDlg message handlers

void CTempDlg::OnBnClickedCancel()
{

}

void CTempDlg::OnBnClickedOk()
{

}

void CTempDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	RECT rect;
	GetWindowRect(&rect);
	if(prect)
	{
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		*(PRECT)prect= rect;
	}
}

void CTempDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanging(lpwndpos);

	
}

BOOL CTempDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	prect = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
