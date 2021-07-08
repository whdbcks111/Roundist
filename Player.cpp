#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameOverScene.h"

Player::Player(const wchar_t* imagePath, float hp)
	:GameObject(imagePath)
{
	col = new AABBCollider(
		transform,
		renderer->GetWidth() * (-0.5f),
		renderer->GetWidth() * 0.5f,
		renderer->GetHeight() * (-0.5f),
		renderer->GetHeight() * 0.5f
	);
	this->hp = hp;
	this->max_hp = hp;
	this->add_hp = 0.0f;
	moveSpeed = 500.0f;
	bm = new BulletManager();
	Scene::GetCurrentScene()->PushBackGameObject(bm);
}
Player::~Player() {}
void Player::Update() {
	//매 프레임 호출
	if (InputManager::GetKeyState(VK_RBUTTON)) {
		moveSpeed = 800.0f;
	}
	else if (InputManager::GetKeyState(VK_SPACE))
	{
		Shoot();
	}
	Move();
	moveSpeed = 500.0f;
	hp = min(max_hp, hp + add_hp * TimeManager::GetDeltaTime());
}

void Player::LateUpdate()
{
	if (hp <= 0.0f) {
		Scene::ChangeScene(new GameOverScene());
	}
}



void Player::Move() {
	//움직임을 담당
	if (InputManager::GetKeyState(VK_LBUTTON)) {
		float mx = (float)InputManager::GetMouseX();
		float my = (float)InputManager::GetMouseY();
		float px = transform->position.x;
		float py = transform->position.y;
		float dx = mx - px;
		float dy = my - py;
		float distance = sqrt(dx*dx + dy * dy);
		if (distance < 10) return;
		float angle = atan2(dy, dx) * 180 / PI;
		float gx = moveSpeed * cos(angle * PI / 180) * TimeManager::GetDeltaTime();
		float gy = moveSpeed * sin(angle * PI / 180) * TimeManager::GetDeltaTime();
		float hw = (renderer->GetWidth() * transform->scale.x / 2);
		float hh = (renderer->GetHeight() * transform->scale.y / 2);
		float sw = WinApp::GetScreenWidth() - hw;
		float  sh = WinApp::GetScreenHeight() - hh;
		if(gx < 0 && px > hw || gx > 0 && px < sw)
			transform->position.x += gx;
		if (gy < 0 && py > hh || gy > 0 && py < sh)
			transform->position.y += gy;
	}
}

void Player::Shoot() {
	//총알 발사
	float mx = (float)InputManager::GetMouseX();
	float my = (float)InputManager::GetMouseY();
	float px = transform->position.x;
	float py = transform->position.y;
	float dx = mx - px;
	float dy = my - py;
	float angle = atan2(dy, dx) * 180 / PI;
	float count = 2.0f;
	float area = 5.0f;

	for (float i = -area / 2; i <= area / 2; i += area / (count - 1.0f)) {
		Bullet* b = new Bullet(L"resources/player.png");
		Scene::GetCurrentScene()->PushBackGameObject(b);
		bm->PushBackBullet(b);

		b->transform->position = this->transform->position;
		b->transform->SetScale(0.015f, 0.015f);
	
		b->minSpeed = 600.0f;
		b->speedRate = -2000.0f;
		b->speed = 1500.0f;
		b->angle = angle + i;
		b->damage = 1.0f;
	}
	
}

void Player::Hit(float damage)
{
	hp -= damage;
}

