#include "TestLevel.h"



TestLevel::TestLevel(Graphics * gfx, DX_Input * pInput)
	:m_pGraphics(gfx),
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Image/Level_BackTile4.png"),
	 m_pPlayer(new Player(100, 100, gfx)),
	 m_pInput(pInput)
{
}

TestLevel::TestLevel(Graphics * gfx, Player * player, DX_Input * pInput)
	:m_pGraphics(gfx),
	m_bIsInitialized(true),
	m_lpszFilePath(L"Image/Level_BackTile4.png"),
	m_pPlayer(player),
	m_pInput(pInput)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load() 
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

void TestLevel::Unload() 
{
	GameUtils::SafeRelease(&m_pDecoder);
	GameUtils::SafeRelease(&m_pFrameDecode);
	GameUtils::SafeRelease(&m_pConvertedBitmap);
	GameUtils::SafeRelease(&m_pBitmap);
}

void TestLevel::Render() 
{
	assert(m_bIsInitialized == true);

	//RECT rect; GetWindowRect(m_pGraphics->GetRenderTaget()->GetHwnd(), &rect);

	D2D1_POINT_2F playerPoint = m_pPlayer->GetPoint();
	
	D2D1_SIZE_F renderSize = m_pGraphics->GetRenderTarget()->GetSize();
	D2D1_RECT_F renderRect = {0, 0, renderSize.width, renderSize.height};
	D2D1_RECT_F imageRect = { 0, 0, 300, 300 };

	int levelWidth = 4400;
	int levelHeight = renderSize.height;
	
	int curWidth = 0;
	int curHeight = 0;

	while (curHeight < levelHeight) {

		while (curWidth < levelWidth) {
			D2D1_RECT_F imageRect = { curWidth, curHeight, 300 + curWidth, 300 + curHeight };
			m_pGraphics->GetRenderTarget()->DrawBitmap(m_pBitmap, imageRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, renderRect);

			curWidth += 300;
		}

		curWidth = 0;
		curHeight += 300;
	}

	m_pPlayer->Draw(m_pGraphics);

}

void TestLevel::Update()
{
	m_pPlayer->Update(*m_pInput);

	if (m_pPlayer->GetPoint().x + 400 > 4000) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation((4000 * -1) + 800, 0));
	}
	else if (m_pPlayer->GetPoint().x > 400) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + 400, 0));
	}
	else if (m_pPlayer->GetPoint().x < 400) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}
}