#pragma once
#include "GameObject.h"
#include "AABBCollider.h"

class Bullet :
	public GameObject
{
public:
	AABBCollider* col;
	float speed, speedRate, minSpeed;	//속도, 가속도, 최소속도
	float angle, angleRate;//각도, 각속도
	float damage;//데미지

	Bullet(const wchar_t* imagePath);
	~Bullet();

	virtual void Update();
	void Move();			//움직이는함수
	virtual void OnDestroy();//삭제시 함수

	bool CheckOutOfScreen();	//총알 화면 벗어났나 체크
};

