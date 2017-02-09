// PokerManager.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "PokerManager.h"
#include <Windows.h>
#include <math.h>

#define WINDOW_WIDTH	960
#define WINDOW_HEIGHT	690

#define RESERVED_COLOR	RGB(65, 49 ,49)
#define JOINWAITINGLIST_POINT_X	804
#define JOINWAITINGLIST_POINT_Y	557

#define SEATED_MARK_COLOR		RGB(248, 248, 248)
#define SEATED_MARK_X			32
#define SEATED_MARK1_Y			498
#define SEATED_MARK2_Y			480

// POINT ptSLOT[13] = {
// 	{960, 1430}, 
// 	{1920, 1430}, 
// 	{960, 740}, 
// 	{1920, 740}, 
// 	{0, 1430}, 
// 	{0, 740}, 
// 	{2880, 1430}, 
// 	{2880, 740}, 
// 	{960, 50}, 
// 	{1920, 50}, 
// 	{0, 50}, 
// 	{2880, 50}, 
// 	{960, 50}
// };

POINT ptSLOT[13] = {
	{0, 0}, 
	{0, 100}, 
	{0, 200}, 
	{0, 300}, 
	{350, 0}, 
	{350, 100}, 
	{350, 200}, 
	{350, 300}, 
	{700, 0}, 
	{700, 100}, 
	{700, 300}, 
	{750, 350}, 
	{800, 400}
};

POINT ptReserved[6] = {
	{314, 460},
	{108, 263},
	{325, 86},
	{637, 86},
	{855, 263},
	{637, 460}
};
int nHandCount[3] = {6, 9, 2};

BOOL CALLBACK EnumPokerWindowsProc(
		HWND hwnd, 
		LPARAM lParam 
		);

BOOL CALLBACK EnumMessageProc(
								   HWND hwnd, 
								   LPARAM lParam 
								   );

void LoadSetting(void);
void AddItem(HWND hwnd);
int RemoveItem(int nIndex);
void UpdateItem(HWND hwnd, int nIndex);

DWORD WINAPI PokerMangerThread( LPVOID lpParam );
DWORD WINAPI AutoThread( LPVOID lpParam );

