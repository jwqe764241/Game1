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
			m_ObjectPoint.x + m_pArrowSpriteSheet->m_spriteWidth + 152,
			m_ObjectPoint.y + 64);
		m_arrowList.push_back(Weapon(m_pArrowSpriteSheet, offset, 700));
		m_isArrowFired = false;
	}
}

void Player::UpdateCollision(std::vector<Enemy> * refList)
{
	for (std::vector<Enemy>::iterator itor = refList->begin(); itor < refList->end();) {
		D2D1_RECT_F enemyRect = itor->GetRect();

		// collision process for enemy <-> weapon
		for (Weapon& weapon : m_arrowList) {
			D2D1_RECT_F weaponRect = weapon.GetRect();

			if ((weaponRect.right > enemyRect.left) &&
				(weaponRect.left < enemyRect.right)) {
				if ((weaponRect.bottom > enemyRect.top) &&
					(weaponRect.top < enemyRect.bottom)) {

					weapon.Destroy();
					if (itor->OnDamage(weapon.m_weaponDamage) == GameUtils::Constant::Enemy::STATE_DIED) {
						itor = refList->erase(itor);
					}
					//TODO:���� ���� �����ѵ�...? �ϴ� �̰� 99% �����ε� �ð��� ����.
					return;
				}
			}
		}

		itor++;
	}
}

void Player::UpdateDamage(std::vector<Enemy>* refList)
{
	for (std::vector<Enemy>::iterator itor = refList->begin(); itor < refList->end();) {
		D2D1_RECT_F enemyRect = itor->GetRect();
		// collision process for enemy <-> player
		D2D1_RECT_F playerRect = GetRect();
		if ((playerRect.right > enemyRect.left) &&
			(playerRect.left < enemyRect.right)) {
			if ((playerRect.bottom > enemyRect.top) &&
				(playerRect.top < enemyRect.bottom)) {
				if (OnDamage(1) == GameUtils::Constant::Player::STATE_DIED) {
					OnDied();
					return;
				}
				//TODO:���� ���� �����ѵ�...? �ϴ� �̰� 99% �����ε� �ð��� ����.
				//return;
			}
		}

		itor++;
	}
}
