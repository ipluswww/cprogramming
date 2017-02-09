#pragma once


// CTempDlg dialog

class CTempDlg : public CDialog
{
	DECLARE_DYNAMIC(CTempDlg)

public:
	PRECT prect;
	CTempDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTempDlg();

// Dialog Data
	enum { IDD = IDD_TEMPLATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual BOOL OnInitDialog();
};
