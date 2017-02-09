#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

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

typedef struct _HWNDSTRUCT
{
	HWND hwnd;
	int nTableType;
	int nSlotNum;
	BOOL bSeated;
	BOOL bSittingOut;
	int nOccupiedSeat;
	BOOL bReserved;
	BOOL bJoined;
	int nSeat[9];	// 0 : empty, 1 : me, 2 : others, 3: reserved
}HWNDSTRUCT, *PHWNDSTRUCT;

HWNDSTRUCT hwndstructs[256];
ULONG nCount = 0;
COLORSETTING colorsetting;