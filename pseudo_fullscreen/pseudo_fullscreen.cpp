// pseudo_fullscreen.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

LPCTSTR INI_PATH = L".\\pseudo_fullscreen.ini";
LPCTSTR INI_SECTION = L"dimensions";
LPCTSTR INI_X = L"x";
LPCTSTR INI_Y = L"y";
LPCTSTR INI_WIDTH = L"width";
LPCTSTR INI_HEIGHT = L"height";

struct Dimensions {
	int x, y, width, height;
};

Dimensions getDimensionsFromIni() {
	Dimensions dim = Dimensions();
	dim.x = GetPrivateProfileInt(INI_SECTION, INI_X, 0, INI_PATH);
	dim.y = GetPrivateProfileInt(INI_SECTION, INI_Y, 0, INI_PATH);
	dim.width = GetPrivateProfileInt(INI_SECTION, INI_WIDTH, 0, INI_PATH);
	dim.height = GetPrivateProfileInt(INI_SECTION, INI_HEIGHT, 0, INI_PATH);

	return dim;
}

void resizeClient(Dimensions dim) {
	HWND hwndClient;

	do {
		hwndClient = FindWindow(TEXT("Mabinogi"), NULL);
	} while (!hwndClient);

	long winLong = GetWindowLong(hwndClient, GWL_STYLE);
	winLong = winLong && !WS_CAPTION
					  && !WS_SYSMENU
					  && !WS_THICKFRAME
					  && !WS_MINIMIZE
					  && !WS_MAXIMIZEBOX;
	SetWindowLong(hwndClient, GWL_STYLE, winLong);
	MoveWindow(hwndClient, dim.x, dim.y, dim.width, dim.height, TRUE);
}

void main() {
	Dimensions dim = getDimensionsFromIni();
	resizeClient(dim);
}
