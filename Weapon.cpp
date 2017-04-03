#include "Weapon.h"

Weapon::Weapon(SpriteSheet* pSpriteSheet, D2D1_POINT_2F offset, float range): 
	m_pSpriteSheet(pSpriteSheet), m_offset(offset), m_xOffset(offset.x),
	m_isDestroyed(false), m_range(range)
{
}
Weapon::~Weapon()
{
}


void Weapon::Shoot(float speed)
{
	m_offset.x += speed;
	m_pSpriteSheet->Draw(0, m_offset.x, m_offset.y);

	if (m_offset.x - m_xOffset > m_range) Destroy();
}

void Weapon::Destroy()
{
	m_isDestroyed = true;
}

D2D1_RECT_F Weapon::GetRect()
{
	D2D1_SIZE_F objectSize = m_pSpriteSheet->GetSize();

	return D2D1_RECT_F{ m_offset.x, m_offset.y, 
		m_offset.x + objectSize.width, m_offset.y + objectSize.height };
}