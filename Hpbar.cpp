#include "stdafx.h"
#include "Hpbar.h"
#include "Scene.h"

Hpbar::Hpbar(const wchar_t* imagePath) : GameObject(imagePath)
{
	Scene::GetCurrentScene()->PushBackGameObject(this);
	transform->SetPosition(
		(float)WinApp::GetScreenWidth() / 2,
		(float)WinApp::GetScreenHeight() * 0.25f
	);
	transform->SetScale(0.5f, 0.03f);
	originalWidth = renderer->GetWidth() * transform->scale.x;
}

Hpbar::~Hpbar()
{
}

void Hpbar::Update()
{
	transform->position.x = owner->transform->position.x + originalWidth * (owner->hp / owner->max_hp - 1) * 0.5f;
	transform->position.y = owner->transform->position.y - 100;
	transform->scale.x = 0.5f * (owner->hp / owner->max_hp);
}