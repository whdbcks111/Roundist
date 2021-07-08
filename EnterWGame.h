#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "Scene.h"

class EnterWGame :
	public GameObject
{
public:
	EnterWGame();
	~EnterWGame();

	virtual void Update();
};

