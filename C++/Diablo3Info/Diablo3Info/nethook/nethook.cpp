// nethook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#define WM_AUTOSTART		WM_USER + 0x321
#define WM_AUTOSTOP			WM_USER + 0x322

#define VALID_PTR(ptr)	(ptr != 0)
#define INVALID_PTR(ptr)	(ptr == 0)

//HANDLE hFlagEvent;
//BOOL bFlag = FALSE;
BOOL bStart = FALSE;
BOOL HookNetFunc();
HANDLE hProcess;
HWND hwndListener;
HWND hwndDiablo;

typedef struct _GOLDAUCTION
{
	CHAR szItemName[256];
	CHAR szDPS[20];
	CHAR szArmor[20];
	CHAR szBid[60];
	CHAR szBuyout[60];
	CHAR szTimeLeft[20];
	ULONG nDPSorArmor;
}GOLDAUCTION, *PGOLDAUCTION;

GOLDAUCTION auctionitem[11];

typedef struct _GEMS
{
	CHAR szGemName[50];
	CHAR szQuantity[20];
	CHAR szPricePerUnit[20];
	CHAR szTotalAmount[60];
}GEMS, *PGEMS;

GEMS gemsitem;

typedef struct _ITEMINFO
{
	CHAR szItemName[256]; // i.e : Dream Strike
	CHAR szRarity[80]; // i.e : Rare Ring
	CHAR szItemType[256]; // i.e : Finger(, Off-Hand)
	CHAR szMainPerformance[30]; // i.e : 1257.1
	CHAR szPerformance[256]; // i.e : 1401 - 1774 Damage
	CHAR szMagicFeature[2048]; // i.e : .........
	CHAR szAddedFeature[1024]; // i.e : +34 Dexterity
	CHAR szItemLevel[80]; // i.e : Item Level : 61
	CHAR szRequiredLevel[80]; // i.e : Required Level : 25
	CHAR szSellValue[80]; // i.e : Sell Value : 476
	CHAR szDurability[80]; // i.e : Durability 44/44
}ITEMINFO, *PITEMINFO;

ITEMINFO detailediteminfo;

ULONG nShowGems = 0;
ULONG nCount = 0;
ULONG nShowDetailedItemInfo = 0;

BOOL SendMessageToListener(DWORD dwBuffer, DWORD dwType);
BOOL bStarted = FALSE;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

DWORD orgWndProc;

DWORD HookThread(LPVOID lpv)
{
	HookNetFunc();
	
	Sleep(2000);
	hwndDiablo = NULL;
	while(hwndDiablo == NULL)
	{
		hwndDiablo = ::FindWindow("D3 Main Window Class", "Diablo III");
		Sleep(1000);
	}
	orgWndProc = (DWORD)SetWindowLong(hwndDiablo, GWL_WNDPROC, (LONG)WindowProc);
	while(TRUE)
	{
		hwndListener = FindWindow(NULL, "Diablo 3 Auction Data Scraper 1.0");
		Sleep(5000);
	}

	return 0;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	if( ul_reason_for_call == DLL_PROCESS_ATTACH || ul_reason_for_call == DLL_THREAD_ATTACH){
		char szFileName[256];

		GetModuleFileName(NULL, szFileName, 256);
		if(strstr(strupr(szFileName), "DIABLO III.EXE") != 0){
			
			if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
			{
				MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
				return FALSE;
			}

			if(bStarted)
				return TRUE;
//			hFlagEvent = CreateEvent(NULL, FALSE, FALSE, "DiabloFlagEvent");

			DWORD dwThreadID;
			HANDLE hThread = CreateThread(NULL, 
				0, 
				(LPTHREAD_START_ROUTINE)HookThread,
				0L, 
				STANDARD_RIGHTS_REQUIRED, 
			&dwThreadID);

			//return TRUE;
			bStarted = TRUE;
			return TRUE;
		}else 
			return FALSE;
	}
    return TRUE;
}

BYTE bHookCode[6] = {0xFF, 0x25, 0x90, 0x90, 0x90, 0x90};

ULONG addr = 0;
ULONG jmpNameAddr = 0;
ULONG jmpDPSAddr = 0;
ULONG jmpArmorAddr = 0;
ULONG jmpBidAddr = 0;
ULONG jmpBuyoutAddr = 0;
ULONG jmpTimeLeftAddr = 0;
ULONG jmpQuantityAddr = 0;
ULONG jmpPricePerUnitAddr = 0;
ULONG jmpTotalAmountAddr = 0;
ULONG jmpGemNameAddr = 0;
ULONG jmpDetailedItemInfoAddr = 0;


