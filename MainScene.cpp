#include "stdafx.h"
#include "MainScene.h"


MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/mainsc.png"));
	background->transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() / 2
	);
	background->transform->SetScale(
		(float)WinApp::GetScreenWidth() / background->renderer->GetWidth(),
		(float)WinApp::GetScreenHeight() / background->renderer->GetHeight()
	);

	ew = (EnterWGame*)PushBackGameObject(new EnterWGame());
}
