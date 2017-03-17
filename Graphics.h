#pragma once

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
	//TODO:타겟 윈도우 핸들이 필요한지
	ID2D1Factory * m_pDirect2DFactory;
	ID2D1HwndRenderTarget * m_pRenderTarget;

	//THISLINE:브러쉬 테스트
	ID2D1SolidColorBrush * brush;

	bool m_bIsInitialized;

private:
	HRESULT CreateDeviceResource(HWND hWnd);
	void ReleaseDeviceResource();

public:
	Graphics();
	~Graphics();

	HRESULT initialize(HWND targetHWND);

	void BeginDraw() {

		assert(m_bIsInitialized == true);
		m_pRenderTarget->BeginDraw(); 
	}
	void EndDraw() {

		assert(m_bIsInitialized == true);
		m_pRenderTarget->EndDraw(); 
	}

	void ClearScreen(D2D1::ColorF color);

	void PutPixel(D2D_POINT_2F point);

};