HINSTANCE hInst;								// current instance
TCHAR szTitle[1024];					// The title bar text
TCHAR szWindowClass[1024];			// the main window class name
BOOL bAutoSeatEnabled = FALSE;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HANDLE hMutex; 

	hMutex = OpenMutex( 
		MUTEX_ALL_ACCESS,            // request full access
		FALSE,                       // handle not inheritable
		TEXT("PokerManager"));  // object name

	if (hMutex == NULL) 
		hMutex = CreateMutex( 
			NULL,                        // default security descriptor
			FALSE,                       // mutex not owned
			TEXT("PokerManager"));  // object name
	else
		return 0;



	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	DWORD dwThread;
	HANDLE hThread = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		PokerMangerThread,          // thread function 
		NULL,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThread);   // returns the thread identifier 

	hThread = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		AutoThread,          // thread function 
		NULL,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThread);   // returns the thread identifier 

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, 1024);
	LoadString(hInstance, IDC_POKERMANAGER, szWindowClass, 1024);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POKERMANAGER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	
	return 0;
}
// Windows Frame
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POKERMANAGER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POKERMANAGER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	RegisterHotKey(hWnd, 100, MOD_CONTROL, 'S');
	RegisterHotKey(hWnd, 101, MOD_CONTROL, 'T');

	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_HOTKEY:
		if(wParam == 100)
		{
			bAutoSeatEnabled = TRUE;
		}
		else if(wParam == 101)
		{
			bAutoSeatEnabled = FALSE;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Poker Managing
DWORD WINAPI PokerMangerThread( LPVOID lpParam ) 
{ 
	LoadSetting();
	while(TRUE)
	{
		int i;
		for(i = 0; i < nCount; i++)
		{
			DWORD dwProcessId = 0;

			GetWindowThreadProcessId(hwndstructs[i].hwnd, &dwProcessId);
			if(dwProcessId == 0)
			{
				RemoveItem(i--);
				continue;
			}

			UpdateItem(hwndstructs[i].hwnd, i);

			char szText[256];
			GetWindowText(hwndstructs[i].hwnd, szText, 256);

			if(hwndstructs[i].bSittingOut && (!bAutoSeatEnabled || (bAutoSeatEnabled && hwndstructs[i].nSlotNum != 12)))
			{
				hwndstructs[i].nSlotNum = 10;
			}
			else if(hwndstructs[i].nOccupiedSeat == 1 && (!bAutoSeatEnabled || (bAutoSeatEnabled && hwndstructs[i].nSlotNum != 12)))
			{
				if(hwndstructs[i].nSlotNum != 11 && hwndstructs[i].nSlotNum >= 10)
					hwndstructs[i].nSlotNum = 11;
				//Move to stack #2
			}else if(hwndstructs[i].bSeated && hwndstructs[i].nOccupiedSeat != 1 && (!bAutoSeatEnabled || (bAutoSeatEnabled && hwndstructs[i].nSlotNum != 12)))
			{
				if(hwndstructs[i].nSlotNum >= 10)
				{
					//Move to normal slot
					for(int j = 0; j < 10; j++)
					{
						int k;
						for(k = 0; k < nCount; k++)
							if(hwndstructs[k].nSlotNum == j)
								break;

						if(k == nCount)
						{
// 							MoveWindow(hwndstructs[i].hwnd, 
// 								ptSLOT[j].x, 
// 								ptSLOT[j].y, 
// 								WINDOW_WIDTH, 
// 							 	WINDOW_HEIGHT, 
// 								TRUE);
							hwndstructs[i].nSlotNum = j;
							break;
						}
					}
				}
			}else if(hwndstructs[i].bSeated == FALSE && (!bAutoSeatEnabled || (bAutoSeatEnabled && hwndstructs[i].nSlotNum != 12)))
			{
				if(hwndstructs[i].nSlotNum != 10 && hwndstructs[i].nSlotNum >= 10)
					hwndstructs[i].nSlotNum = 10;
				//Move to stack #1
			}

			if(bAutoSeatEnabled && hwndstructs[i].nSlotNum == 12 && hwndstructs[i].bReserved == FALSE)
			{
				hwndstructs[i].nSlotNum = 10;
			}

			//AutoSeat
			if(bAutoSeatEnabled && hwndstructs[i].bReserved)
			{
				if(hwndstructs[i].nTableType == 0 && 
					hwndstructs[i].nOccupiedSeat < 6 && 
					hwndstructs[i].bSeated == FALSE && 
					hwndstructs[i].bJoined == FALSE)//If this is 6 handed table
				{
					BOOL bExit = FALSE;
					for(int j = 1; j < 6 && !bExit; j++)
						for(int k = 0; k < 6 && !bExit; k++)
							if(hwndstructs[i].nSeat[k] == 3 && 
								hwndstructs[i].nSeat[(k + j) % 6] == 0)
							{
								POINT ptClick = ptReserved[(k + j) % 6];
								::PostMessage(hwndstructs[i].hwnd, 
									WM_LBUTTONDOWN, 
									MK_LBUTTON, 
									MAKELPARAM(ptClick.x, ptClick.y));
								Sleep(200);
								::PostMessage(hwndstructs[i].hwnd, 
									WM_LBUTTONUP, 
									0, 
									MAKELPARAM(ptClick.x, ptClick.y));

								hwndstructs[i].nSlotNum = 12;
								hwndstructs[i].bJoined = TRUE;
								bExit = TRUE;
							}
				}

				if(hwndstructs[i].nTableType == 0 && 
					hwndstructs[i].nOccupiedSeat == 6 && 
					hwndstructs[i].bSeated == FALSE && 
					hwndstructs[i].bReserved && 
					hwndstructs[i].bJoined == FALSE)
				{
					POINT ptClick;
					ptClick.x = JOINWAITINGLIST_POINT_X;
					ptClick.y = JOINWAITINGLIST_POINT_Y;

					::PostMessage(hwndstructs[i].hwnd, 
						WM_LBUTTONDOWN, 
						MK_LBUTTON, 
						MAKELPARAM(ptClick.x, ptClick.y));
					Sleep(200);
					::PostMessage(hwndstructs[i].hwnd, 
						WM_LBUTTONUP, 
						0, 
						MAKELPARAM(ptClick.x, ptClick.y));

					hwndstructs[i].nSlotNum = 12;
					hwndstructs[i].bJoined = TRUE;
				}
			}
		}

		EnumWindows(EnumPokerWindowsProc, (LPARAM)NULL);
		Sleep(100);
	}
}

BOOL CALLBACK EnumPokerWindowsProc(
								   HWND hwnd, 
								   LPARAM lParam 
								   )
{
	char szClassName[256];

	GetClassName(hwnd, szClassName, 256);

	if(strcmp(szClassName, "PokerStarsTableFrameClass") == 0)
	{
		int i;
		BOOL bExist = FALSE;
		for(i = 0; i < nCount; i++)
		{
			if(hwndstructs[i].hwnd == hwnd)
			{
				bExist = TRUE;
			}
		}

		if(bExist == FALSE)
		{
			AddItem(hwnd);
			return TRUE;
		}
	}

	return TRUE;
}

void LoadSetting(void)
{
	char szFileName[256];
	GetModuleFileName(NULL, szFileName, 256);

	char* ptemp = strrchr(szFileName, '\\');
	if(ptemp)
		strcpy(ptemp, "\\Config.dat");

	DWORD dwBytes;
	HANDLE hConfigFile = CreateFile(szFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 5; j++)
			for(int k = 0; k < 9; k++)
				colorsetting.colorstruct[i].crColors[j][k] = RGB(254, 254, 254);

		for(int j = 0; j < 9; j++)
		{
			colorsetting.colorstruct[i].ptPoint[j].x = 0;
			colorsetting.colorstruct[i].ptPoint[j].y = 0;

			colorsetting.colorstruct[i].ptSeatPoint[j].x = 0;
			colorsetting.colorstruct[i].ptSeatPoint[j].y = 0;

			colorsetting.colorstruct[i].ptEmptyPoint[j].x = 0;
			colorsetting.colorstruct[i].ptEmptyPoint[j].y = 0;
		}
	}

	colorsetting.ptSittingOutPoint.x = 0;
	colorsetting.ptSittingOutPoint.y = 0;
	colorsetting.ptActivePoint.x = 0;
	colorsetting.ptActivePoint.y = 0;
	colorsetting.crSO[0] = RGB(254, 254, 254);
	colorsetting.crSO[1] = RGB(254, 254, 254);
	colorsetting.crActive[0] = RGB(254, 254, 254);
	colorsetting.crActive[1] = RGB(254, 254, 254);

	if(hConfigFile != INVALID_HANDLE_VALUE)
	{
		//for(int i = 0; i < SITE_COUNT; i++)
		{
			ReadFile(hConfigFile, &colorsetting, sizeof(COLORSETTING), &dwBytes, NULL);
		}
	}

	CloseHandle(hConfigFile);

	//Temporary added code
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 5; j++)
			for(int k = 0; k < 9; k++)
				if(colorsetting.colorstruct[i].crColors[j][k] == RGB(255, 255, 255))
				colorsetting.colorstruct[i].crColors[j][k] = RGB(254, 254, 254);
	}

	if(colorsetting.crSO[0] == RGB(255, 255, 255))
		colorsetting.crSO[0] = RGB(254, 254, 254);
	if(colorsetting.crSO[1] == RGB(255, 255, 255))
		colorsetting.crSO[1] = RGB(254, 254, 254);
	if(colorsetting.crActive[0] = RGB(255, 255, 255))
		colorsetting.crActive[0] = RGB(254, 254, 254);
	if(colorsetting.crActive[1] = RGB(255, 255, 255))
		colorsetting.crActive[1] = RGB(254, 254, 254);
}

