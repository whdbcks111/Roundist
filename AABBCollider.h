#pragma once
#include "Transform.h"
class AABBCollider
{
public:
	float left;
	float right;
	float top;
	float bottom;
	Transform* transform;

	bool Intersected(AABBCollider* col);

	AABBCollider(Transform* transform,
		float left, float right, float top, float bottom);
	~AABBCollider();
};

