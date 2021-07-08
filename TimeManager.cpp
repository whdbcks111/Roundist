#include "stdafx.h"
#include "TimeManager.h"
TimeManager::TimeManager(){}
TimeManager::~TimeManager(){}

float TimeManager::deltaTime;
void TimeManager::UpdateTime()
{
	static DWORD oldTime = timeGetTime();

	DWORD curTime = timeGetTime();
	deltaTime = (float)(curTime - oldTime)*0.001f;
	oldTime = curTime;
}

float TimeManager::GetDeltaTime()
{//getterÇÔ¼ö
	return deltaTime;
}
