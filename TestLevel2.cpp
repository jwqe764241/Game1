#include "TestLevel2.h"



TestLevel2::TestLevel2(Graphics * gfx)
	:m_pGraphics(gfx),
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

	m_pGraphics->GetImagingFactory()->CreateDecoderFromFilename(
		m_lpszFilePath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&m_pDecoder
	);

	m_pDecoder->GetFrame(0, &m_pFrameDecode);

	m_pGraphics->GetImagingFactory()->CreateFormatConverter(&m_pConvertedBitmap);

	m_pConvertedBitmap->Initialize(
		m_pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	);

	m_renderProperties = D2D1::RenderTargetProperties();
	m_pGraphics->GetD2DFactory()->GetDesktopDpi(&m_renderProperties.dpiX, &m_renderProperties.dpiY);
	m_pGraphics->GetRenderTarget()->CreateBitmapFromWicBitmap(m_pConvertedBitmap, NULL, &m_pBitmap);
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

	D2D1_SIZE_F size = m_pGraphics->GetRenderTarget()->GetSize();
	D2D1_RECT_F rect = {0 ,0, size.width, size.height};

	m_pGraphics->GetRenderTarget()->DrawBitmap(m_pBitmap, rect, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);
}

void TestLevel2::Update()
{

}
