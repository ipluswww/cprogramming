// ColorSettingDlg.h : header file
//

#pragma once

#include "ImageDialog.h"

typedef struct _COLORSTRUCT
{
	HWND hwnd;
	COLORREF crColors[5][9];
	int nColorStatus[9];
	POINT ptPoint[9];
	POINT ptSeatPoint[9];
	POINT ptEmptyPoint[9];
} COLORSTRUCT, *PCOLORSTRUCT;

typedef struct _COLORSETTING
{
	COLORSTRUCT colorstruct[3];
	POINT ptSittingOutPoint;
	POINT ptActivePoint;
	COLORREF crSO[2];
	COLORREF crActive[2];
}COLORSETTING, *PCOLORSETTING;

// CColorSettingDlg dialog
class CColorSettingDlg : public CDialog
{
// Construction
public:
	int nColorCount;
	DWORD dwWPTPokerPID, dwLAPokerPID;
	COLORREF* pcrColor;
	int nType;
	CImageDialog* imagedlg;	
	COLORSETTING colorsetting;
	CListBox m_tablelist;

	CColorSettingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COLORSETTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void LoadSetting(void);
	void SaveSetting(void);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedTabletype6();
	afx_msg void OnBnClickedTabletype9();
	afx_msg void OnBnClickedTabletype2();
	afx_msg void OnBnClickedRefresh1();
	afx_msg void OnBnClickedRefresh2();
	afx_msg void OnBnClickedRefresh3();
	afx_msg void OnBnClickedRefresh4();
	afx_msg void OnBnClickedRefresh5();
	afx_msg void OnBnClickedRefresh6();
	afx_msg void OnBnClickedRefresh7();
	afx_msg void OnBnClickedRefresh8();
	afx_msg void OnBnClickedRefresh9();
	afx_msg void OnBnClickedRefresh10();
	afx_msg void OnBnClickedRefresh11();
	void ClearSelection(void);
	afx_msg void OnBnClickedPlayerpos1();
	afx_msg void OnBnClickedPlayerpos2();
	afx_msg void OnBnClickedPlayerpos3();
	afx_msg void OnBnClickedPlayerpos4();
	afx_msg void OnBnClickedPlayerpos5();
	afx_msg void OnBnClickedPlayerpos6();
	afx_msg void OnBnClickedPlayerpos7();
	afx_msg void OnBnClickedPlayerpos8();
	afx_msg void OnBnClickedPlayerpos9();
	afx_msg void OnBnClickedPlayer1();
	afx_msg void OnBnClickedPlayer2();
	afx_msg void OnBnClickedPlayer3();
	afx_msg void OnBnClickedPlayer4();
	afx_msg void OnBnClickedPlayer5();
	afx_msg void OnBnClickedPlayer6();
	afx_msg void OnBnClickedPlayer7();
	afx_msg void OnBnClickedPlayer8();
	afx_msg void OnBnClickedPlayer9();
	afx_msg void OnBnClickedEmptyplayerpos1();
	afx_msg void OnBnClickedEmptyplayerpos2();
	afx_msg void OnBnClickedEmptyplayerpos3();
	afx_msg void OnBnClickedEmptyplayerpos4();
	afx_msg void OnBnClickedEmptyplayerpos5();
	afx_msg void OnBnClickedEmptyplayerpos6();
	afx_msg void OnBnClickedEmptyplayerpos7();
	afx_msg void OnBnClickedEmptyplayerpos8();
	afx_msg void OnBnClickedEmptyplayerpos9();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedChkSittingOut();
	afx_msg void OnBnClickedChkActive();
};
