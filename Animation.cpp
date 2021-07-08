#include "stdafx.h"
#include "Animation.h"

Animation::Animation(const int state, float fps)
	:state(state), fps(fps), currentFrame(0), frameTime(0.0f), reciprocalFPS(1.0f / fps), length(0)
{
}

void Animation::SetFPS(float fps)
{
	this->fps = fps;
	reciprocalFPS = 1.0f / fps;
}

float Animation::GetFPS(float fps)
{
	return fps;
}

D2D1_RECT_F* Animation::GetSourceRect()
{
	return nullptr;
}

void Animation::Reset()
{
	currentFrame = 0;
	frameTime = 0.0f;
}
