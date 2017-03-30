#pragma once

#include "Graphics.h"
#include "IActor.h"
#include "SpriteSheet.h"
#include "Weapon.h"
#include "Enemy.h"

class Player : public IActor
{
private:
	Graphics* m_pGfx;

	D2D1_POINT_2F m_ObjectPoint;
	SpriteSheet* m_pSpriteSheet;

	UINT m_frame;

	// weapon
	SpriteSheet* m_pArrowSpriteSheet;
	std::vector<Weapon> m_arrowList;
	float m_arrowCoolDown;
	float m_arrowCurCoolDown;
	bool m_isArrowFired;

public:
	Player() = delete;
	Player(Graphics* gfx);
	Player(D2D1_POINT_2F point, Graphics* gfx);
	Player(float x, float y, Graphics* gfx);

	~Player() override;

	void Draw(Graphics * gfx) override;

	//void Update(Keyboard & keyboard) override;
	void Update(DX_Input & input, float dt) override;
	void UpdateWeapon(std::vector<Weapon>& pWeapon);

	D2D1_POINT_2F GetPoint() { return m_ObjectPoint; }

	//Update Data with collision
	void UpdateCollision(std::vector<Enemy>& refList);
	D2D1_RECT_F GetRect() override;
private:
	// Animation Frame.
	void UpdateFrame();
	void SetFrame(UINT frame);

	bool ClampPosition();

	// Combat System.
	void GetAttackKey(DX_Input & input, float dt);
	void Attack();

};

