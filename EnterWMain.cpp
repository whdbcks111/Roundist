#include "stdafx.h"
#include "EnterWMain.h"
#include "MainScene.h"


EnterWMain::EnterWMain()
{
}


EnterWMain::~EnterWMain()
{
}

void EnterWMain::Update()
{
	if (InputManager::GetKeyDown(VK_RETURN)) {
		Scene::ChangeScene(new MainScene());
	}
}
