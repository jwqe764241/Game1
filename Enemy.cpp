#include "Enemy.h"

Enemy::Enemy():
	 m_ObjectPoint(D2D1_POINT_2F{0, 0}),
	 m_pSpriteSheet(new SpriteSheet(L"Images/Enemy_Basic1.png")),
	 m_iHealth(100)
{
}

Enemy::Enemy(D2D1_POINT_2F point):
	 m_ObjectPoint(point),
	 m_pSpriteSheet(new SpriteSheet(L"Images/Enemy_Basic1.png")),
	 m_iHealth(100)
{
}

Enemy::Enemy(float x, float y):
	 m_ObjectPoint(D2D1_POINT_2F{x, y}),
	 m_pSpriteSheet(new SpriteSheet(L"Image/Enemy_Basic1.png")),
	 m_iHealth(100)
{
}

Enemy::~Enemy()
{
}


void Enemy::Draw()
{
	m_pSpriteSheet->Draw(0, m_ObjectPoint.x, m_ObjectPoint.y);
}
void Enemy::Update(DX_Input & input, float dt)
{

}

void Enemy::UpdateFrame()
{
}
void Enemy::SetFrame(UINT frame)
{
}

bool Enemy::ClampPosition()
{
	INT height = Graphics::GetInstance()->GetRenderTarget()->GetSize().height;
	bool isValid = false;

	if (m_ObjectPoint.x < 0) {
		m_ObjectPoint.x = 0;
		isValid |= true;
	}
	if (m_ObjectPoint.y < 0) {
		m_ObjectPoint.y = 0;
		isValid |= true;
	}
	if (m_ObjectPoint.y > height - m_pSpriteSheet->m_spriteHeight) {
		m_ObjectPoint.y = height - m_pSpriteSheet->m_spriteHeight;
		isValid |= true;
	}

	return isValid;
}

D2D1_RECT_F Enemy::GetRect()
{
	D2D1_SIZE_F objectSize = m_pSpriteSheet->GetSize();

	return D2D1_RECT_F{ m_ObjectPoint.x, m_ObjectPoint.y,
		m_ObjectPoint.x + objectSize.width, m_ObjectPoint.y + objectSize.height };
}

GameUtils::Type::State Enemy::OnDamage(int damage)
{
	if (0 >= m_iHealth - damage) {
		return GameUtils::Constant::Enemy::STATE_DIED;
	}
	else {
		m_iHealth -= damage;
		return GameUtils::Constant::Enemy::STATE_ALiVE;
	}
}