#pragma once
#include "stdafx.h"

class WinApp
{
public:
	WinApp();
private:
	HWND hWnd;
	static int width;
	static int height;
	bool isFullScreen;
public:
	HWND GetHWND();
	static int GetScreenWidth();
	static int GetScreenHeight();
	bool GetFullScreened();
public:
	bool Initialize(const wchar_t* title, int width, int height, bool isFullScreen);

	
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

