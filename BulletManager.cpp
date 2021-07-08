#include "stdafx.h"
#include "BulletManager.h"
#include "Scene.h"

void BulletManager::CheckCollision()
{
	for (auto& i : bulletList)
	{
		if (i->col->Intersected(enemy->col))
		{
			enemy->Hit(i->damage);
			Destroy(i);
		}
		if (i->CheckOutOfScreen())
		{
			Destroy(i);
		}
	}
}



BulletManager::BulletManager()
{}
BulletManager::~BulletManager()
{}

Bullet* BulletManager::PushBackBullet(Bullet* b)
{
	bulletList.push_back(b);
	return b;
}

void BulletManager::Destroy(Bullet* b)
{
	destroyed.push_back(b);
}

void BulletManager::RemoveDestroyed()
{
	for (auto& i : destroyed)
	{
		bulletList.remove(i);
		Scene::GetCurrentScene()->Destroy(i);
	}
	destroyed.clear();
}

void BulletManager::LateUpdate()
{
	CheckCollision();
	RemoveDestroyed();
}