void AddItem(HWND hwnd)
{
	char szWindowName[256];
	::GetWindowText(hwnd, szWindowName, 256);
	
	if(strlen(szWindowName) == 0)
		return;

	RECT rect;
	GetWindowRect(hwnd, &rect);
	MoveWindow(hwnd, 
		rect.left, 
		rect.top, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		TRUE);

	hwndstructs[nCount].hwnd = hwnd;

	BOOL nType6Or9Or2 = 0;
	int nErr4692[3] = {0, 0, 0};
	int i, j, k, n;


	InvalidateRect(hwnd, NULL, TRUE);

	Sleep(800);
	HDC hdc = ::GetDC(hwnd);

	for(n = 0; n < 3; n++)
		for(i = 0; i < nHandCount[n]; i++)
		{
			COLORREF cr = ::GetPixel(hdc, colorsetting.colorstruct[n].ptSeatPoint[i].x, colorsetting.colorstruct[n].ptSeatPoint[i].y);

			for(j = 1; j < 4; j++)			
				if(cr == colorsetting.colorstruct[n].crColors[j][i])
					break;

			if(j == 4)
			{
				cr = ::GetPixel(hdc, colorsetting.colorstruct[n].ptEmptyPoint[i].x, colorsetting.colorstruct[n].ptEmptyPoint[i].y);
				if(cr != colorsetting.colorstruct[n].crColors[4][i])
					nErr4692[n]++;
			}
		}

	if((float)nErr4692[0] / nHandCount[0] < (float)nErr4692[1] / nHandCount[1])
	{
		if(nErr4692[0] < 4)
			nType6Or9Or2 = 0;
		else nType6Or9Or2 = 2;
	}
	else nType6Or9Or2 = 1;
	//nType6Or9Or2 = (nErr4692[0] / nHandCount[0] < nErr4692[1] / nHandCount[1]) ? ((nErr4692[0] / nHandCount[0] < nErr4692[2] / nHandCount[2]) ? 0 : 2) : 1;

	if(nErr4692[0] == 6 && nErr4692[1] == 9 && nErr4692[2] == 2)
		return;
	if(nErr4692[0] >= 2 && nErr4692[1] >= 2 && nErr4692[2] >= 2)
		return;

	if(nType6Or9Or2 != 0)
	{
		int a = 5;
	}
	char szText[256];
	char szName[256];
	GetWindowText(hwnd, szName, 256);
	switch(nType6Or9Or2)
	{
	case 0:
		sprintf(szText, "6 Hand Table : %s\r\n", szName);
		break;
	case 1:
		sprintf(szText, "9 Hand Table : %s\r\n", szName);
		break;
	case 2:
		sprintf(szText, "2 Hand Table : %s\r\n", szName);
		break;
	}
	OutputDebugString(szText);


	hwndstructs[nCount].nTableType = nType6Or9Or2;


	hwndstructs[nCount].nOccupiedSeat = 0;
	hwndstructs[nCount].bSeated = FALSE;
	hwndstructs[nCount].nSlotNum = 10;
	hwndstructs[nCount].bReserved = FALSE;
	hwndstructs[nCount].bJoined = FALSE;

	for(i = 0; i < nHandCount[nType6Or9Or2]; i++)
	{
		hwndstructs[nCount].nSeat[i] = 0;
		COLORREF cr;
		for(j = 1; j < 5; j++)
		{
			if(j == 1)
				cr = ::GetPixel(hdc, colorsetting.colorstruct[nType6Or9Or2].ptSeatPoint[i].x, colorsetting.colorstruct[nType6Or9Or2].ptSeatPoint[i].y);
			else if(j == 4)
				cr = ::GetPixel(hdc, colorsetting.colorstruct[nType6Or9Or2].ptEmptyPoint[i].x, colorsetting.colorstruct[nType6Or9Or2].ptEmptyPoint[i].y);

			if(cr == colorsetting.colorstruct[nType6Or9Or2].crColors[j][i])
			{
				if(j < 4)
					hwndstructs[nCount].nSeat[i] = 2;
				else
					hwndstructs[nCount].nSeat[i] = 0;
				break;
			}
		}

		if(hwndstructs[nCount].nSeat[i] == 2)
			hwndstructs[nCount].nOccupiedSeat++;
	}

	::ReleaseDC(hwnd, hdc);
	
	nCount++;
}

