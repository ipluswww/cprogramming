#pragma once


// CLicenseDlg dialog

class CLicenseDlg : public CDialog
{
	DECLARE_DYNAMIC(CLicenseDlg)

public:
	CLicenseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLicenseDlg();

// Dialog Data
	enum { IDD = IDD_LICENSEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
