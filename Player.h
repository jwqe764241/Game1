#pragma once

#include "Graphics.h"
#include "IActor.h"
#include "SpriteSheet.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PlayerHealthUI.h"
#include "GameDefine.h"

class Player : public IActor
{
public:
	D2D1_SIZE_F m_levelSize;

	// player Health gui.
	// this is drawn in level class.
	PlayerHealthUI m_playerHealthUI;

private:
	D2D1_POINT_2F m_ObjectPoint;
	SpriteSheet*  m_pSpriteSheet;

	UINT m_frame;

	// weapon
	SpriteSheet* m_pArrowSpriteSheet;
	std::vector<Weapon> m_arrowList;
	float m_arrowCoolDown;
	float m_arrowCurCoolDown;
	bool  m_isArrowFired;

public:
	Player();
	Player(D2D1_POINT_2F point, D2D1_SIZE_F levelSize);
	Player(float x, float y, float levelWidth, float levelHeight);

	~Player() override;

	void Draw() override;
	void Update(DX_Input & input, float dt) override;
	void UpdateWeapon(std::vector<Weapon>& pWeapon);

	//Update Data with collision
	void UpdateCollision(std::vector<Enemy> * refList);

	D2D1_POINT_2F GetPoint() { return m_ObjectPoint; }
	D2D1_RECT_F   GetRect() override;

	void OnDamage();
private:
	// Animation Frame.
	void UpdateFrame();
	void SetFrame(UINT frame);

	bool ClampPosition();

	// Combat System.
	void GetAttackKey(DX_Input & input, float dt);
	void Attack();

};

