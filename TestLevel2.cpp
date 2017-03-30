#include "TestLevel2.h"



TestLevel2::TestLevel2():
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Level_Background2.jpg")
{
}


TestLevel2::~TestLevel2()
{
}

void TestLevel2::Load()
{
	assert(m_bIsInitialized == true);

	Graphics::GetInstance()->GetImagingFactory()->CreateDecoderFromFilename(
		m_lpszFilePath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&m_pDecoder
	);

	m_pDecoder->GetFrame(0, &m_pFrameDecode);

	Graphics::GetInstance()->GetImagingFactory()->CreateFormatConverter(&m_pConvertedBitmap);

	m_pConvertedBitmap->Initialize(
		m_pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	);

	m_renderProperties = D2D1::RenderTargetProperties();
	Graphics::GetInstance()->GetD2DFactory()->GetDesktopDpi(&m_renderProperties.dpiX, &m_renderProperties.dpiY);
	Graphics::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(m_pConvertedBitmap, NULL, &m_pBitmap);
}

void TestLevel2::Unload()
{
	GameUtils::SafeRelease(&m_pDecoder);
	GameUtils::SafeRelease(&m_pFrameDecode);
	GameUtils::SafeRelease(&m_pConvertedBitmap);
	GameUtils::SafeRelease(&m_pBitmap);
}

void TestLevel2::Render()
{
	assert(m_bIsInitialized == true);

	//RECT rect; GetWindowRect(m_pGraphics->GetRenderTaget()->GetHwnd(), &rect);

	D2D1_SIZE_F size = Graphics::GetInstance()->GetRenderTarget()->GetSize();
	D2D1_RECT_F rect = {0 ,0, size.width, size.height};

	Graphics::GetInstance()->GetRenderTarget()->DrawBitmap(m_pBitmap, rect, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);
}

void TestLevel2::Update(float dt)
{

}
