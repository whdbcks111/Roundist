#pragma once
#include "stdafx.h"
#include "WinApp.h"

struct Sprite {
	const wchar_t* uri;
	ID2D1Bitmap* bitmap;
};

class D2DApp
{
public:
	D2DApp(WinApp* winApp);
private:
	WinApp* winApp;

public:
	bool Initialize();
	void Uninitialize();

private:
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void DiscardDeviceIndependentResources();

public:
	ID2D1Bitmap* example;
	void Render();
	void BeginRender();
	void EndRender();
	HRESULT LoadBitmapFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** bitmap);

private:
	ID2D1Factory* factory;
	IWICImagingFactory* wicFactory;
	ID2D1HwndRenderTarget* renderTarget;
	
public:
	ID2D1HwndRenderTarget* GetRenderTarget();
	IWICImagingFactory* GetImagingFactory();
	ID2D1Factory* GetFactory();
};

