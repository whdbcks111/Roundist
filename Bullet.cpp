#include "stdafx.h"
#include "Bullet.h"
#include "TimeManager.h"
Bullet::Bullet(const wchar_t* imagePath)
	:GameObject(imagePath)
{
	col = new AABBCollider(
		transform,
		renderer->GetWidth() * (-0.5f),
		renderer->GetWidth() * 0.5f,
		renderer->GetHeight() * (-0.5f),
		renderer->GetHeight() * 0.5f
	);
	speed = 0.0f;
	speedRate = 0.0f;
	angle = 0.0f;
	angleRate = 0.0f;
	damage = 0.0f;
}
void Bullet::Move()
{
	float rad = angle * PI / 180;

	transform->position.x
		+= (speed * cos(rad) * TimeManager::GetDeltaTime());
	transform->position.y
		+= (speed * sin(rad) * TimeManager::GetDeltaTime());

	speed += speedRate * TimeManager::GetDeltaTime();
	speed = max(minSpeed, speed);
	angle += angleRate * TimeManager::GetDeltaTime();
}

Bullet::~Bullet() {
	SAFE_DELETE(col);
}


void Bullet::OnDestroy() {
}

bool Bullet::CheckOutOfScreen()
{
	//총알의 포지션과, 총알의 이미지 크기를 고려해서
	//총알이 밖에 나갔는 지 판정해주어야 함.
	int sw = WinApp::GetScreenWidth();					//윈도우의 가로 길이
	int sh = WinApp::GetScreenHeight();					//윈도우의 세로 길이
	int bw = renderer->GetWidth() * (int)transform->scale.x;	//이미지의 가로 길이*스케일
	int bh = renderer->GetHeight() * (int)transform->scale.y;//이미지의 세로 길이*스케일

	return transform->position.x<bw * (-1.0f) ||	//총알이 왼쪽 끝을 나갔거나
		transform->position.x>bw + sw ||			//총알이 오른 끝을 나갔거나
		transform->position.y<bh * (-1.0f) ||		//총알이 위쪽 끝을 나갔거나
		transform->position.y>bh + sh;				//총알이 아래 끝을 나갔거나
}

void Bullet::Update()
{
	Move();
}

