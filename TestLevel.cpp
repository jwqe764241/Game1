#include "TestLevel.h"



TestLevel::TestLevel(Graphics * gfx, DX_Input * pInput)
	:m_pGraphics(gfx),
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Image/LevelTile.png"),
	 m_pPlayer(new Player(100, 100, gfx)),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, m_pGraphics->GetRenderTarget()->GetSize().height })
{
}
TestLevel::TestLevel(Graphics * gfx, Player * player, DX_Input * pInput)
	:m_pGraphics(gfx),
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Image/LevelTile.png"),
	 m_pPlayer(player),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, m_pGraphics->GetRenderTarget()->GetSize().height })
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
	
	D2D1_RECT_F renderRect = {0, 0, m_LevelSize.width, m_LevelSize.height};
	D2D1_RECT_F imageRect = { 0, 0, 5000, 2000 };
	
	/*
	float curWidth  = 0;
	float curHeight = 0;

	while (curHeight < m_LevelSize.height) {

		while (curWidth < m_LevelSize.width) {
			D2D1_RECT_F imageRect = { curWidth, curHeight, 300 + curWidth, 300 + curHeight };
			m_pGraphics->GetRenderTarget()->DrawBitmap(m_pBitmap, imageRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, renderRect);

			curWidth += 300;
		}

		curWidth = 0;
		curHeight += 300;
	}
	*/

	//m_pGraphics->GetRenderTarget()->DrawBitmap(m_pBitmap, imageRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, imageRect);
	m_pGraphics->GetRenderTarget()->DrawBitmap(m_pBitmap, renderRect);

	m_pPlayer->Draw(m_pGraphics);
}

void TestLevel::Update(float dt)
{
	m_pPlayer->Update(*m_pInput, dt);

	/*
	if (m_pPlayer->GetPoint().x + 400 > 4000) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation((4000 * -1) + 800, 0));
	}
	else if (m_pPlayer->GetPoint().x > 800) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + 800, 0));
	}
	else if (m_pPlayer->GetPoint().x < 400) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}
	*/

	RECT rect; ::GetWindowRect(m_pGraphics->GetRenderTarget()->GetHwnd(), &rect);

	int blockSize = rect.right / 3;

	if (m_pPlayer->GetPoint().x + blockSize > m_LevelSize.width - 400) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_LevelSize.width - 400) * -1) + (blockSize * 2), 0));
	}
	else if (m_pPlayer->GetPoint().x > blockSize) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + blockSize, 0));
	}
	else if (m_pPlayer->GetPoint().x < blockSize) {
		m_pGraphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}

}