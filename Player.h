#pragma once
#include "GameObject.h"
#include "BulletManager.h"
#include "AABBCollider.h"

class Player :
	public GameObject
{
public:
	Player(const wchar_t* imagePath, float hp = 100.0f);
	~Player();

	BulletManager* bm;		//총알 관리자 클래스
	float moveSpeed;		//이동 속도
	AABBCollider* col;
	float hp, max_hp, add_hp;

	virtual void Update();	//업데이트 처리
	virtual void LateUpdate();
	void Move();
	void Shoot();
	void Hit(float damage);
};

