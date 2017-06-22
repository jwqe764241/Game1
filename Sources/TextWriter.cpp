#include <Sources/TextWriter.h>

TextWriter::TextWriter(const wchar_t * fontName, float fontSize,
	D2D1::ColorF color, D2D1_RECT_F layout,
	DWRITE_TEXT_ALIGNMENT textAlign, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlign): 
	m_fontName(fontName), m_fontSize(fontSize), m_fontColor(color), m_layout(layout),
	m_textAlign(textAlign), m_paragraphAlign(paragraphAlign)
{
	CreateDeviceResources();
}

TextWriter::~TextWriter()
{
	ReleaseDeviceResources();
}

void TextWriter::CreateDeviceResources()
{
	HRESULT hr;
	hr = Graphics::GetInstance()->GetDWriteFactory()->CreateTextFormat(
		m_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_fontSize,
		L"kor",
		&m_pTextFormat
	);

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetTextAlignment(m_textAlign);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetParagraphAlignment(m_paragraphAlign);
	}

	if (SUCCEEDED(hr))
	{
		hr = Graphics::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(
			m_fontColor, &m_pTextColorBrush);
	}
}

void TextWriter::ReleaseDeviceResources()
{
	GameUtils::SafeRelease(&m_pTextFormat);
	GameUtils::SafeRelease(&m_pTextColorBrush);
}

void TextWriter::Draw(const wchar_t * text)
{
	Graphics::GetInstance()->GetRenderTarget()->DrawTextA(
		text,
		(UINT32)wcslen(text),
		m_pTextFormat,
		m_layout,
		m_pTextColorBrush
	);
}
