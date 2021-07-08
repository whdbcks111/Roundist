#include "stdafx.h"
#include "PlayerHpbar.h"
#include "Scene.h"

PlayerHpbar::PlayerHpbar(const wchar_t* imagePath) : GameObject(imagePath)
{
	Scene::GetCurrentScene()->PushBackGameObject(this);
	transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() * 0.25f
	);
	transform->SetScale(0.2f, 0.025f);
	originalWidth = renderer->GetWidth() * transform->scale.x;
}

PlayerHpbar::~PlayerHpbar()
{
}

void PlayerHpbar::Update()
{
	transform->position.x = owner->transform->position.x + originalWidth * (owner->hp / owner->max_hp - 1) * 0.5f;
	transform->position.y = owner->transform->position.y - 40;
	transform->scale.x = 0.2f * (owner->hp / owner->max_hp);
}