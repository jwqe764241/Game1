#include "Button.h"

Button::Button(wchar_t * normal, wchar_t * focus, wchar_t * click, wchar_t * labelText, D2D1_POINT_2F offset):
	m_normalSpriteSheet(normal), m_focusedSpriteSheet(focus), m_clickedSpriteSheet(click), m_buttonLabelText(labelText),
	m_offset(offset), m_pressed(false), m_focused(false),
	m_buttonLabelLayout(
		L"Gabriola",
		40,
		D2D1::ColorF(D2D1::ColorF::Black),
		D2D1::RectF(offset.x, offset.y,
			offset.x + m_normalSpriteSheet.GetSize().width, offset.y + m_normalSpriteSheet.GetSize().height)
	)
{
	SetSize(m_normalSpriteSheet.GetSize().width, m_normalSpriteSheet.GetSize().height);
}
Button::~Button()
{
}


void Button::CreateDeviceResources()
{
}

void Button::ReleaseDeviceResources()
{
	m_pressed = false;
	m_focused = false;
}

void Button::Draw()
{
	if (m_pressed) {
		m_clickedSpriteSheet.Draw(m_offset.x, m_offset.y,
			m_clickedSpriteSheet.m_spriteWidth, m_clickedSpriteSheet.m_spriteHeight);
	}
	else if (m_focused) {
		m_focusedSpriteSheet.Draw(m_offset.x, m_offset.y,
			m_focusedSpriteSheet.m_spriteWidth, m_focusedSpriteSheet.m_spriteHeight);
	}
	else {
		m_normalSpriteSheet.Draw(m_offset.x, m_offset.y,
			m_normalSpriteSheet.m_spriteWidth, m_normalSpriteSheet.m_spriteHeight);
	}

	m_buttonLabelLayout.Draw(m_buttonLabelText);
}

void Button::SetPressed(bool value)
{
	m_pressed = value;
}

bool Button::GetPressed()
{
	return m_pressed;
}

void Button::SetFocused(bool value)
{
	m_focused = value;
}

bool Button::GetFocused()
{
	return m_focused;
}

void Button::SetSize(float width, float height)
{
	m_size = D2D1::SizeF(width, height);
}

D2D1_SIZE_F Button::GetSize()
{
	return m_size;
}
