#pragma once

#include "Graphics.h"
#include "IActor.h"
#include "SpriteSheet.h"

class Player : public IActor
{
private:
	D2D1_POINT_2F m_ObjectPoint;
	SpriteSheet* m_pSpriteSheet;

	UINT m_frame;

public:

	Player() = delete;
	Player(Graphics* gfx);
	Player(D2D1_POINT_2F point, Graphics* gfx);
	Player(float x, float y, Graphics* gfx);

	~Player() override;

	void Draw(Graphics * gfx) override;

	void Update() override;
	void Update(D2D1_POINT_2F point) override;
	void Update(float x, float y) override;
};

