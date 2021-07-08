#pragma once
#include "GameObject.h"
#include "Player.h"

class PlayerHpbar :
	public GameObject
{
public:
	PlayerHpbar(const wchar_t* imagePath);
	~PlayerHpbar();

	Player* owner;
	float originalWidth;

	virtual void Update();
};