int RemoveItem(int nIndex)
{
	for(int i = nIndex + 1; i < nCount; i++)
	{
		hwndstructs[i - 1] = hwndstructs[i];
	}
	nCount--;

	return 0;
}

void UpdateItem(HWND hwnd, int nIndex)
{
	int i, j, k;

	RECT rect;
	GetWindowRect(hwnd, &rect);

	SHORT shMouse = GetAsyncKeyState(VK_LBUTTON);

	if((shMouse & 0x8000) == 0)
	{
		if(hwndstructs[nIndex].nSlotNum < 10)
		{
			int nDist = abs(rect.left - ptSLOT[0].x) + abs(rect.top - ptSLOT[0].y), nSlotIndex = 0;

			for(int i = 1; i < 10; i++)
			{
				int nTemp = abs(rect.left - ptSLOT[i].x) + abs(rect.top - ptSLOT[i].y);
				if(nTemp < nDist)
				{
					nDist = nTemp;
					nSlotIndex = i;
				}
			}

			if(hwndstructs[nIndex].nSlotNum != nSlotIndex)
				hwndstructs[nIndex].nSlotNum = nSlotIndex;
		}
		
		
		MoveWindow(hwnd, 
			rect.left, 
			rect.top, 
			WINDOW_WIDTH, 
			WINDOW_HEIGHT, 
			TRUE);

	}
	if(rect.bottom - rect.top != WINDOW_HEIGHT ||
		rect.right - rect.left != WINDOW_WIDTH)
		Sleep(100);
	InvalidateRect(hwnd, NULL, TRUE);
	
	HDC hdc = ::GetDC(hwnd);

	hwndstructs[nIndex].nOccupiedSeat = 0;
	hwndstructs[nIndex].bReserved = FALSE;

	COLORREF cr;

	for(i = 0; i < nHandCount[hwndstructs[nIndex].nTableType]; i++)
	{
		hwndstructs[nIndex].nSeat[i] = 0;
		for(j = 1; j < 5; j++)
		{
			if(j == 1)
				cr = ::GetPixel(hdc, colorsetting.colorstruct[hwndstructs[nIndex].nTableType].ptSeatPoint[i].x, colorsetting.colorstruct[hwndstructs[nIndex].nTableType].ptSeatPoint[i].y);
			else if(j == 4)
				cr = ::GetPixel(hdc, colorsetting.colorstruct[hwndstructs[nIndex].nTableType].ptEmptyPoint[i].x, colorsetting.colorstruct[hwndstructs[nIndex].nTableType].ptEmptyPoint[i].y);

			if(cr == colorsetting.colorstruct[hwndstructs[nIndex].nTableType].crColors[j][i])
			{
				if(j < 4)
					hwndstructs[nIndex].nSeat[i] = 2;
				else
					hwndstructs[nIndex].nSeat[i] = 0;
				break;
			}
		}

		if(hwndstructs[nIndex].nSeat[i] == 2)
			hwndstructs[nIndex].nOccupiedSeat++;
	}
	
	if(hwndstructs[nIndex].nTableType == 0)
	{
		for(int i = 0; i < 6; i++)
		{
			cr = ::GetPixel(hdc, ptReserved[i].x, ptReserved[i].y);
			if(RESERVED_COLOR == cr)
			{
				hwndstructs[nIndex].nSeat[i] = 3;
				hwndstructs[nIndex].nOccupiedSeat++;
				hwndstructs[nIndex].bReserved = TRUE;
			}
		}
	}

	cr = ::GetPixel(hdc, colorsetting.ptSittingOutPoint.x, colorsetting.ptSittingOutPoint.y);
	if(cr == colorsetting.crSO[0] || cr == colorsetting.crSO[1])
	{
		hwndstructs[nIndex].bSeated = TRUE;
		hwndstructs[nIndex].bSittingOut = TRUE;
	}
	else
		hwndstructs[nIndex].bSittingOut = FALSE;

	cr = ::GetPixel(hdc, SEATED_MARK_X, SEATED_MARK1_Y);
	COLORREF cr1 = ::GetPixel(hdc, SEATED_MARK_X, SEATED_MARK2_Y);

	if(cr == SEATED_MARK_COLOR || cr1 == SEATED_MARK_COLOR)
	{
		hwndstructs[nIndex].bSeated = TRUE;
	}
	else
		hwndstructs[nIndex].bSeated = FALSE;
// 		cr = ::GetPixel(hdc, colorsetting.ptActivePoint.x, colorsetting.ptActivePoint.y);
// 		if(cr == colorsetting.crActive)
// 		{
// 
// 		}

// 	if(hwndstructs[nIndex].nOccupiedSeat != 6)
// 		int a = 4;

	::ReleaseDC(hwnd, hdc);
	return;
}

DWORD WINAPI AutoThread( LPVOID lpParam )
{
	while(TRUE)
	{
		EnumWindows(EnumMessageProc, NULL);
		Sleep(100);
	}
	return 0;
}

BOOL CALLBACK EnumMessageProc(
							  HWND hwnd, 
							  LPARAM lParam 
							  )
{
	char szName[256];
	RECT rect;

	GetWindowText(hwnd, szName, 256);
	GetWindowRect(hwnd, &rect);

	if(strcmp(szName, "PokerStars") == 0 && 
		rect.right - rect.left == 270 && 
		rect.bottom - rect.top == 134)
	{
		HWND hwndbutton = GetWindow(hwnd, GW_CHILD);
		::SendMessage(hwnd, WM_COMMAND, 0x3FFE, (LPARAM)hwndbutton);
	}
	return TRUE;
}