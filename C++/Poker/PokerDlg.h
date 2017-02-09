// PokerDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "ColorDlg.h"
#include "LayoutDlg.h"
#include "afxwin.h"

// CPokerDlg dialog
#define SITE_COUNT	3

typedef struct _POKERSETTING
{
	BOOL bMoveToSlot;
	BOOL bTakeSeat;
	BOOL bEnableSound;
	BOOL bShowMessage;
	BOOL bCloseFilledTable;
	BOOL bJoinWaitingList;
	WORD wHotKey;
	WORD wModifier;
}POKERSETTING, *PPOKERSETTING;

typedef struct _HWNDSTRUCT
{
	HWND hwnd;
	int nTableSite;
	BOOL bTableType;
	BOOL bSeated;
	int nEmptySeat;
	int nSeat[9]; // 0 : good, 1 : bad, 2 : unknown, 3 : empty
}HWNDSTRUCT, *PHWNDSTRUCT;

class CPokerDlg : public CDialog
{
// Construction
public:
	DWORD dwWPTPokerPID, dwLAPokerPID;
	HWND hwndPlay;
	int nSiteIndex;
	int nIndex4Slot[SITE_COUNT];
	LAYOUTSETTING layoutsetting[SITE_COUNT];
	PLAYERSETTING playersetting[SITE_COUNT][9];
	POKERSETTING pokersetting[SITE_COUNT];
	COLORSETTING colorsetting[SITE_COUNT];

	CPokerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CHotKeyCtrl m_hotkeyctrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_colorlist;
	CListCtrl m_hwndlist;
	afx_msg void OnNMCustomdrawColorlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCapturecolor();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLayout();
	afx_msg void OnEnChangeLabelname();
	afx_msg void OnNMClickColorlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkbad();
	afx_msg void OnBnClickedChkgood();
	
	int SaveSetting(void);
	int LoadSetting(void);
	
	void AddItem(HWND hwnd, int nTableSite);
	void UpdateItem(HWND hwnd, int nIndex);
	int RemoveItem(int nIndex, BOOL bClear);
	void ChangeStatus(int nIndex);

	static DWORD WINAPI TimerThread( LPVOID lpParam );
	int AddLog(char* pszLog);

	afx_msg void OnNMDblclkHwndlist(NMHDR *pNMHDR, LRESULT *pResult);

	CString m_logs;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnNMRClickHwndlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedHwndlist(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_sitelist;
	afx_msg void OnCbnSelchangeCmbsite();
};
