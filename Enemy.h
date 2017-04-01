#pragma once

#include "IActor.h"
#include "SpriteSheet.h"
#include "GameDefine.h"

class Enemy : public IActor
{
	
private:
	D2D1_POINT_2F m_ObjectPoint;
	SpriteSheet* m_pSpriteSheet;

	UINT m_frame;

	int m_iHealth;

public:
	Enemy();
	Enemy(D2D1_POINT_2F point);
	Enemy(float x, float y);

	~Enemy() override;

	void Draw() override;
	void Update(DX_Input & input, float dt) override;

	D2D1_POINT_2F GetPoint() { return m_ObjectPoint; }
	D2D1_RECT_F GetRect() override;

	GameUtils::Type::State OnDamage(int damage);
private:
	void UpdateFrame();
	void SetFrame(UINT frame);

	bool ClampPosition();
};

