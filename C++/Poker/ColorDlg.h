#pragma once
#include "afxwin.h"
#include "ImageDialog.h"
#include "ColorPickerCB.h"

// CColorDlg dialog
typedef struct _PLAYERSETTING
{
	char szPlayerName[256];
	BOOL bBadOrGood;
}PLAYERSETTING, *PPLAYERSETTING;

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	int nColorCount;
	DWORD dwWPTPokerPID, dwLAPokerPID;
	PPLAYERSETTING pplayersetting;
	COLORREF* pcrColor;
	int nType;
	CImageDialog* imagedlg;	
	PCOLORSETTING colorsetting;

	CColorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorDlg();

// Dialog Data
	enum { IDD = IDD_CAPTURECOLOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_tablelist;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnClose();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	void RefreshColor(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedTabletype6();
	afx_msg void OnBnClickedTabletype9();
	afx_msg void OnBnClickedRefresh1();
	afx_msg void OnBnClickedRefresh2();
	afx_msg void OnBnClickedRefresh3();
	afx_msg void OnBnClickedRefresh4();
	afx_msg void OnBnClickedRefresh5();
	afx_msg void OnBnClickedRefresh6();
	afx_msg void OnBnClickedRefresh7();
	afx_msg void OnBnClickedRefresh8();
	afx_msg void OnBnClickedRefresh9();
	CColorPickerCB m_colorlist;
	afx_msg void OnCbnSelchangeCombo1();
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
	afx_msg void OnBnClickedChkjoinpos();
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
	afx_msg void OnBnClickedRefresh10();
	afx_msg void OnBnClickedRefresh11();
	afx_msg void OnBnClickedRefresh12();
	afx_msg void OnBnClickedRefresh13();
	afx_msg void OnBnClickedRefresh14();
	afx_msg void OnBnClickedRefresh15();
	afx_msg void OnBnClickedRefresh16();
	afx_msg void OnBnClickedRefresh17();
	afx_msg void OnBnClickedRefresh18();
};
