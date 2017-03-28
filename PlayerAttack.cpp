#include "Player.h"

void Player::GetAttackKey(DX_Input & input, float dt)
{
	if (m_arrowCurCoolDown > 0) {
		m_arrowCurCoolDown -= dt;
	}
	if (input.m_MouseState.rgbButtons[0]) {
		if (m_arrowCurCoolDown <= 0) {
			m_arrowCurCoolDown = m_arrowCoolDown;
			m_isArrowFired = true;
		}
	}
	Attack();
}

void Player::Attack()
{
	if (m_isArrowFired) {
		D2D1_POINT_2F offset = D2D1::Point2F(
			m_ObjectPoint.x + m_pArrowSpriteSheet->m_spriteWidth,
			m_ObjectPoint.y);
		m_arrowList.push_back(Weapon(m_pArrowSpriteSheet, offset, 700));
		m_isArrowFired = false;
	}
}