#pragma once
#include "SpriteSheet.h"
#include "IActor.h"

class Weapon
{
public:
	Weapon() = delete;
	Weapon(SpriteSheet* pSpriteSheet, D2D1_POINT_2F offset, float range);
	~Weapon();

	void Shoot(float speed);
	void Destroy();

	D2D1_RECT_F GetRect();

public:
	bool m_isDestroyed;
	int  m_weaponDamage;

private:
	SpriteSheet*  m_pSpriteSheet;
	D2D1_POINT_2F m_offset;
	float m_xOffset;
	float m_range;
};