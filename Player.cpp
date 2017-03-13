#include "Player.h"



Player::Player()
{
	m_ObjectPoint.x = 0;
	m_ObjectPoint.y = 0;
}

Player::Player(D2D1_POINT_2F point)
{
	m_ObjectPoint.x = point.x;
	m_ObjectPoint.y = point.y;
}

Player::Player(float x, float y)
{
	m_ObjectPoint.x = x;
	m_ObjectPoint.y = y;
}

Player::~Player()
{

}

void Player::Draw(Graphics * gfx) 
{
	//gfx->PutPixel(m_ObjectPoint);
}

void Player::Update()
{

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
