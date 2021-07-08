#include "stdafx.h"
#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/over.png"));
	background->transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() / 2
	);
	background->transform->SetScale(
		(float)WinApp::GetScreenWidth() / background->renderer->GetWidth(),
		(float)WinApp::GetScreenHeight() / background->renderer->GetHeight()
	);

	ew = (EnterWMain*)PushBackGameObject(new EnterWMain());
}
