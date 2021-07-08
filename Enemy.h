#pragma once
#include "GameObject.h"
#include "AABBCollider.h"

class EBulletManager;

class Enemy :
	public GameObject
{
public:
	float hp, max_hp;
	int phase;
	float ptime;

	EBulletManager* bm;
	AABBCollider* col;

	virtual void Update();
	virtual void LateUpdate();
	Enemy(const wchar_t* imagePath, float hp);
	void Hit(float damage);
	void Phase1();
	void Phase2();
	void Shoot1();
	void Shoot2();
	~Enemy();
};

