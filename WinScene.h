#pragma once
#include "Scene.h"
#include "EnterWMain.h"

class WinScene :
	public Scene
{
public:
	WinScene();
	~WinScene();

	virtual void Initialize();

	GameObject* background;	//배경 이미지
	EnterWMain* ew;
};

