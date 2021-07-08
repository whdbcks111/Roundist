#include "stdafx.h"
#include "WinScene.h"


WinScene::WinScene()
{
}


WinScene::~WinScene()
{
}

void WinScene::Initialize()
{
	background = PushBackGameObject(new GameObject(L"resources/win.png"));
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
