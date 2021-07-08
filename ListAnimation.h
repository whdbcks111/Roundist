#pragma once
#include "Animation.h"

//여러 이미지를 받아서 애니메이션을 구현합니다.

class ListAnimation
	:public Animation
{
public:
	ListAnimation(const int state, float fps); //초기화 단계에서 PushBackSprite로 list 완성
	virtual ~ListAnimation();
public:
	std::list<Sprite*> sprites;
	std::list<Sprite*>::iterator iter;			//현재 Sprite값

public:
	//프레임워크 내부적으로 작동하는 함수입니다.
	virtual Sprite* UpdateAnim();

public:
	virtual Sprite* GetCurrentSprite();			//현재 Sprite 반환
	virtual Vector2 GetAnimationSize();			//애니메이션의 대표 이미지 사이즈 반환
	virtual int GetAnimationWidth();
	virtual int GetAnimationHeight();
	virtual void Reset();						//애니메이션 진행 상황 초기화
	void PushBackSprite(Sprite* sprite);		//이미지 등록
	void PushBackSprite(const wchar_t* path);	//이미지 등록
};

