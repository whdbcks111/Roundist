#include "stdafx.h"
#include "GameObject.h"
#include "Framework.h"

GameObject::GameObject(Vector2 position, float angle, Vector2 scale)
	: transform(new Transform(position, angle, scale)),
	renderer(new RenderInfo()),
	isActive(true)

{
}


GameObject::GameObject(const wchar_t* imagePath, Vector2 position, float angle, Vector2 scale)
	:transform(new Transform(position, angle, scale)), 
	renderer(new RenderInfo(Scene::GetCurrentScene()->GetRenderingManager()->LoadBitmapFromFile(imagePath, 0, 0))),
	isActive(true)
{
}

GameObject::GameObject(RenderInfo* renderInfo, Vector2 position, float angle, Vector2 scale)
	:transform(new Transform(position, angle, scale)),
	renderer(renderInfo),
	isActive(true)
{
}


GameObject::~GameObject()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(transform);
}