ULONG dwNameorgfunc;
ULONG dwDPSorgfunc;
ULONG dwArmororgfunc;
ULONG dwBidorgfunc;
ULONG dwBuyoutorgfunc;
ULONG dwTimeLeftorgfunc;
ULONG dwQuantityorgfunc;
ULONG dwPricePerUnitorgfunc;
ULONG dwTotalAmountorgfunc;
ULONG dwGemNameorgfunc;
ULONG dwDetailedItemInfoorgfunc;

DWORD dwBuffer;
// __declspec (naked) void MyPriceFunc ()
// {
// 	_asm mov dwBuffer, ecx;
// 
// 	_asm pushad;
// 
// 
// // 	if(dwBuffer)
// // 		SendMessageToListener(dwBuffer, 0);
// 
// 	_asm popad;
// 
// 	_asm
// 	{
// 		lea     ecx, [ebp-0x108];
// 	}
// 	
// 	_asm jmp     dwPriceorgfunc;
// }

__declspec (naked) void MyNameFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x24];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 1);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0x0C;
		mov     byte ptr [ebp-0x4], 1;
	}
	
	_asm jmp     dwNameorgfunc;
}

__declspec (naked) void MyDPSFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x34];
	_asm mov dwBuffer, eax;
	_asm pop eax;

	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 2);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0x1c;
		mov     byte ptr [ebp-0x4], 5
	}
	
	_asm jmp     dwDPSorgfunc;
}

__declspec (naked) void MyArmorFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x38];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 3);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0x14;
		mov     byte ptr [ebp-0x4], 0x4;
	}
	
	_asm jmp     dwArmororgfunc;
}

__declspec (naked) void MyBidFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x18];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 4);
	
	_asm popad;
	
	_asm
	{
		push    eax;
		lea     ecx, [ebp-0x840];
	}
	
	_asm jmp     dwBidorgfunc;
}

__declspec (naked) void MyBuyoutFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x24];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 5);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0xC;
		mov     byte ptr [ebp-0x4], 0x14;
	}
	
	_asm jmp     dwBuyoutorgfunc;
}

__declspec (naked) void MyTimeLeftFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x2C];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 6);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0x14;
		mov     byte ptr [ebp-0x4], 0x17;
	}
	
	_asm jmp     dwTimeLeftorgfunc;
}

__declspec (naked) void MyQuantityFunc ()
{
	_asm push eax;
	_asm mov eax, [esp + 0x3c];
	_asm mov dwBuffer, eax;
	_asm pop eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 7);
	
	_asm popad;
	
	_asm
	{
		add     esp, 0x18;
		mov     [ebp-0x04], 0;
	}
	
	_asm jmp     dwQuantityorgfunc;
}

__declspec (naked) void MyPricePerUnitFunc ()
{
	_asm mov dwBuffer, eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 8);
	
	_asm popad;
	
	_asm
	{
		mov     edx, [esi+0x84];
	}
	
	_asm jmp     dwPricePerUnitorgfunc;
}

__declspec (naked) void MyTotalAmountFunc ()
{
	_asm mov dwBuffer, eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 9);
	
	_asm popad;
	
	_asm
	{
		mov     edx, [esi+0x84];
	}
	
	_asm jmp     dwTotalAmountorgfunc;
}

__declspec (naked) void MyGemNameFunc ()
{
	_asm mov dwBuffer, eax;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer, 0);
	
	_asm popad;
	
	_asm
	{
		push    eax;
		mov     eax, [esi+0x84];
	}
	
	_asm jmp     dwGemNameorgfunc;
}

__declspec (naked) void MyDetailedItemInfoFunc ()
{
	_asm mov dwBuffer, esp;
	
	_asm pushad;
	
	
	if(dwBuffer)
		SendMessageToListener(dwBuffer + 0x40, 10);
	
	_asm popad;
	
	_asm
	{
		lea     ecx, [ebp-0x1E8];
	}
	
	_asm jmp     dwDetailedItemInfoorgfunc;
}

