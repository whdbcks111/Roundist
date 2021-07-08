#pragma once
#include "RenderingManager.h"

//하나의 애니메이션을 관리할 객체입니다.
//추상 클래스입니다.
//게임 제작시엔 ListAnimation, SheetAnimation을 사용합니다.
//스켈레톤 애니메이션은 구현되지 않았으며, 해당 클래스와 별개로 구현하셔야 합니다.
class Animation
{
public:
	Animation(const int state, float fps);
public:
	const int state;		//애니메이션의 state number
	int currentFrame;			//현재 frame number
	float frameTime;		//현재 애니메이션의 시간
	int length;				//애니메이션의 프레임 개수
protected:
	float fps;				//애니메이션을 실행할 fps
	float reciprocalFPS;	//1/fps

public:
	void SetFPS(float fps);
	float GetFPS(float fps);
public:
	virtual Sprite* UpdateAnim() = 0;
	virtual Sprite* GetCurrentSprite() = 0;
	virtual int GetAnimationWidth() = 0;
	virtual int GetAnimationHeight() = 0;
	virtual D2D1_RECT_F* GetSourceRect();
	virtual void Reset();
};

