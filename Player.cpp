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
	gfx->PutPixel(m_ObjectPoint);
}
/*
void Player::Update(Keyboard & keyboard)
{
	if (keyboard.KeyIsPressed(VK_RIGHT)) {
		m_ObjectPoint.x += 5;
	}
	if (keyboard.KeyIsPressed(VK_LEFT)) {
		m_ObjectPoint.x -= 5;
	}
	if (keyboard.KeyIsPressed(VK_UP))  {
		m_ObjectPoint.y -= 5;
	}
	if (keyboard.KeyIsPressed(VK_DOWN)) {
		m_ObjectPoint.y += 5;
	}
}
*/

void Player::Update(DX_Input & input) 
{
	/*
	if (input.IsKeyPressed(DIK_D)) {
		m_ObjectPoint.x += 5;
	}
	if (input.IsKeyPressed(DIK_A)) {
		m_ObjectPoint.x -= 5;
	}
	if (input.IsKeyPressed(DIK_W)) {
		m_ObjectPoint.y -= 5;
	}
	if (input.IsKeyPressed(DIK_S)) {
		m_ObjectPoint.y += 5;
	}
	*/
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
