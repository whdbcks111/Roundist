#pragma once
#include "Scene.h"
#include "Player.h"		
#include "Enemy.h"
#include "Hpbar.h"
#include "PlayerHpbar.h"

//4,5일차 수업 시간에 함께 제작한 Scene입니다.

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Initialize();

	GameObject* background;	//배경 이미지
	Player* player;		//플레이어
	Enemy* enemy;		//적
	Hpbar* hpbar;
	PlayerHpbar* phpbar;
};

