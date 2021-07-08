#pragma once
#include "GameObject.h"
#include "Enemy.h"

class Hpbar :
	public GameObject
{
public:
	Hpbar(const wchar_t* imagePath);
	~Hpbar();

	Enemy* owner;
	float originalWidth;

	virtual void Update();
};

