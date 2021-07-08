#pragma once
#include "Scene.h"
#include "EnterWGame.h"

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Initialize();

	GameObject* background;	//배경 이미지
	EnterWGame* ew;
};

