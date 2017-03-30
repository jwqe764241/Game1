#include "TestLevel.h"



TestLevel::TestLevel(DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Image/Level_BackTile4.png"),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height })
{
	m_pPlayer = new Player(100, 100, m_LevelSize.width, m_LevelSize.height);
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Image/Level_BackTile4.png"),
	 m_pPlayer(player),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height })
{
}

TestLevel::~TestLevel()
{
	Unload();
}

void TestLevel::Load() 
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

	GameUtils::SafeRelease(&m_pDecoder);
	GameUtils::SafeRelease(&m_pFrameDecode);
	GameUtils::SafeRelease(&m_pConvertedBitmap);
}

void TestLevel::Unload() 
{
	GameUtils::SafeRelease(&m_pBitmap);
}

void TestLevel::Render() 
{
	assert(m_bIsInitialized == true);

	//RECT rect; GetWindowRect(m_pGraphics->GetRenderTaget()->GetHwnd(), &rect);

	D2D1_POINT_2F playerPoint = m_pPlayer->GetPoint();
	
	D2D1_RECT_F renderRect = {0, 0, m_LevelSize.width, m_LevelSize.height};
	D2D1_RECT_F imageRect = { 0, 0, 300, 300 };
	
	float curWidth  = 0;
	float curHeight = 0;

	while (curHeight < m_LevelSize.height) {

		while (curWidth < m_LevelSize.width) {
			D2D1_RECT_F imageRect = { curWidth, curHeight, 300 + curWidth, 300 + curHeight };
			Graphics::GetInstance()->GetRenderTarget()->DrawBitmap(m_pBitmap, imageRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, renderRect);

			curWidth += 300;
		}

		curWidth = 0;
		curHeight += 300;
	}

	m_pPlayer->Draw();
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

	RECT rect; ::GetWindowRect(Graphics::GetInstance()->GetRenderTarget()->GetHwnd(), &rect);

	int blockSize = rect.right / 3;

	if (m_pPlayer->GetPoint().x + blockSize > m_LevelSize.width - 400) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_LevelSize.width - 400) * -1) + (blockSize * 2), 0));
	}
	else if (m_pPlayer->GetPoint().x > blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + blockSize, 0));
	}
	else if (m_pPlayer->GetPoint().x < blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}

}