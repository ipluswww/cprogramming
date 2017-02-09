#pragma once
#include "afxcmn.h"
#include "TempDlg.h"

// CLayoutDlg dialog
typedef struct _LAYOUTSETTING
{
	int nStackNumber;
	RECT activerect[10];
	RECT observationrect;
}LAYOUTSETTING, *PLAYOUTSETTING;

class CLayoutDlg : public CDialog
{
	DECLARE_DYNAMIC(CLayoutDlg)

public:
	PLAYOUTSETTING playoutsetting;
	CTempDlg* ptempdlg[10];
	int nNumber;
	CLayoutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLayoutDlg();

// Dialog Data
	enum { IDD = IDD_LAYOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSpinButtonCtrl m_spinctrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};
