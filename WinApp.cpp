#include "stdafx.h"
#include "WinApp.h"

int WinApp::width = 0;
int WinApp::height = 0;

WinApp::WinApp():hWnd(NULL), isFullScreen(false)
{

}

HWND WinApp::GetHWND()
{
	return hWnd;
}

int WinApp::GetScreenWidth()
{
	return width;
}

int WinApp::GetScreenHeight()
{
	return height;
}

bool WinApp::GetFullScreened()
{
	return isFullScreen;
}

bool WinApp::Initialize(const wchar_t* title, int width, int height, bool isFullScreen = false)
{
	//윈도우의 속성 지정
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);				//윈도우 클래스 크기 값 등록
	wc.style = CS_HREDRAW | CS_VREDRAW;			//화면 크기 변경 시마다 가로, 세로 다시 그림
	wc.lpfnWndProc = WndProc;					//윈도우 프로시저(콜백) 함수 등록
	wc.cbClsExtra = 0;							//윈도우 클래스 예약 영역 사용 X
	wc.cbWndExtra = 0;							//윈도우 클래스 예약 영역 사용 X
	wc.hInstance = GetModuleHandle(NULL);		//윈도우 핸들 받아옴
	wc.hbrBackground = NULL;					//배경색 지정
	wc.lpszMenuName = NULL;						//메뉴 지정 x
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//마우스 커서 기본커서
	wc.lpszClassName = title;					//윈도우 클래스 이름 지정

	if (!RegisterClassEx(&wc))
	{
		printf("윈도우 클래스 등록 실패!\n");
		return false;
	}

	//전체화면 설정
	int wx, wy;
	RECT windowRect = { 0, };		//윈도우 크기 지정할 Rect
	DWORD style, exstyle;
	if (isFullScreen)
	{
		wx = wy = 0L;
		windowRect.right = GetSystemMetrics(SM_CXSCREEN);		//화면 크기 받아옴(가로)
		windowRect.bottom = GetSystemMetrics(SM_CYSCREEN);		//화면 크기 받아옴(세로)
		style = WS_SYSMENU | WS_POPUP;							//윈도우 스타일 지정
		exstyle = WS_EX_TOPMOST;
	}
	else
	{
		wx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;		//윈도우 띄울 위치 지정(화면 중앙)
		wy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

		windowRect.right = width;								//윈도우 크기 지정
		windowRect.bottom = height;
		style = WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION;		//윈도우 스타일 지정
		exstyle = NULL;
	}

	this->width = width;
	this->height = height;

	//윈도우 속성 수정
	AdjustWindowRectEx(&windowRect, style, FALSE, exstyle);

	//윈도우 생성
	hWnd = CreateWindowEx(exstyle, title, title, style,
		wx, wy, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		NULL, NULL, wc.hInstance, NULL);

	if (hWnd == NULL)
	{
		printf("CreateWindowEx Failed\n");
		return false;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	
	return true;
}

LRESULT WinApp::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//윈도우 프로시저 함수
	//메시지 루프 도중 메시지가 왔을 경우 실행됨
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0); return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}