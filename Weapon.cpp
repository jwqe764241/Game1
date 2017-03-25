#include "Weapon.h"

Weapon::Weapon(SpriteSheet* pSpriteSheet, D2D1_POINT_2F offset)
	: m_pSpriteSheet(pSpriteSheet), m_offset(offset), m_xOffset(offset.x),
	m_isDestroyed(false)
{
}

Weapon::~Weapon()
{
}

void Weapon::Shoot(float speed)
{
	m_offset.x += speed;
	m_pSpriteSheet->Draw(0, m_offset.x, m_offset.y);

	if (m_offset.x - m_xOffset > 500) Destroy();
}

void Weapon::Destroy()
{
	m_isDestroyed = true;
}