#include "stdafx.h"
#include "AABBCollider.h"


AABBCollider::AABBCollider(Transform* transform,
	float left, float right, float top, float bottom)
{
	this->transform = transform;
	this->left	= left;
	this->right = right;
	this->top	= top;
	this->bottom = bottom;
}

bool AABBCollider::Intersected(AABBCollider* other)
{
	float aLeft, bLeft;
	float aRight, bRight;
	float aTop, bTop;
	float aBottom, bBottom;
	aLeft = left * transform->scale.x
		+ transform->position.x;
	aRight = right * transform->scale.x
		+ transform->position.x;
	aTop = top * transform->scale.y
		+ transform->position.y;
	aBottom = bottom * transform->scale.y
		+ transform->position.y;
	bLeft = other->left * other->transform->scale.x
		+ other->transform->position.x;
	bRight = other->right * other->transform->scale.x
		+ other->transform->position.x;
	bTop = other->top * other->transform->scale.y
		+ other->transform->position.y;
	bBottom = other->bottom * other->transform->scale.y
		+ other->transform->position.y;

	return
		!(
		(aRight < bLeft) || (bRight < aLeft) ||
			(aBottom < bTop) || (bBottom < aTop)
			);
}


AABBCollider::~AABBCollider()
{
}
