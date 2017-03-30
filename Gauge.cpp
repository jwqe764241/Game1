#include "Gauge.h"
#include "GameDefine.h"

Gauge::Gauge(int max, int min, int value, D2D1_POINT_2F offset, D2D1_SIZE_F size, wchar_t* fileName) :
	m_max(max), m_min(min), m_value(value), m_offset(offset), m_size(size), m_fileName(fileName),
	m_pSpriteSheet(NULL), m_pGaugeRectangleGeometry(NULL)
{
	CreateDeviceResources();
}

Gauge::~Gauge()
{
	ReleaseDeviceResources();
}

void Gauge::AddValue(int value)
{
	m_value = m_value + value > m_max ? m_max : m_value + value;
}

void Gauge::SubValue(int value)
{
	m_value = m_value - value < m_min ? m_min : m_value - value;
}

void Gauge::CreateDeviceResources()
{
	m_pSpriteSheet = new SpriteSheet(m_fileName);
	Graphics::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &m_pGaugeBorderBrush
	);
	Graphics::GetInstance()->GetD2DFactory()->CreateRectangleGeometry(
		D2D1::RectF(m_offset.x, m_offset.y, m_size.width, m_size.height), &m_pGaugeRectangleGeometry);
}

void Gauge::ReleaseDeviceResources()
{
	GameUtils::SafeRelease(&m_pGaugeRectangleGeometry);
	GameUtils::SafeRelease(&m_pGaugeBorderBrush);
	delete m_pSpriteSheet;
}

void Gauge::Draw()
{
	int currentWidth = m_size.width * (float)(m_value / m_max);
	if (currentWidth > m_size.width) currentWidth = m_size.width;
	else if (currentWidth < 0) currentWidth = 0;
	m_pSpriteSheet->Draw(m_offset.x, m_offset.y, currentWidth, m_size.height);
	Graphics::GetInstance()->GetRenderTarget()->DrawGeometry(m_pGaugeRectangleGeometry, m_pGaugeBorderBrush, 2);
}
