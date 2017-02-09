// LicenseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poker.h"
#include "LicenseDlg.h"
#include "PokerDlg.h"

// CLicenseDlg dialog

IMPLEMENT_DYNAMIC(CLicenseDlg, CDialog)

CLicenseDlg::CLicenseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseDlg::IDD, pParent)
{

}

CLicenseDlg::~CLicenseDlg()
{
}

void CLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLicenseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLicenseDlg message handlers

void CLicenseDlg::OnBnClickedOk()
{
	BYTE szSrc[256], szDst[256], szTarget[256];
	char szTemp[256];

	GetDlgItem(IDC_HWDID)->GetWindowText((LPSTR)szSrc, 256);
	
	LONG lSum = 0;
	int nLen = strlen((LPSTR)szSrc);

	strcpy((LPSTR)szDst, "ABCD");

	for(int i = 0; i < nLen; i++)
	{
		szSrc[i] = szSrc[i] * szSrc[(i + 1) % nLen] + szSrc[(i + 2) % nLen] + szSrc[(i + 3) % nLen];
		lSum += (szSrc[i] + 1);
		sprintf(szTemp, "%02X", szSrc[i]);
		strcat((LPSTR)szDst, szTemp);
	}

	sprintf(szTemp, "%02X", lSum % 0xFF);
	szDst[0] = szTemp[0];
	szDst[1] = szTemp[1];

	GetDlgItem(IDC_LICENSEKEY)->GetWindowText((LPSTR)szTarget, 256);

	int j = 0;
	for(; j < strlen((LPSTR)szTarget); j++)
		if((szTarget[j] == szDst[j]) || j == 2 || j == 3)
		{
		}
		else
			break;

	if(j == strlen((LPSTR)szTarget))
	{
		HKEY hKey;
		DWORD dwLen;
		RegOpenKeyA(HKEY_LOCAL_MACHINE, LPCSTR("SOFTWARE\\AutoPoker"), &hKey);

		dwLen = 256;
		RegSetValueExA(hKey, LPCSTR("SerialKey"), 0, REG_SZ, (const unsigned char*)szTarget, 256);
		//RegQueryValueEx(hKey, "MachineGuid", NULL, &dwType, (LPBYTE)szMachineID, &dwLen);

		RegCloseKey(hKey);

		CPokerDlg dlg;
		ShowWindow(SW_HIDE);
		INT_PTR nResponse = dlg.DoModal();
		CDialog::OnCancel();
	}
	else
		MessageBox("Invalid License");
}

BOOL CLicenseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	HKEY hKey;
	DWORD dwLen;
	RegOpenKeyA(HKEY_LOCAL_MACHINE, LPCSTR("SOFTWARE\\Microsoft\\Cryptography"), &hKey);
	
	dwLen = 256;
	//RegSetValueExA(hKey, LPCSTR("LoadAppInit_DLLs"), 0, REG_DWORD, (const unsigned char*)(&dwValue), 4);
	DWORD dwType = REG_SZ;
	char szMachineID[256];
	RegQueryValueEx(hKey, "MachineGuid", NULL, &dwType, (LPBYTE)szMachineID, &dwLen);

	RegCloseKey(hKey);

	RegCreateKeyA(HKEY_LOCAL_MACHINE, LPCSTR("SOFTWARE\\AutoPoker"), &hKey);

	dwLen = 256;
	dwType = REG_SZ;
	char szSerialKey[256];
	strcpy(szSerialKey, "");
	RegQueryValueEx(hKey, "SerialKey", NULL, &dwType, (LPBYTE)szSerialKey, &dwLen);

	RegCloseKey(hKey);

	char *p;

	while ((p = strchr(szMachineID,'-')) != NULL)
		strcpy(p, p+1);
	GetDlgItem(IDC_HWDID)->SetWindowText(szMachineID);
	GetDlgItem(IDC_LICENSEKEY)->SetWindowText(szSerialKey);
	
	BYTE szSrc[256], szDst[256], szTarget[256];
	char szTemp[256];

	GetDlgItem(IDC_HWDID)->GetWindowText((LPSTR)szSrc, 256);

	LONG lSum = 0;
	int nLen = strlen((LPSTR)szSrc);

	strcpy((LPSTR)szDst, "ABCD");

	for(int i = 0; i < nLen; i++)
	{
		szSrc[i] = szSrc[i] * szSrc[(i + 1) % nLen] + szSrc[(i + 2) % nLen] + szSrc[(i + 3) % nLen];
		lSum += (szSrc[i] + 1);
		sprintf(szTemp, "%02X", szSrc[i]);
		strcat((LPSTR)szDst, szTemp);
	}

	sprintf(szTemp, "%02X", lSum % 0xFF);
	szDst[0] = szTemp[0];
	szDst[1] = szTemp[1];

	GetDlgItem(IDC_LICENSEKEY)->GetWindowText((LPSTR)szTarget, 256);

	int j = 0;
	for(; j < strlen((LPSTR)szTarget); j++)
		if((szTarget[j] == szDst[j]) || j == 2 || j == 3)
		{
		}
		else
			break;

	if(j == strlen((LPSTR)szTarget) && strlen((LPSTR)szTarget) != 0)
	{
		CPokerDlg dlg;
		ShowWindow(SW_HIDE);
		INT_PTR nResponse = dlg.DoModal();
		CDialog::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
