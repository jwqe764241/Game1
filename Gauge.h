#pragma once

#include "SpriteSheet.h"
#include "IDrawable.h"

class Gauge : public IDrawable
{
public:
	Gauge(int max, int min, int value, D2D1_POINT_2F offset, D2D1_SIZE_F size, wchar_t* fileName);
	~Gauge();

	void AddValue(int value);
	void SubValue(int value);

	virtual void CreateDeviceResources();
	virtual void ReleaseDeviceResources();
	virtual void Draw();

public:
	int m_max, m_min;
	int m_value;

	D2D1_POINT_2F m_offset;
	D2D1_SIZE_F m_size;

private:

	const wchar_t* m_fileName;

	SpriteSheet* m_pSpriteSheet;
	ID2D1SolidColorBrush* m_pGaugeBorderBrush;
	ID2D1RectangleGeometry* m_pGaugeRectangleGeometry;
};