BOOL HookNetFunc()
{

	DWORD sizeCode;

	//Hooking setting Price
// 	DWORD dwnetfunc = (DWORD)0x00D188AA; 
// 	
// 
// 	jmpPriceAddr = (DWORD)MyPriceFunc;
// 	addr = (DWORD)&jmpPriceAddr;
// 	
// 	
// 	memcpy(&bHookCode[2], &addr, 4);
// 	
// 	
// 	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
// 	{
// 		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
// 		return FALSE;
// 	}
// 
// 	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
// 		return FALSE;
// 	
// 	dwPriceorgfunc = dwnetfunc + 6;

	//Hooking setting Item Name!
	DWORD dwnetfunc = (DWORD)0x00D774C0/*0x00D80ED2*//*0x00DBD722*//*0xDBE002*//*0x00DBDAD2*//*0x00DA6282*/; 
	
	
	jmpNameAddr = (DWORD)MyNameFunc;
	addr = (DWORD)&jmpNameAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}

	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwNameorgfunc = dwnetfunc + 7;

	//Hooking setting DPS
	dwnetfunc = (DWORD)0x00D777BD/*0x00D811BD*//*0x00DBDA0D*//*0x00DBE2ED*//*0x00DBDDBD*//*0x00DA656D*/; 
	
	
	jmpDPSAddr = (DWORD)MyDPSFunc;
	addr = (DWORD)&jmpDPSAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwDPSorgfunc = dwnetfunc + 7;


	//Hooking setting Armor
	dwnetfunc = (DWORD)0x00D77710/*0x00D81104*//*0x00DBD954*//*0x00DBE234*//*0xDBDD04*//*0x00DA64B4*/;	
	
	jmpArmorAddr = (DWORD)MyArmorFunc;
	addr = (DWORD)&jmpArmorAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwArmororgfunc = dwnetfunc + 7;

	//Hooking setting Bid
	dwnetfunc = (DWORD)0x00D7790B/*0x00D812D2*//*0x00DBDB22*//*0x00DBE402*//*0x00DBDED2*//*0x00DA6682*/;	
	
	jmpBidAddr = (DWORD)MyBidFunc;
	addr = (DWORD)&jmpBidAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwBidorgfunc = dwnetfunc + 7;
	
	
	//Hooking setting Buyout
	dwnetfunc = (DWORD)0x00D77A17/*0x00D813A0*//*0x00DBDBF0*//*0x00DBE4D0*//*0xDBDFA0*//*0x00DA6750*/;	
	
	jmpBuyoutAddr = (DWORD)MyBuyoutFunc;
	addr = (DWORD)&jmpBuyoutAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwBuyoutorgfunc = dwnetfunc + 7;

	//Hooking setting Time Left
	dwnetfunc = (DWORD)0x00D77B29/*0x00D814A9*//*0x00DBDCF9*//*0x00DBE5D9*//*0xDBE0A9*//*0x00DA6859*/;	
	
	jmpTimeLeftAddr = (DWORD)MyTimeLeftFunc;
	addr = (DWORD)&jmpTimeLeftAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwTimeLeftorgfunc = dwnetfunc + 7;
	
	//Hooking setting Quantity
	dwnetfunc = (DWORD)0x00D753AC/*0x00D7EEC6*//*0x00DBB6E1*/;	
	
	jmpQuantityAddr = (DWORD)MyQuantityFunc;
	addr = (DWORD)&jmpQuantityAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwQuantityorgfunc = dwnetfunc + 10;
	
	
	//Hooking setting PricePerUnit
	dwnetfunc = (DWORD)0x00D75434/*0x00D7EF4F*//*0x00DBB76A*/;	
	
	jmpPricePerUnitAddr = (DWORD)MyPricePerUnitFunc;
	addr = (DWORD)&jmpPricePerUnitAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwPricePerUnitorgfunc = dwnetfunc + 6;

	//Hooking setting TotalAmount
	dwnetfunc = (DWORD)0x00D754D6/*0x00D7EFF3*//*0x00DBB80E*/;	
	
	jmpTotalAmountAddr = (DWORD)MyTotalAmountFunc;
	addr = (DWORD)&jmpTotalAmountAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwTotalAmountorgfunc = dwnetfunc + 6;

	//Hooking setting GemName
	dwnetfunc = (DWORD)0x00BAFD3F/*0x00BFF545*//*0x00C1EAF5*/;	
	
	jmpGemNameAddr = (DWORD)MyGemNameFunc;
	addr = (DWORD)&jmpGemNameAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwGemNameorgfunc = dwnetfunc + 7;

	//Hooking Getting Item detailed infos
	dwnetfunc = (DWORD)0x00B6EC31/*0x00BCC0D2*//*0x00BECD12*/;	
	
	jmpDetailedItemInfoAddr = (DWORD)MyDetailedItemInfoFunc;
	addr = (DWORD)&jmpDetailedItemInfoAddr;
	
	
	memcpy(&bHookCode[2], &addr, 4);
	
	
	if((hProcess = OpenProcess(0x1F0FFF, FALSE, GetCurrentProcessId())) == NULL)
	{
		MessageBox(NULL, "You couldn't process handle. -> OpenProcess", "Attach_Error", MB_OK);
		return FALSE;
	}
	
	if(!WriteProcessMemory(hProcess, (LPVOID)dwnetfunc, bHookCode, 6, &sizeCode))
		return FALSE;
	
	dwDetailedItemInfoorgfunc = dwnetfunc + 6;

	return TRUE;
}

