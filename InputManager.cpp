#include "stdafx.h"
#include "InputManager.h"

WinApp* InputManager::winApp;
bool InputManager::lkey[256];
bool InputManager::rkey[256];
int InputManager::mX;
int InputManager::mY;

InputManager::InputManager(){}
InputManager::~InputManager(){}

void InputManager::UpdateKeyState()
{
	static HWND hWnd = winApp->GetHWND();
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(hWnd, &mousePosition);
	mX = mousePosition.x;
	mY = mousePosition.y;

	
	for (int i = 0; i < 256; ++i)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int InputManager::GetKeyState(int vk)
{
	//Pressed: 2, KeyDown: 1
	//KeyUp: -1, 안눌렸을경우: 0
	if (lkey[vk] && rkey[vk]) return 2;
	if (!lkey[vk] && rkey[vk]) return 1;
	if (lkey[vk] && !rkey[vk]) return -1;
	return 0;
}

bool InputManager::GetKeyDown(int vk){
	return (GetKeyState(vk) == KEYDOWN);
}
bool InputManager::GetKeyPressed(int vk){
	return (GetKeyState(vk) == KEYPRESSED);
}
bool InputManager::GetKeyUp(int vk) {
	return (GetKeyState(vk) == KEYUP);
}

int InputManager::GetMouseX()
{
	return mX;
}

int InputManager::GetMouseY()
{
	return mY;
}