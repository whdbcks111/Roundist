#include "stdafx.h"
#include "GameScene.h"
#include "EBulletManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/background.png"));
	background->transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() / 2
	);
	background->transform->SetScale(
		(float)WinApp::GetScreenWidth() / background->renderer->GetWidth(), 
		(float)WinApp::GetScreenHeight() / background->renderer->GetHeight()
	);

	player = (Player*)PushBackGameObject(new Player(L"resources/player.png", 150.0f));
	player->transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() * 0.85f
	);
	player->transform->SetScale(0.07f, 0.07f);

	enemy = (Enemy*)PushBackGameObject(new Enemy(L"resources/enemy.png", 2500.0f));
	enemy->transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() * 0.2f
	);
	enemy->transform->SetScale(0.3f, 0.3f);
	player->bm->enemy = enemy;
	enemy->bm->player = player;

	hpbar = new Hpbar(L"resources/progress_red.png");
	hpbar->owner = enemy;

	phpbar = new PlayerHpbar(L"resources/progress_green.png");
	phpbar->owner = player;
}