BOOL SendMessageToListener(DWORD dwBuffer, DWORD dwType)
{
// 	if(dwType == 0)//Price
// 	{
// 		char szText[30];
// 		sprintf(szText, "%d", *(DWORD*)(dwBuffer + 0xB8));
// 		strcpy(auctionitem[nCount].szBuyout, szText);
// 
// 		sprintf(szText, "%d", *(DWORD*)(dwBuffer + 0xB0));
// 		if(*(DWORD*)(dwBuffer + 0xB0) == 0)
// 			sprintf(szText, "%d", *(DWORD*)(dwBuffer + 0xC0));
// 		strcpy(auctionitem[nCount].szBid, szText);
// 
// 	}else 
	if(dwType == 1)//Name
	{
		char szItemName[256];
		char* ptemp;

		if(INVALID_PTR(dwBuffer + 12) || strlen((LPCSTR)(dwBuffer + 12)) >= sizeof(szItemName))
			return TRUE;

		strcpy(szItemName, (LPCSTR)(dwBuffer + 12));
		ptemp = strstr(szItemName, "{/c}");
		if(ptemp)
			*ptemp = 0;

		strcpy(auctionitem[nCount].szItemName, (LPTSTR)szItemName);
		
		//Format Bid and Buyout
		strcpy(auctionitem[nCount].szDPS, "");
		strcpy(auctionitem[nCount].szTimeLeft, "");
		auctionitem[nCount].nDPSorArmor = 2;
	}
	else if(dwType == 2)//DPS
	{
		strcpy(auctionitem[nCount].szDPS, (LPTSTR)dwBuffer);
		auctionitem[nCount].nDPSorArmor = 1;
	}
	else if(dwType == 3)//Armor
	{
		strcpy(auctionitem[nCount].szArmor, (LPTSTR)dwBuffer);
		auctionitem[nCount].nDPSorArmor = 0;
	}
	else if(dwType == 4)//Bid
	{
		strcpy(auctionitem[nCount].szBid, (LPTSTR)dwBuffer);
	}
	else if(dwType == 5)//Buyout
	{
		strcpy(auctionitem[nCount].szBuyout, (LPTSTR)dwBuffer);
	}
	else if(dwType == 6)//TimeLeft
	{
		strcpy(auctionitem[nCount].szTimeLeft, (LPTSTR)dwBuffer);
		nCount++;
	}
	else if(dwType == 7)//Quantity
	{
		strcpy(gemsitem.szQuantity, (LPTSTR)dwBuffer);
		nShowGems = 1;
	}
	else if(dwType == 8)//Price Per Unit
	{
		strcpy(gemsitem.szPricePerUnit, (LPTSTR)dwBuffer);
		nShowGems++;
	}
	else if(dwType == 9)//Total Amount
	{
		strcpy(gemsitem.szTotalAmount, (LPTSTR)dwBuffer);
		nShowGems++;
	}
	else if(dwType == 0)//Gem Name
	{
		char szItemName[256];
		char* ptemp;
		
		if(INVALID_PTR(dwBuffer + 12) || strlen((LPCSTR)(dwBuffer + 12)) >= sizeof(szItemName))
			return TRUE;
		
		strcpy(szItemName, (LPCSTR)(dwBuffer + 12));
		ptemp = strstr(szItemName, "{/c}");
		if(ptemp)
			*ptemp = 0;
		
		strcpy(gemsitem.szGemName, (LPTSTR)szItemName);
		nShowGems++;
	}
	else if(dwType == 10)//Detailed Item Info
	{
		if(INVALID_PTR(dwBuffer) || 
			INVALID_PTR(dwBuffer + 0xC) || 
			INVALID_PTR(dwBuffer + 0x18) || 
			INVALID_PTR(dwBuffer + 0x24) || 
			INVALID_PTR(dwBuffer + 0x30) || 
			INVALID_PTR(dwBuffer + 0x54) || 
			INVALID_PTR(dwBuffer + 0x60) || 
			INVALID_PTR(dwBuffer + 0x78) || 
			INVALID_PTR(dwBuffer + 0x84) || 
			INVALID_PTR(dwBuffer + 0x9C) || 
			INVALID_PTR(dwBuffer + 0xCC))
			return TRUE;
		strcpy(detailediteminfo.szItemName, (LPCTSTR)*(ULONG*)dwBuffer);
		strcpy(detailediteminfo.szRarity, (LPCTSTR)*(ULONG*)(dwBuffer + 0xC));
		strcpy(detailediteminfo.szMagicFeature, (LPCTSTR)*(ULONG*)(dwBuffer + 0x18));
		strcpy(detailediteminfo.szMainPerformance, (LPCTSTR)*(ULONG*)(dwBuffer + 0x24));
		strcpy(detailediteminfo.szPerformance, (LPCTSTR)*(ULONG*)(dwBuffer + 0x30));
		strcpy(detailediteminfo.szSellValue, (LPCTSTR)*(ULONG*)(dwBuffer + 0x54));
		strcpy(detailediteminfo.szDurability, (LPCTSTR)*(ULONG*)(dwBuffer + 0x60));
		strcpy(detailediteminfo.szItemLevel, (LPCTSTR)*(ULONG*)(dwBuffer + 0x78));
		strcpy(detailediteminfo.szRequiredLevel, (LPCTSTR)*(ULONG*)(dwBuffer + 0x84));
		strcpy(detailediteminfo.szItemType, (LPCTSTR)*(ULONG*)(dwBuffer + 0x9C));
		strcpy(detailediteminfo.szAddedFeature, (LPCTSTR)*(ULONG*)(dwBuffer + 0xCC));
		nShowDetailedItemInfo++;
	}

	
	if(nCount == 1)
	{
		nCount = 0;
		if(hwndListener)
		{
			COPYDATASTRUCT cds;
			
			cds.dwData = 0;
			cds.lpData = (LPVOID)&auctionitem[0];
			cds.cbData = sizeof(GOLDAUCTION);

			return SendMessage(hwndListener, WM_COPYDATA, (WPARAM)hwndDiablo, (LPARAM)&cds);
		}
	}

	if(nShowGems == 5)
	{
		nShowGems = 0;
		if(hwndListener)
		{
			COPYDATASTRUCT cds;
			
			cds.dwData = 1;
			cds.lpData = (LPVOID)&gemsitem;
			cds.cbData = sizeof(GEMS);
			
			return SendMessage(hwndListener, WM_COPYDATA, (WPARAM)hwndDiablo, (LPARAM)&cds);
		}
	}
	
	if(nShowDetailedItemInfo == 1)
	{
		nShowDetailedItemInfo = 0;
		if(hwndListener)
		{
			COPYDATASTRUCT cds;
			
			cds.dwData = 2;
			cds.lpData = (LPVOID)&detailediteminfo;
			cds.cbData = sizeof(ITEMINFO);
			
			return SendMessage(hwndListener, WM_COPYDATA, (WPARAM)hwndDiablo, (LPARAM)&cds);
		}
	}
	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{ 
	case WM_AUTOSTART:
		bStart = TRUE;
		return 0;
	case WM_AUTOSTOP:
		bStart = FALSE;
		return 0;
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		if(bStart)
			return 0;
		break;
	case WM_ACTIVATEAPP:
	case WM_NCACTIVATE:
	case WM_ACTIVATE:
	case WM_KILLFOCUS:
		if(bStart && wParam == 0)
			return 0;
		break;
	case WM_LBUTTONDOWN:
		if(bStart)
		{
			if(wParam == 0x321)
			{
				wParam = 1;
				OutputDebugString("WM_LBUTTONDOWN is called!\r\n");
				break;
			}
			else 
				return 0;
		}
		break;
	case WM_LBUTTONUP:
		if(bStart)
		{
			if(wParam == 0x321)
			{
				wParam = 0;
				break;
			}
			else 
				return 0;
		}
		break;
	case WM_MOUSEMOVE:
		if(bStart)
		{
			if(wParam == 0x321)
			{
				wParam = 0;
				break;
			}
			else 
				return 0;
		}
		break;
	case WM_SETCURSOR:
		if(bStart)
		{
			if(wParam == 0x321)
			{
				wParam = (WPARAM)hwndDiablo;
				break;
			}
			else 
				return 0;
		}
		break;
	}
	return CallWindowProc((WNDPROC)orgWndProc, hWnd, iMsg, wParam, lParam);
}