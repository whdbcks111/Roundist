#include "stdafx.h"
#include "RenderingManager.h"
#include "Framework.h"


RenderingManager::RenderingManager(D2DApp* d2dApp) :d2dApp(d2dApp)
{
}

RenderingManager::~RenderingManager()
{
	for (auto& i : spriteList)
	{
		SAFE_RELEASE(i->bitmap);
		SAFE_DELETE(i);
	}
	spriteList.clear();
}

Sprite* RenderingManager::LoadBitmapFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight)
{
	Sprite* sprite = nullptr;

	for (auto& i : spriteList)
	{
		if (wcscmp(i->uri, uri) == 0)
			return i;
	}
	sprite = new Sprite();
	if (SUCCEEDED(d2dApp->LoadBitmapFromFile(uri, 0, 0, &sprite->bitmap)))
	{
		sprite->uri = uri;
		spriteList.push_back(sprite);
		return sprite;
	}
	else 
	{
		SAFE_DELETE(sprite);
		printf("이미지 로드 오류 발생\n");
		return nullptr;
	}
}

void RenderingManager::BeginRender()
{
	d2dApp->BeginRender();
}

//수업 내용에서 수정된 부분입니다.
void RenderingManager::Render(RenderInfo* renderInfo, Transform* transform)
{
	Sprite* currentSprite = renderInfo->GetCurrentSprite();
	float alpha = renderInfo->GetAlpha();
	ID2D1HwndRenderTarget* renderTarget = d2dApp->GetRenderTarget();

	if (!renderTarget)
	{
		printf("RenderingManger::Render 실패, 렌더타겟이 없습니다.\n");
		return;
	}

	if (!currentSprite || !currentSprite->bitmap)
	{
		//printf("RenderingManger::Render 실패, 스프라이트가 없습니다.\n");
		return;
	}

	renderInfo->UpdateRenderInfo();

	//D2D1_SIZE_U size;
	//size = currentSprite->bitmap->GetPixelSize();
	Vector2 size;
	size.x = (float)renderInfo->GetWidth();
	size.y = (float)renderInfo->GetHeight();

	Point positioningCenter;
	positioningCenter.x = transform->position.x - transform->positioningCenter.x;
	positioningCenter.y = transform->position.y - transform->positioningCenter.y;

	D2D1_RECT_F rect;
	rect.left = positioningCenter.x - size.x * 0.5f;//* o->scale.x;
	rect.top = positioningCenter.y - size.y * 0.5f;// *o->scale.y;
	rect.right = positioningCenter.x + size.x * 0.5f;// *o->scale.x;
	rect.bottom = positioningCenter.y + size.y * 0.5f;// *o->scale.y;

	D2D1_RECT_F* sourceRect = nullptr;
	sourceRect = renderInfo->GetSourceRect();

	Point scalingCenter;
	scalingCenter.x = positioningCenter.x + transform->scalingCenter.x;
	scalingCenter.y = positioningCenter.y + transform->scalingCenter.y;

	Point rotatingCenter;
	rotatingCenter.x = positioningCenter.x + transform->rotatingCenter.x;
	rotatingCenter.y = positioningCenter.y + transform->rotatingCenter.y;

	renderTarget->SetTransform(
		D2D1::Matrix3x2F::Scale(
			transform->scale.x,
			transform->scale.y,
			scalingCenter)
		* D2D1::Matrix3x2F::Rotation(
			transform->rotatingAngle,
			rotatingCenter
		));
	renderTarget->DrawBitmap(currentSprite->bitmap, &rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);
	
}

void RenderingManager::EndRender()
{
	d2dApp->EndRender();
}
