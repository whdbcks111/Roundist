#include "stdafx.h"
#include "RenderInfo.h"
#include "Framework.h"

RenderInfo::RenderInfo()
	: Component(), currentSprite(nullptr), alpha(1.0f), initialized(false),width(0),height(0)
{
}

RenderInfo::RenderInfo(Sprite* startSprite, float alpha)
	:Component(),currentSprite(startSprite),alpha(alpha),initialized(true)
{
	//Sprite Å©±â ¹Þ¾Æ¿È
	if (startSprite)
	{
		if (startSprite->bitmap)
		{
			D2D1_SIZE_U size = startSprite->bitmap->GetPixelSize();
			width = size.width;
			height = size.height;
		}
		else
		{
			RenderInfo();
		}
	}
	else
	{
		RenderInfo();
	}
}

Sprite* RenderInfo::GetCurrentSprite()
{
	return currentSprite;
}

float RenderInfo::GetAlpha()
{
	return alpha;
}

bool RenderInfo::GetInitialized()
{
	return initialized;
}

int RenderInfo::GetWidth()
{
	return width;
}

int RenderInfo::GetHeight()
{
	return height;
}

D2D1_RECT_F* RenderInfo::GetSourceRect()
{
	return nullptr;
}
