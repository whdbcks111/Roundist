#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "Scene.h"

class EnterWMain :
	public GameObject
{
public:
	EnterWMain();
	~EnterWMain();

	virtual void Update();
};

