#include "stdafx.h"
#include "SheetAnimation.h"
#include "Scene.h"
#include "TimeManager.h"

SheetAnimation::SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int width, int height, int length)
	:Animation(state, fps), width(width), height(height), rowCount(0)
{
	sheet = Scene::GetCurrentScene()->GetRenderingManager()->LoadBitmapFromFile(sheetPath, 0, 0);
	if (sheet)
	{
		this->length = length;
		if (width != 0)
			rowCount = sheet->bitmap->GetPixelSize().width / width;
		if (rowCount == 0)
			printf("rowCount==0\n");

		for (int i = 0; i < length; ++i)
		{
			if (rowCount)
			{
				D2D1_RECT_F sourceRect;
				sourceRect.left = (float)((i % rowCount) * width);
				sourceRect.top = (float)((i / rowCount) * height);
				sourceRect.right = sourceRect.left + width;
				sourceRect.bottom = sourceRect.top + height;
				sourceRects.push_back(sourceRect);
			}
		}
	}

}

SheetAnimation::SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int rowCount, int length)
	:Animation(state, fps), rowCount(rowCount), width(0), height(0)
{
	sheet = Scene::GetCurrentScene()->GetRenderingManager()->LoadBitmapFromFile(sheetPath, 0, 0);
	if (sheet)
	{
		this->length = length;
		if (rowCount != 0)
		{
			width = sheet->bitmap->GetPixelSize().width / rowCount;
			height = sheet->bitmap->GetPixelSize().height / (((length - 1) / rowCount) + 1);
		}
		if (rowCount == 0)
		{
			printf("rowCount==0\n");
			this->length = 0;
			return;
		}

		for (int i = 0; i < length; ++i)
		{
			if (rowCount)
			{
				D2D1_RECT_F sourceRect;
				sourceRect.left = (float)((i % rowCount) * width);
				sourceRect.top = (float)((i / rowCount) * height);
				sourceRect.right = sourceRect.left + width;
				sourceRect.bottom = sourceRect.top + height;
				sourceRects.push_back(sourceRect);
			}
		}
		currentSourceRect = sourceRects[currentFrame];
	}
}

D2D1_RECT_F* SheetAnimation::GetSourceRect()
{
	return &currentSourceRect;
}

Sprite* SheetAnimation::GetCurrentSprite()
{
	return sheet;
}

int SheetAnimation::GetAnimationWidth()
{
	return width;
}
int SheetAnimation::GetAnimationHeight()
{
	return height;
}


Sprite* SheetAnimation::UpdateAnim()
{
	if (length == 0)
		return nullptr;
	//printf("d");
	frameTime += TimeManager::GetDeltaTime();
	//다음 프레임으로 전환할지 확인
	if (frameTime > reciprocalFPS)
	{
		frameTime = 0.0f;
		++currentFrame;
		if (currentFrame >= length)
		{
			currentFrame = 0;
		}
		currentSourceRect = sourceRects[currentFrame];
	}
	return sheet;
}
