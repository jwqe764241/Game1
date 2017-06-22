#pragma once
//TODO: 프로젝트 설정으로 변경할것 포함할것 ##3
#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "Dwrite.lib")

#include <Windows.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <cassert>

#include <Sources/GameDefine.h>

class Graphics
{
private:
	static Graphics* m_pInstance;

	ID2D1Factory          * m_pDirect2DFactory;
	ID2D1HwndRenderTarget * m_pRenderTarget;

	IWICImagingFactory    * m_pIWICFactory;
	IDWriteFactory		  * m_pDWriteFactory;

	HWND m_hwnd;

	bool m_bIsInitialized;

public:
	static Graphics* GetInstance();

	Graphics();
	~Graphics();

	HRESULT initialize(HWND targetHWND);

	HRESULT CreateDeviceResource(HWND hWnd);
	void    ReleaseDeviceResource();

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

	ID2D1HwndRenderTarget * GetRenderTarget() { return m_pRenderTarget; }
	IWICImagingFactory* GetImagingFactory()   { return m_pIWICFactory; }
	ID2D1Factory* GetD2DFactory()			  { return m_pDirect2DFactory; }
	IDWriteFactory* GetDWriteFactory()		  { return m_pDWriteFactory; }
};

