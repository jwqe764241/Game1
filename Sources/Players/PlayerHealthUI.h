#pragma once

#include <Sources/Actors/Gauge.h>
#include <Sources/TextWriter.h>
#include <Sources/GameDefine.h>

class PlayerHealthUI : public IDrawable
{
public:
	PlayerHealthUI();
	~PlayerHealthUI();

	virtual void CreateDeviceResources()  override;
	virtual void ReleaseDeviceResources() override;

	virtual void Draw() override;

	void AddValue(int value);
	void SubValue(int value);
	void SetValue(int value);

private:
	ID2D1RectangleGeometry* m_pHealthPanel;
	ID2D1SolidColorBrush*   m_pHealthPanelBrush;
	Gauge		 m_healthGauge;
	TextWriter	 m_healthTextWriter;
};