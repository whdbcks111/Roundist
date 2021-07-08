#include "stdafx.h"
#include "ListAnimation.h"
#include "TimeManager.h"
#include "Scene.h"


ListAnimation::ListAnimation(const int state, float fps)
	:Animation(state, fps), iter(sprites.begin())
{
}

ListAnimation::~ListAnimation()
{
}

Sprite* ListAnimation::UpdateAnim()
{
	if (length == 0)
		return nullptr;
	frameTime += TimeManager::GetDeltaTime();

	//다음 프레임으로 전환할지 확인
	if (frameTime > reciprocalFPS)
	{
		frameTime = 0.0f;
		++currentFrame;
		++iter;
		if (currentFrame >= length)
		{
			currentFrame = 0;
			iter = sprites.begin();
		}
	}
	return *iter;
}

Sprite* ListAnimation::GetCurrentSprite()
{
	if (length == 0)
		return nullptr;
	return *iter;
}

Vector2 ListAnimation::GetAnimationSize()
{
	if (length == 0)
		return Vector2();
	D2D1_SIZE_U u;
	u = (*iter)->bitmap->GetPixelSize();
	return Vector2((float)u.width,(float)u.height);
}

int ListAnimation::GetAnimationWidth()
{
	return (*iter)->bitmap->GetPixelSize().width;
}


int ListAnimation::GetAnimationHeight()
{
	return (*iter)->bitmap->GetPixelSize().height;
}

void ListAnimation::Reset()
{
	Animation::Reset();
	iter = sprites.begin();
}

void ListAnimation::PushBackSprite(Sprite* sprite)
{
	sprites.push_back(sprite);
	++length;
}

void ListAnimation::PushBackSprite(const wchar_t* path)
{
	Sprite* s = Scene::GetCurrentScene()->GetRenderingManager()->LoadBitmapFromFile(path, 0, 0);
	sprites.push_back(s);
	++length;
}
