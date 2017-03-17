#include "Graphics.h"

Graphics::Graphics()
	:m_pDirect2DFactory(NULL),
	 m_pRenderTarget(NULL),
	 m_bIsInitialized(false)
{
}

Graphics::~Graphics()
{
	/*if (m_pDirect2DFactory != NULL) {
		m_pDirect2DFactory->Release();
		m_pDirect2DFactory = NULL;
	}

	if (m_pRenderTarget != NULL) {
		m_pRenderTarget->Release();
		m_pRenderTarget = NULL;
	}*/

	//
	GameUtils::SafeRelease(&m_pDirect2DFactory);
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
	//if (m_pRenderTarget != NULL) {
	//	m_pRenderTarget->Release();
	//	m_pRenderTarget = NULL;
	//}

	GameUtils::SafeRelease(&m_pRenderTarget);
}

HRESULT Graphics::initialize(HWND TargetHWND)
{
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2DFactory) != S_OK) { return S_FALSE; }
	if (CreateDeviceResource(TargetHWND) != S_OK)										   { return S_FALSE; }

	//THISLINE:테스트 브러쉬 초기화
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);

	m_bIsInitialized = true;

	return S_OK;
}

void Graphics::ClearScreen(D2D1::ColorF color) 
{
	assert(m_bIsInitialized == true);

	m_pRenderTarget->Clear(color);
}

void Graphics::PutPixel(D2D_POINT_2F point)
{
	assert(m_bIsInitialized == true);

	m_pRenderTarget->DrawRectangle(
		D2D1::RectF(
		point.x + 5.0f,
		point.y + 5.0f,
		point.x - 5.0f,
		point.y - 5.0f)
		, brush);
	//delete brush;
}