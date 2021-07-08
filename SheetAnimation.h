#pragma once
#include "Animation.h"

class SheetAnimation
	:public Animation
{
public:
	//pixelWidth,Height: 한 프레임의 가로,세로크기
	//ex)4*4 sheet이고, 시트의 이미지 크기가 1024*1024일 경우, pixelWidth,Heigt는 각각256,256을 입력
	SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int pixelWidth, int pixelHeight, int length);

	//row: 애니메이션 시트의 가로 이미지 개수 ex)4x4 sheet일 경우 4를 입력, ex)8*4 sheet일 경우 8을 입력, length:이미지 수
	SheetAnimation(const int state, float fps, const wchar_t* sheetPath, int row, int length);
public:
	Sprite* sheet;
	int width, height;	//애니메이션을 자를 단위
	int rowCount;

public:
	//프레임워크 내부적으로 작동하는 함수입니다.
	virtual D2D1_RECT_F* GetSourceRect();

public:
	virtual Sprite* GetCurrentSprite();
	virtual int GetAnimationWidth();
	virtual int GetAnimationHeight();
	virtual Sprite* UpdateAnim();
	std::vector<D2D1_RECT_F> sourceRects;
	D2D1_RECT_F currentSourceRect;

};

