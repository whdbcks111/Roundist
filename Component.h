#pragma once
#include "stdafx.h"

class Component
{
public:
	Component();
	virtual ~Component();

public:

	virtual void Initialize() {};
	virtual void Update() = 0;
	virtual void Uninitialze() {};

public:
	bool isActive;
};

