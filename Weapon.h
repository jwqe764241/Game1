#pragma once
#include "SpriteSheet.h"
#include "IActor.h"

class Weapon
{
public:
	Weapon(SpriteSheet* pSpriteSheet, D2D1_POINT_2F offset);
	~Weapon();

	void Shoot(float speed);
	void Destroy();

public:
	bool m_isDestroyed;

private:
	SpriteSheet* m_pSpriteSheet;
	D2D1_POINT_2F m_offset;
	float m_xOffset;
};