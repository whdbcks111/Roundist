#include "stdafx.h"
#include "D2DApp.h"
#include "Framework.h"

D2DApp::D2DApp(WinApp* winApp) : winApp(winApp), factory(nullptr), wicFactory(nullptr), renderTarget(nullptr), example(nullptr)
{
}

bool D2DApp::Initialize()
{
	HRESULT hr = S_OK;
	hr = CreateDeviceIndependentResources();
	if (!SUCCEEDED(hr))
		return false;
	hr = CreateDeviceResources();
	if (!SUCCEEDED(hr))
		return false;
	return true;
}

void D2DApp::Uninitialize()
{
	DiscardDeviceResources();
	DiscardDeviceIndependentResources();
}

HRESULT D2DApp::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;
	const D2D1_FACTORY_OPTIONS opts = { D2D1_DEBUG_LEVEL_INFORMATION };

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

	if (SUCCEEDED(hr))
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	return hr;
}

HRESULT D2DApp::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!renderTarget)
	{
		RECT rc;
		GetClientRect(winApp->GetHWND(), &rc);
		D2D1_SIZE_U size;
		if (!winApp->GetFullScreened())
			size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
		else
			size = D2D1::SizeU(winApp->GetScreenWidth(), winApp->GetScreenHeight());
		hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(winApp->GetHWND(), size), &renderTarget);

	}
	return hr;
}

void D2DApp::DiscardDeviceResources()
{
	SAFE_RELEASE(renderTarget);
}

void D2DApp::DiscardDeviceIndependentResources()
{
	SAFE_RELEASE(renderTarget);
	SAFE_RELEASE(factory);
	SAFE_RELEASE(wicFactory);
}

HRESULT D2DApp::LoadBitmapFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** bitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRESULT hr = wicFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = wicFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = wicFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(pSource, destinationWidth, destinationHeight, WICBitmapInterpolationModeCubic);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(pScaler, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = renderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, bitmap);
	}

	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);

	return hr;

}

ID2D1HwndRenderTarget* D2DApp::GetRenderTarget()
{
	return renderTarget;
}

IWICImagingFactory* D2DApp::GetImagingFactory()
{
	return wicFactory;
}

ID2D1Factory* D2DApp::GetFactory()
{
	return factory;
}


void D2DApp::Render()
{
	CreateDeviceResources();

	// 렌더타겟의 크기를 얻음.
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();

	renderTarget->BeginDraw();
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	// 왼쪽 위 모서리에 비트맵 bitmap을 그림.
	D2D1_SIZE_F size = example->GetSize();
	renderTarget->DrawBitmap(example, D2D1::RectF(0.0f, 0.0f, size.width, size.height));

	HRESULT hr = renderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		DiscardDeviceResources();
	}

}

void D2DApp::BeginRender()
{
	//반드시 EndRender도 호출해야함

	//장치 의존적 자원이 없을경우 생성
	CreateDeviceResources();

	// 렌더타겟의 크기를 얻음.
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();

	renderTarget->BeginDraw();
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void D2DApp::EndRender()
{
	HRESULT hr = renderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		DiscardDeviceResources();
	}
}
