#include "Graphics.h"

Graphics::Graphics()
	:m_pDirect2DFactory(NULL),
	 m_pRenderTarget(NULL),
	 m_bIsInitialized(false)
{
}

Graphics::~Graphics()
{
	GameUtils::SafeRelease(&m_pDirect2DFactory);
	GameUtils::SafeRelease(&m_pIWICFactory);
	GameUtils::SafeRelease(&m_pRenderTarget);
}

HRESULT Graphics::CreateDeviceResource(HWND targetHWND)
{
	assert(targetHWND);

	RECT rect;
	GetClientRect(targetHWND, &rect);

	HRESULT hr = m_pDirect2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			targetHWND,
			D2D1::SizeU(
				rect.right,
				rect.bottom)
		),
		&m_pRenderTarget
	);

	return hr;
}

void Graphics::ReleaseDeviceResource()
{
	GameUtils::SafeRelease(&m_pRenderTarget);
}

HRESULT Graphics::initialize(HWND TargetHWND)
{
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2DFactory) != S_OK) { return S_FALSE; }
	if (CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&m_pIWICFactory)) { return S_FALSE; }
	if (CreateDeviceResource(TargetHWND) != S_OK)										   { return S_FALSE; }

	m_bIsInitialized = true;

	return S_OK;
}

void Graphics::ClearScreen(D2D1::ColorF color) 
{
	assert(m_bIsInitialized == true);
  
	if (m_pRenderTarget) { m_pRenderTarget->Clear(color); }
}

void Graphics::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
