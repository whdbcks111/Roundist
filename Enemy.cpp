#include "stdafx.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "EBulletManager.h"
#include "WinScene.h"

Enemy::Enemy(const wchar_t* imagePath, float hp)
	: GameObject(imagePath)
{
	col = new AABBCollider(
		transform,
		renderer->GetWidth()*(-0.45f),
		renderer->GetWidth()*0.45f,
		renderer->GetHeight()*(-0.1f),
		renderer->GetHeight()*0.1f
	);
	this->hp = hp;
	this->max_hp = hp;
	phase = 0;
	ptime = 0.0f;
	bm = new EBulletManager();
	Scene::GetCurrentScene()->PushBackGameObject(bm);
}
Enemy::~Enemy(){
	SAFE_DELETE(col);
}

void Enemy::Update() {
	ptime += TimeManager::GetDeltaTime();
	switch (phase) {
	case 0:
		Phase1();
		break;
	case 1:
		Phase2();
		break;
	}
}

void Enemy::LateUpdate()
{
	if (hp <= 0) {
		Scene::ChangeScene(new WinScene());
	}
}

void Enemy::Phase1() {
	Shoot1();
	static float vecx = 190.0f;
	float hw = (renderer->GetWidth() * transform->scale.x / 2);
	float sw = WinApp::GetScreenWidth() - hw;
	transform->position.x = max(hw, min(sw, transform->position.x + vecx * TimeManager::GetDeltaTime()));
	if (transform->position.x >= sw || transform->position.x <= hw) {
		vecx = -vecx;
	}
	if (hp < max_hp / 2 || ptime > 60.0f) {
		phase++;
		max_hp *= 2;
		hp *= 2;
	}
}

void Enemy::Phase2() {
	Shoot2();
	static float vecx = 250.0f;
	float hw = (renderer->GetWidth() * transform->scale.x / 2);
	float sw = WinApp::GetScreenWidth() - hw;
	transform->position.x = max(hw, min(sw, transform->position.x + vecx * TimeManager::GetDeltaTime()));
	if (transform->position.x >= sw || transform->position.x <= hw) {
		vecx = -vecx;
	}
}

void Enemy::Hit(float damage)
{
	hp -= damage;
}

void Enemy::Shoot1() {
	//ÃÑ¾Ë ¹ß»ç
	static float cool = 0.0f;
	if (cool > 0.0f) {
		cool -= TimeManager::GetDeltaTime();
		return;
	}
	cool = 0.3f + (float)(rand() % 8) / 10.0f;
	float mx = bm->player->transform->position.x;
	float my = bm->player->transform->position.y;
	float px = transform->position.x;
	float py = transform->position.y;
	float dx = mx - px;
	float dy = my - py - 60.0f;
	float angle = atan2(dy, dx) * 180 / PI;

	Bullet* b = new Bullet(L"resources/player.png");
	Scene::GetCurrentScene()->PushBackGameObject(b);
	bm->PushBackBullet(b);

	b->transform->position = this->transform->position;
	b->transform->SetScale(0.045f, 0.045f);
	b->transform->position.y += 60.0f;
	b->minSpeed = 200.0f;
	b->speedRate = 200.0f;
	b->speed = 300.0f;
	b->angle = angle;
	b->angleRate = (float)(rand() % 21 - 10);
	b->damage = 7.5f;
	b->transform->rotatingAngle = angle - 90.0f;

	for (float i = 0.0f; i < 4.0f; i += 1.0f) {
		Bullet* b = new Bullet(L"resources/bullet_2.png");
		Scene::GetCurrentScene()->PushBackGameObject(b);
		bm->PushBackBullet(b);

		b->transform->position = this->transform->position;
		b->transform->SetScale(0.025f, 0.025f);
		b->transform->position.y += 40.0f;
		b->transform->position.x -= 130.0f;
		b->transform->position.x += 90.0f * i;
		b->minSpeed = 200.0f;
		b->speedRate = 200.0f;
		b->speed = 300.0f;
		b->angle = 90;
		b->angleRate = (float)(rand() % 21 - 10);
		b->damage = 3.0f;
	}
}

void Enemy::Shoot2() {
	//ÃÑ¾Ë ¹ß»ç
	static float cool = 0.0f;
	if (cool > 0.0f) {
		cool -= TimeManager::GetDeltaTime();
		return;
	}
	cool = 0.5f;
	float mx = bm->player->transform->position.x;
	float my = bm->player->transform->position.y;
	float px = transform->position.x;
	float py = transform->position.y;
	float dx = mx - px;
	float dy = my - py - 60.0f;
	float angle = atan2(dy, dx) * 180 / PI;

	if (!(angle > 0.0f && angle <= 180.0f) || hp < max_hp * 0.1f) {
		Bullet* b = new Bullet(L"resources/player.png");
		Scene::GetCurrentScene()->PushBackGameObject(b);
		bm->PushBackBullet(b);

		b->transform->position = this->transform->position;
		b->transform->SetScale(0.045f, 0.045f);
		b->transform->position.y += 60.0f;
		b->minSpeed = 200.0f;
		b->speedRate = 200.0f;
		b->speed = 300.0f;
		b->angle = angle;
		b->damage = 20.5f;
		b->transform->rotatingAngle = angle - 90.0f;
	}

	for (float j = 0.0f; j < 4.0f; j += 1.0f) {
		for (float i = 0.0f; i < 4.0f; i += 1.0f) {
			Bullet* b = new Bullet(L"resources/bullet_2.png");
			Scene::GetCurrentScene()->PushBackGameObject(b);
			bm->PushBackBullet(b);

			b->transform->position = this->transform->position;
			b->transform->SetScale(0.025f, 0.025f);
			b->transform->position.y += 40.0f + j * 5.0f;
			b->transform->position.x -= 130.0f;
			b->transform->position.x += 90.0f * i;
			b->minSpeed = 200.0f;
			b->speedRate = 200.0f + j * 100.0f;
			b->speed = 300.0f;
			b->angle = 90;
			b->angleRate = (float)(rand() % 21 - 10);
			b->damage = 1.5f;
		}
	}
}