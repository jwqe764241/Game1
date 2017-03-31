#include "TestLevel.h"



TestLevel::TestLevel(DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height }),
	 m_pHealthPanel(nullptr), m_pHealthPanelBrush(nullptr)
{
	m_pPlayer = new Player(100, 100, m_LevelSize.width, m_LevelSize.height);
	Load();
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pPlayer(player),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height }),
	 m_pHealthPanel(nullptr), m_pHealthPanelBrush(nullptr)
{
	Load();
}

TestLevel::~TestLevel()
{
	Unload();
}

void TestLevel::Load() 
{
	//assert(m_bIsInitialized == true);

	//Graphics::GetInstance()->GetImagingFactory()->CreateDecoderFromFilename(
	//	m_lpszFilePath,
	//	NULL,
	//	GENERIC_READ,
	//	WICDecodeMetadataCacheOnDemand,
	//	&m_pDecoder
	//);

	//m_pDecoder->GetFrame(0, &m_pFrameDecode);

	//Graphics::GetInstance()->GetImagingFactory()->CreateFormatConverter(&m_pConvertedBitmap);

	//m_pConvertedBitmap->Initialize(
	//	m_pFrameDecode,
	//	GUID_WICPixelFormat32bppPBGRA,
	//	WICBitmapDitherTypeNone,
	//	NULL,
	//	0.f,
	//	WICBitmapPaletteTypeCustom
	//);

	//m_renderProperties = D2D1::RenderTargetProperties();
	//Graphics::GetInstance()->GetD2DFactory()->GetDesktopDpi(&m_renderProperties.dpiX, &m_renderProperties.dpiY);
	//Graphics::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(m_pConvertedBitmap, NULL, &m_pBitmap);

	//GameUtils::SafeRelease(&m_pDecoder);
	//GameUtils::SafeRelease(&m_pFrameDecode);
	//GameUtils::SafeRelease(&m_pConvertedBitmap);
	m_pSpriteSheet = new SpriteSheet(L"Image/Level_BackTile4.png");
	Graphics::GetInstance()->GetD2DFactory()->CreateRectangleGeometry(
		D2D1::RectF(10, 10, 230, 75), &m_pHealthPanel);
	Graphics::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Beige), &m_pHealthPanelBrush);
	m_pHealthGauge = new Gauge(5, 0, 5, D2D1::Point2F(20, 40), D2D1::SizeF(200, 20), L"Image/HealthBar.png");
	m_pHealthTextWriter = new TextWriter(
		L"Gabriola",
		20,
		D2D1::ColorF(D2D1::ColorF::Black),
		D2D1::RectF(
			m_pHealthGauge->m_offset.x,
			m_pHealthGauge->m_offset.y - 60,
			(m_pHealthGauge->m_offset.x + m_pHealthGauge->m_size.width) / 3,
			m_pHealthGauge->m_offset.y + m_pHealthGauge->m_size.height),
		DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
}

void TestLevel::Unload() 
{
	delete m_pSpriteSheet;
	delete m_pHealthGauge;
	delete m_pHealthTextWriter;

	GameUtils::SafeRelease(&m_pHealthPanel);
	GameUtils::SafeRelease(&m_pHealthPanelBrush);
}

void TestLevel::Render() 
{
	assert(m_bIsInitialized == true);

	//RECT rect; GetWindowRect(m_pGraphics->GetRenderTaget()->GetHwnd(), &rect);

	/*D2D1_POINT_2F playerPoint = m_pPlayer->GetPoint();
	
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
	}*/

	m_pSpriteSheet->Draw();

	m_pPlayer->Draw();

	Graphics::GetInstance()->GetRenderTarget()->FillGeometry(m_pHealthPanel, m_pHealthPanelBrush);
	m_pHealthGauge->Draw();

	std::wostringstream wos;
	wos << m_pHealthGauge->m_value << "/" << m_pHealthGauge->m_max;
	m_pHealthTextWriter->Draw(wos.str().c_str());
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

	if (m_pPlayer->GetPoint().x + blockSize > m_LevelSize.width - blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_LevelSize.width - blockSize) * -1) + (blockSize * 2), 0));
	}
	else if (m_pPlayer->GetPoint().x > blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + blockSize, 0));
	}
	else if (m_pPlayer->GetPoint().x < blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}

}

void TestLevel::OnResize()
{
	m_LevelSize.height = Graphics::GetInstance()->GetRenderTarget()->GetSize().height;
	m_pPlayer->m_levelSize.height = m_LevelSize.height;
}
