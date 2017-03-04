#include "Graphics.h"

Graphics::Graphics()
	:m_pDirect2DFactory(NULL),
	 m_pRenderTarget(NULL),
	 m_bIsInitialized(false)
{
}


Graphics::~Graphics()
{

	//GameUtils::ReleaseCOM(&m_pDirect2DFactory);
	//GameUtils::ReleaseCOM(&m_pRenderTarget);

	if (m_pDirect2DFactory != NULL) {
		m_pDirect2DFactory->Release();
		m_pDirect2DFactory = NULL;
	}

	if (m_pRenderTarget != NULL) {
		m_pRenderTarget->Release();
		m_pRenderTarget = NULL;
	}

}

HRESULT Graphics::CreateDeviceResource(HWND targetHWND)
{

	RECT rect;
	GetClientRect(targetHWND, &rect);

	HRESULT hr = m_pDirect2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			targetHWND,
			D2D1::SizeU(
				rect.right - rect.left,
				rect.bottom - rect.top)
		),
		&m_pRenderTarget
	);

	return hr;
}

void Graphics::ReleaseDeviceResource()
{

	//ReleaseCOM::GameUtils(&m_pRenderTarget);

	if (m_pRenderTarget != NULL) {
		m_pRenderTarget->Release();
		m_pRenderTarget = NULL;
	}

}

HRESULT Graphics::initialize(HWND TargetHWND)
{
	
	//HRESULT hr =  D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2DFactory);
	//hr = CreateDeviceResource(TargetHWND);

	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2DFactory) != S_OK) {

		return S_FALSE;
	}

	if (CreateDeviceResource(TargetHWND) != S_OK) {

		return S_FALSE;
	}

	m_bIsInitialized = true;

	return S_OK;
}