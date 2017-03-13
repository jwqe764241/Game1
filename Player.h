#pragma once

#include "Graphics.h"
#include "IActor.h"

class Player : public IActor
{
private:
	D2D1_POINT_2F m_ObjectPoint;
public:

	Player();
	Player(D2D1_POINT_2F point);
	Player(float x, float y);

	~Player() override;

	void Draw(Graphics * gfx) override;

	void Update() override;
	void Update(D2D1_POINT_2F point) override;
	void Update(float x, float y) override;
};

