#pragma once

#include "Level.h"

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

	void Load()   override;
	void Unload() override;
	void Render() override;
	void Update(float dt) override;
};

