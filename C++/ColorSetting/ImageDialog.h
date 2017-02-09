#pragma once

#define WM_SENDCOLOR			WM_USER + 0x321
#define WM_SENDCOLOR_SITTINGOUT	WM_USER + 0x322
#define WM_SENDCOLOR_ACTIVATE	WM_USER + 0x323

#define WM_SENDPOSITION			WM_USER + 0x317
#define WM_SEATPOSITION			WM_USER + 0x1117
#define WM_EMPTYPOSITION		WM_USER + 0x1220
#define WM_SITTINGOUTPOSITION	WM_USER + 0x615
#define WM_ACTIVEPOSITION		WM_USER + 0x1004

// CImageDialog dialog

class CImageDialog : public CDialog
{
	DECLARE_DYNAMIC(CImageDialog)

public:
	int nMode;
	BOOL bStart;
	HWND hwnd;
	HWND hwndSend;
	POINT ptOrg;
	COLORREF crOrg[3];
	int nIndex;

	CImageDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageDialog();

// Dialog Data
	enum { IDD = IDD_IMAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
