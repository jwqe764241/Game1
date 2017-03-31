#include "Player.h"

Player::Player()
	: m_frame(0), m_isArrowFired(false),
	m_arrowCoolDown(15.f), m_ObjectPoint(D2D1::Point2F())
{
	m_levelSize = Graphics::GetInstance()->GetRenderTarget()->GetSize();
	m_pSpriteSheet = new SpriteSheet(L"Image/Sprite.png", 64, 64);
	m_pArrowSpriteSheet = new SpriteSheet(L"Image/Arrow.png", 64, 64);
}

Player::Player(D2D1_POINT_2F point, D2D1_SIZE_F levelSize) : Player()
{
	m_ObjectPoint = point;
	m_levelSize = levelSize;
}

Player::Player(float x, float y, float levelWidth, float levelHeight) : Player()
{
	m_ObjectPoint.x = x;
	m_ObjectPoint.y = y;
	m_levelSize.width = levelWidth;
	m_levelSize.height = levelHeight;
}

Player::~Player()
{
	delete m_pSpriteSheet;
}

void Player::Draw() 
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

	UINT height = m_levelSize.height - m_pSpriteSheet->m_spriteHeight;
	UINT width = m_levelSize.width - m_pSpriteSheet->m_spriteWidth;
	if (ClampPosition() && !(moveDirectionCount > 2 && m_ObjectPoint.x > 0 && m_ObjectPoint.x < width)) {
		if (y != 0 &&
			(m_ObjectPoint.x == 0 || m_ObjectPoint.x == width) && 
			(m_ObjectPoint.y > 0 && m_ObjectPoint.y < height) && 
			(moveDirectionCount == 3 || moveDirectionCount == 4)) {
			moveDirectionCount = y > 0 ? 1 : 2;
		}
		else if ((moveDirectionCount < 3) ||
			(moveDirectionCount == 4 && m_ObjectPoint.x == 0) ||
			(moveDirectionCount == 3 && m_ObjectPoint.x == width)) {
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
	if (m_frame > 0 && m_frame % 190 == 0) { m_frame -= 190; }
}

void Player::SetFrame(UINT frame)
{
	if (m_frame/190 != frame/190) { m_frame = frame; }
}

bool Player::ClampPosition()
{
	UINT height = m_levelSize.height - m_pSpriteSheet->m_spriteHeight;
	UINT width = m_levelSize.width - m_pSpriteSheet->m_spriteWidth;
	bool isValid = false;

	if (m_ObjectPoint.x < 0) {
		m_ObjectPoint.x = 0;
		isValid |= true;
	}
	if (m_ObjectPoint.y < 0) {
		m_ObjectPoint.y = 0;
		isValid |= true;
	}
	if (m_ObjectPoint.y > height) {
		m_ObjectPoint.y = height;
		isValid |= true;
	}
	if (m_ObjectPoint.x > width) {
		m_ObjectPoint.x = width;
		isValid |= true;
	}

	return isValid;
}

D2D1_RECT_F Player::GetRect() 
{
	D2D1_SIZE_F objectSize = m_pSpriteSheet->GetSize();

	return D2D1_RECT_F{ m_ObjectPoint.x, m_ObjectPoint.y, 
			m_ObjectPoint.x + objectSize.width, m_ObjectPoint.y + objectSize.height };
}