#pragma once
#pragma comment(lib, "Windowscodecs.lib")

#include <Windows.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <cassert>
#include "GameDefine.h"

class Graphics
{
private:
	ID2D1Factory          * m_pDirect2DFactory;
	ID2D1HwndRenderTarget * m_pRenderTarget;

	IWICImagingFactory    * m_pIWICFactory;

	HWND m_hwnd;

	bool m_bIsInitialized;

public:
	Graphics();
	~Graphics();

	HRESULT initialize(HWND targetHWND);

	HRESULT CreateDeviceResource(HWND hWnd);
	void ReleaseDeviceResource();

	void BeginDraw() {
		assert(m_bIsInitialized == true);
		m_pRenderTarget->BeginDraw(); 
	}
	HRESULT EndDraw() {
		assert(m_bIsInitialized == true);
		return m_pRenderTarget->EndDraw(); 
	}

	void ClearScreen(D2D1::ColorF color);

	void OnResize(UINT width, UINT height);

	ID2D1HwndRenderTarget* GetRenderTaget() { return m_pRenderTarget; }
	IWICImagingFactory* GetImagingFactory() { return m_pIWICFactory; }
};

