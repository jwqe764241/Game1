#include "PlayerHealthUI.h"

PlayerHealthUI::PlayerHealthUI() : 
	m_healthGauge(5, 0, 5, D2D1::Point2F(20, 40), D2D1::SizeF(200, 20), L"Image/HealthBar.png"),
	m_healthTextWriter(
		L"Gabriola",
		20,
		D2D1::ColorF(D2D1::ColorF::Black),
		D2D1::RectF(
			m_healthGauge.m_offset.x,
			m_healthGauge.m_offset.y - 60,
			(m_healthGauge.m_offset.x + m_healthGauge.m_size.width) / 3,
			m_healthGauge.m_offset.y + m_healthGauge.m_size.height),
		DWRITE_TEXT_ALIGNMENT_JUSTIFIED
	)
{
	CreateDeviceResources();
}

PlayerHealthUI::~PlayerHealthUI()
{
	ReleaseDeviceResources();
}

void PlayerHealthUI::CreateDeviceResources()
{
	Graphics::GetInstance()->GetD2DFactory()->CreateRectangleGeometry(
		D2D1::RectF(10, 10, 230, 75), &m_pHealthPanel);
	Graphics::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Beige), &m_pHealthPanelBrush);
}

void PlayerHealthUI::ReleaseDeviceResources()
{
	GameUtils::SafeRelease(&m_pHealthPanel);
	GameUtils::SafeRelease(&m_pHealthPanelBrush);
}

void PlayerHealthUI::Draw()
{
	Graphics::GetInstance()->GetRenderTarget()->FillGeometry(m_pHealthPanel, m_pHealthPanelBrush);
	m_healthGauge.Draw();

	std::wostringstream wos;
	wos << m_healthGauge.m_value << "/" << m_healthGauge.m_max;
	m_healthTextWriter.Draw(wos.str().c_str());
}
