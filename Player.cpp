#include "Player.h"



//Player::Player()
//{
//	m_ObjectPoint.x = 0;
//	m_ObjectPoint.y = 0;
//}

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
	m_pSpriteSheet->Draw((m_frame/10) % 5, 100, 100);
	//gfx->PutPixel(m_ObjectPoint);
}

void Player::Update()
{
	m_frame++;
	if (m_frame == 50) m_frame = 0;
}

void Player::Update(D2D1_POINT_2F point) 
{
	m_ObjectPoint.x += point.x;
	m_ObjectPoint.y += point.y;
}

void Player::Update(float x, float y)
{
	m_ObjectPoint.x += x;
	m_ObjectPoint.y += y;
}
