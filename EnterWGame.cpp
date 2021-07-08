#include "stdafx.h"
#include "EnterWGame.h"
#include "GameScene.h"


EnterWGame::EnterWGame()
{
}


EnterWGame::~EnterWGame()
{
}

void EnterWGame::Update()
{
	if (InputManager::GetKeyDown(VK_RETURN)) {
		Scene::ChangeScene(new GameScene());
	}
}
