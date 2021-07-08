#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Enemy.h"
class BulletManager :
	public GameObject
{
public:
	std::list<Bullet*> bulletList;	//총알 저장 리스트

	Enemy* enemy;					//적 등록
									//필요하다면 List나
									//EnemyManager 등으로 구현 가능

	void CheckCollision();				//충돌 확인
	Bullet* PushBackBullet(Bullet* b);	//총알 생성시 해주기
	void Destroy(Bullet* b);			//총알 삭제 함수
	
	virtual void LateUpdate();
private:
	std::list<Bullet*> destroyed;
	void RemoveDestroyed();				//실제 총알 삭제 처리

public:
	BulletManager();
	~BulletManager();
};

