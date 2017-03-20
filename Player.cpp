#include "Player.h"

Player::Player(Graphics * gfx) : m_frame(0)
{
	m_pSpriteSheet = new SpriteSheet(L"Image/Sprite.png", gfx, 64, 64);
}

Player::Player(D2D1_POINT_2F point, Graphics* gfx) : Player(gfx)
{
	m_ObjectPoint.x = point.x;
	m_ObjectPoint.y = point.y;
}

Player::Player(float x, float y, Graphics* gfx) : Player(gfx)
{
	m_ObjectPoint.x = x;
	m_ObjectPoint.y = y;
}

Player::~Player()
{
}

void Player::Draw(Graphics * gfx) 
{
	m_pSpriteSheet->Draw((m_frame / 10 / 19) * 19 + ((m_frame / 10) % 5), m_ObjectPoint.x, m_ObjectPoint.y);
}

void Player::Update(DX_Input & input) 
{
	if (input.m_KeyboardState[DIK_D]) {
		m_ObjectPoint.x += 5;
	}
	if (input.m_KeyboardState[DIK_A]) {
		m_ObjectPoint.x -= 5;
	}
	if (input.m_KeyboardState[DIK_W]) {
		m_ObjectPoint.y -= 5;
	}
	if (input.m_KeyboardState[DIK_S]) {
		m_ObjectPoint.y += 5;
	}
}

void Player::SetFrame(UINT frame)
{
	if (m_frame/190 != frame/190) {
		m_frame = frame;
	}
}
