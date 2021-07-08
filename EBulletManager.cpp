#include "stdafx.h"
#include "EBulletManager.h"
#include "Scene.h"

void EBulletManager::CheckCollision()
{
	for (auto& i : bulletList)
	{
		if (i->col->Intersected(player->col))
		{
			player->Hit(i->damage);
			Destroy(i);
		}
		if (i->CheckOutOfScreen())
		{
			Destroy(i);
		}
	}
}



EBulletManager::EBulletManager()
{}
EBulletManager::~EBulletManager()
{}

Bullet* EBulletManager::PushBackBullet(Bullet* b)
{
	bulletList.push_back(b);
	return b;
}

void EBulletManager::Destroy(Bullet* b)
{
	destroyed.push_back(b);
}

void EBulletManager::RemoveDestroyed()
{
	for (auto& i : destroyed)
	{
		bulletList.remove(i);
		Scene::GetCurrentScene()->Destroy(i);
	}
	destroyed.clear();
}

void EBulletManager::LateUpdate()
{
	CheckCollision();
	RemoveDestroyed();
}