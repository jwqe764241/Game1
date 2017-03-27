#include "Player.h"

Player::Player(Graphics * gfx)
	: m_pGfx(gfx), m_frame(0), m_isArrowFired(false),
	m_arrowCoolDown(15.f)
{
	m_pSpriteSheet = new SpriteSheet(L"Image/Sprite.png", gfx, 64, 64);
	m_pArrowSpriteSheet = new SpriteSheet(L"Image/Arrow.png", gfx, 64, 64);
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
	UpdateWeapon(m_arrowList);
}

void Player::Update(DX_Input & input, float dt) 
{
	UpdateFrame();

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
	GetAttackKey(input, dt);

	float length = sqrt(pow(x, 2) + pow(y, 2));

	if (length > 0) {
		speed *= dt;
		x *= speed / length;
		y *= speed / length;
		m_ObjectPoint.x += x;
		m_ObjectPoint.y += y;
	}
	if (ClampPosition() && !(moveDirectionCount > 2 && m_ObjectPoint.x > 0)) {
		UINT height = m_pGfx->GetRenderTaget()->GetSize().height - m_pSpriteSheet->m_spriteHeight;
		if (y != 0 && m_ObjectPoint.x == 0 && (m_ObjectPoint.y > 0 && m_ObjectPoint.y < height) && moveDirectionCount == 4) {
			moveDirectionCount = y > 0 ? 1 : 2;
		}
		else if ((moveDirectionCount < 3) || (moveDirectionCount == 4 && m_ObjectPoint.x == 0)) {
			moveDirectionCount = 0;
		}
	}

	SetFrame(moveDirectionCount * 190 + 1);
}

void Player::UpdateWeapon(std::vector<Weapon>& pWeapon)
{
	for (int i = 0; i < pWeapon.size(); i++) {
		if (pWeapon.at(i).m_isDestroyed) {
			pWeapon.erase(pWeapon.begin() + i);
			i--;
		}
		i++;
	}
	for (Weapon& weapon : pWeapon) {
		weapon.Shoot(10.f);
	}
}

void Player::UpdateFrame()
{
	m_frame++;
	if (m_frame > 0 && m_frame % 190 == 0) m_frame -= 190;
}

void Player::SetFrame(UINT frame)
{
	if (m_frame/190 != frame/190) {
		m_frame = frame;
	}
}

bool Player::ClampPosition()
{
	UINT height = m_pGfx->GetRenderTaget()->GetSize().height;
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
