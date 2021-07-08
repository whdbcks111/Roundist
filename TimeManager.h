#pragma once
class TimeManager
{
	friend class Framework;
public:
	TimeManager();
	~TimeManager();
private:
	static float deltaTime;

	static void UpdateTime();
public:
	static float GetDeltaTime();
};

