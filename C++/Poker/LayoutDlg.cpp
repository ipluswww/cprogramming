// LayoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poker.h"
#include "LayoutDlg.h"


// CLayoutDlg dialog

IMPLEMENT_DYNAMIC(CLayoutDlg, CDialog)

CLayoutDlg::CLayoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayoutDlg::IDD, pParent)
{

}

CLayoutDlg::~CLayoutDlg()
{
}

void CLayoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN, m_spinctrl);
}


BEGIN_MESSAGE_MAP(CLayoutDlg, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CLayoutDlg::OnDeltaposSpin)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CLayoutDlg message handlers

BOOL CLayoutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_spinctrl.SetRange32(1, 10);
	m_spinctrl.SetPos32(1);
	nNumber = 1;
	GetDlgItem(IDC_NUMBER)->SetWindowText("1");
	
	m_spinctrl.SetPos32(playoutsetting->nStackNumber);
	nNumber = playoutsetting->nStackNumber;
	char szNumber[256];
	sprintf(szNumber, "%d", nNumber);
	GetDlgItem(IDC_NUMBER)->SetWindowText(szNumber);

	SetWindowPos(NULL, playoutsetting->observationrect.left, playoutsetting->observationrect.top, playoutsetting->observationrect.right, playoutsetting->observationrect.bottom, SWP_SHOWWINDOW);
	
	for(int i = 0; i < playoutsetting->nStackNumber; i++)
	{
		ptempdlg[i] = new CTempDlg;
		ptempdlg[i]->Create(IDD_TEMPLATE_DIALOG, this);
		ptempdlg[i]->SetWindowPos(NULL, 
			playoutsetting->activerect[i].left, 
			playoutsetting->activerect[i].top, 
			playoutsetting->activerect[i].right, 
			playoutsetting->activerect[i].bottom,
			SWP_SHOWWINDOW);
		ptempdlg[i]->prect = &playoutsetting->activerect[i];
		char szText[256];
		sprintf(szText, "Slot %d", i + 1);
		ptempdlg[i]->SetWindowText(szText);
		ptempdlg[i]->ShowWindow(SW_SHOW);
	}
	return TRUE;
}

void CLayoutDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if(pNMUpDown->iDelta > 0)
		nNumber = m_spinctrl.GetPos32() + 1;
	else
		nNumber = m_spinctrl.GetPos32() - 1;
	nNumber = min(max(nNumber, 1), 10);

	char szText[10];
	sprintf(szText, "%d", nNumber/*pNMUpDown->iPos + pNMUpDown->iDelta*/);
	GetDlgItem(IDC_NUMBER)->SetWindowText(szText);

	if(nNumber < playoutsetting->nStackNumber)
	{
		::DestroyWindow(ptempdlg[playoutsetting->nStackNumber - 1]->m_hWnd);
		playoutsetting->nStackNumber = nNumber;
	}
	else if(nNumber > playoutsetting->nStackNumber)
	{
		playoutsetting->activerect[playoutsetting->nStackNumber].left = 0;
		playoutsetting->activerect[playoutsetting->nStackNumber].top = 0;
		playoutsetting->activerect[playoutsetting->nStackNumber].right = 491;
		playoutsetting->activerect[playoutsetting->nStackNumber].bottom = 365;
		
		ptempdlg[playoutsetting->nStackNumber] = new CTempDlg;
		ptempdlg[playoutsetting->nStackNumber]->Create(IDD_TEMPLATE_DIALOG, this);
		ptempdlg[playoutsetting->nStackNumber]->SetWindowPos(NULL, 
			playoutsetting->activerect[playoutsetting->nStackNumber].left, 
			playoutsetting->activerect[playoutsetting->nStackNumber].top, 
			playoutsetting->activerect[playoutsetting->nStackNumber].right, 
			playoutsetting->activerect[playoutsetting->nStackNumber].bottom,
			SWP_SHOWWINDOW);
		ptempdlg[playoutsetting->nStackNumber]->prect = &playoutsetting->activerect[playoutsetting->nStackNumber];
		char szText[256];
		sprintf(szText, "Slot %d", playoutsetting->nStackNumber + 1);
		ptempdlg[playoutsetting->nStackNumber]->SetWindowText(szText);
		ptempdlg[playoutsetting->nStackNumber]->ShowWindow(SW_SHOW);
		playoutsetting->nStackNumber = nNumber;
	}
}

void CLayoutDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	RECT rect;
	GetWindowRect(&rect);
	playoutsetting->observationrect.left = rect.left;
	playoutsetting->observationrect.top = rect.top;
	playoutsetting->observationrect.right = rect.right - rect.left;
	playoutsetting->observationrect.bottom = rect.bottom - rect.top;
}
