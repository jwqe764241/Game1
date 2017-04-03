#include "Button.h"


Button::Button(float x, float y) 
	:m_SpriteSheet(L"Image/Button.png"),
	 m_ObjectPoint(D2D1_POINT_2F{x, y})
{

}

Button::~Button()
{

}

void Button::Render()
{
	m_SpriteSheet.Draw(0, m_ObjectPoint.x, m_ObjectPoint.y);
}

bool Button::IsOnMouse(float x, float y)
{
	RECT rect = { m_ObjectPoint.x, m_ObjectPoint.y,
	  m_ObjectPoint.x + m_SpriteSheet.m_spriteWidth,
	  m_ObjectPoint.y + m_SpriteSheet.m_spriteHeight };

	if ((rect.left < x) && (rect.right > x)) {
		if ((rect.top < y) && (rect.bottom > y)) {
			return true;
		}
	}

	return false;
}