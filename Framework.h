#pragma once
#include "WinApp.h"
#include "D2DApp.h"
#include "Scene.h"
class Framework
{
public:
	Framework();
	~Framework();
private:
	WinApp* winApp;
	D2DApp* d2dApp;

public:
	void Run(Scene* startScene,const wchar_t* title, int width, int height, bool isFullScreen);

private:
	void StartGameLoop();
};
