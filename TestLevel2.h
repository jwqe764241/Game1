#pragma once

#include "Level.h"


//수정필요
class TestLevel2 : public Level
{
private:
	IWICBitmapDecoder	  * m_pDecoder;
	IWICBitmapFrameDecode * m_pFrameDecode;
	IWICFormatConverter	  * m_pConvertedBitmap;
	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;
	ID2D1Bitmap	* m_pBitmap;

	wchar_t * m_lpszFilePath;
	bool m_bIsInitialized;
public:
	TestLevel2();
	~TestLevel2();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hwnd) override;

	virtual void UpdateUI(HWND hwnd) override;
};

