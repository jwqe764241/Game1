#include "Player.h"

#include <iostream>

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
	delete m_pSpriteSheet;
}

void Player::Draw(Graphics * gfx) 
{
	m_pSpriteSheet->Draw((m_frame / 10 / 19) * 19 + ((m_frame / 10) % 5), m_ObjectPoint.x, m_ObjectPoint.y);
}

void Player::Update(DX_Input & input) 
{
	m_frame++;

	int moveDirectionCount = 0;
	float x = 0.f, y = 0.f;
	float speed = 3.f;

	if (input.m_KeyboardState[DIK_S]) {
		moveDirectionCount = 1;
		y += 5;
	}
	else if (input.m_KeyboardState[DIK_W]) {
		moveDirectionCount = 2;
		y -= 5;
	}
	if (input.m_KeyboardState[DIK_D]) {
		moveDirectionCount = 3;
		x += 5;
	}
	else if (input.m_KeyboardState[DIK_A]) {
		moveDirectionCount = 4;
		x -= 5;
	}

	if (input.m_KeyboardState[DIK_LSHIFT]) {
		speed *= 1.5f;
	}

	float length = sqrt(pow(x, 2) + pow(y, 2));

	if (length > 0) {
		x *= speed / length;
		y *= speed / length;
		m_ObjectPoint.x += x;
		m_ObjectPoint.y += y;
	}

	SetFrame(moveDirectionCount * 190 + 1);
}

void Player::UpdateFrame()
{
	m_frame++;
	if (m_frame > 0 && m_frame % 190 == 0) { m_frame -= 190; }
}

void Player::SetFrame(UINT frame)
{
	if (m_frame/190 != frame/190) { m_frame = frame; }
}
