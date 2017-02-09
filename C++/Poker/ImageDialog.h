#pragma once

typedef struct _COLORSTRUCT
{
	HWND hwnd;
	COLORREF crColors[12][9];
	int nColorStatus[9];
	POINT ptPoint[9];
	POINT ptSeatPoint[9];
	POINT ptEmptyPoint[9];
} COLORSTRUCT, *PCOLORSTRUCT;

typedef struct _COLORSETTING
{
	COLORSTRUCT colorstruct[2];
	POINT ptJoin;
}COLORSETTING, *PCOLORSETTING;

#define WM_SENDCOLOR		WM_USER + 0x321
#define WM_SENDCOLOR1		WM_USER + 0x321
#define WM_SENDPOSITION		WM_USER + 0x317
#define WM_SEATPOSITION		WM_USER + 0x821
#define WM_JOINPOSITION		WM_USER + 0x615
#define WM_EMPTYPOSITION	WM_USER + 0x1224

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
