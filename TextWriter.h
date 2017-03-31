#pragma once

#include "Graphics.h"
#include "GameDefine.h"
#include "IDrawable.h"

class TextWriter : public IDrawable
{
public:
	TextWriter(const wchar_t* fontName, float fontSize, D2D1::ColorF color,
		D2D1_RECT_F layout,
		DWRITE_TEXT_ALIGNMENT textAlign = DWRITE_TEXT_ALIGNMENT_CENTER, 
		DWRITE_PARAGRAPH_ALIGNMENT paragraphAlign = DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	~TextWriter();

	virtual void CreateDeviceResources();
	virtual void ReleaseDeviceResources();

	virtual void Draw() {};
	virtual void Draw(const wchar_t* text);

private:
	const wchar_t* m_fontName;
	float m_fontSize;
	D2D1::ColorF m_fontColor;
	D2D1_RECT_F m_layout;

	DWRITE_TEXT_ALIGNMENT m_textAlign;
	DWRITE_PARAGRAPH_ALIGNMENT m_paragraphAlign;

	ID2D1SolidColorBrush* m_pTextColorBrush;
	IDWriteTextFormat* m_pTextFormat;
};