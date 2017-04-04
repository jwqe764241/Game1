#include "TestLevel2.h"

TestLevel2::TestLevel2(DX_Input * pInput):
	m_bIsInitialized(true),
	m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile2.png"))
{
	m_pPlayer = new Player(
		100, 100,
		m_SpriteSheet.GetSize().width,
		Graphics::GetInstance()->GetRenderTarget()->GetSize().height);
}
TestLevel2::TestLevel2(DX_Input * pInput, Player * pPlayer):
	m_bIsInitialized(true),
	m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile2.png"))
{
	//나중에 체력 같은거 옮길 수 있게 하든가 걍 하든가
	m_pPlayer = new Player(
		100, 100,
		m_SpriteSheet.GetSize().width,
		Graphics::GetInstance()->GetRenderTarget()->GetSize().height);
}
TestLevel2::~TestLevel2()
{
	Unload();
}


void TestLevel2::Load()
{
	m_RenderEnemy.push_back(Enemy(600, 500));
	m_RenderEnemy.push_back(Enemy(1200, 400));
	m_RenderEnemy.push_back(Enemy(1500, 400));
	m_RenderEnemy.push_back(Enemy(3000, 500));
}

void TestLevel2::Unload()
{
}

void TestLevel2::Render()
{
	RECT rect; ::GetWindowRect(Graphics::GetInstance()->GetRenderTarget()->GetHwnd(), &rect);

	D2D1_SIZE_F windowSize = Graphics::GetInstance()->GetRenderTarget()->GetSize();
	D2D1_SIZE_F levelSize = m_SpriteSheet.GetSize();

	float blockSize = windowSize.width / 3.0f;

	if (m_pPlayer->GetPoint().x + blockSize > levelSize.width - blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((levelSize.width - blockSize) * -1) + (blockSize * 2), 0));
	}
	else if (m_pPlayer->GetPoint().x > blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + blockSize, 0));
	}
	else if (m_pPlayer->GetPoint().x < blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}

	m_SpriteSheet.Draw();
	m_pPlayer->Draw();

	for (Enemy enemy : m_RenderEnemy) {
		enemy.Draw();
	}

	Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_playerHealthUI.Draw();
}

void TestLevel2::Update(float dt, HWND hwnd)
{
	if (m_RenderEnemy.size() == 0) {
		SendMessage(hwnd, GameUtils::Constant::Level::LEVEL_END, NULL, NULL);
		return;
	}

	m_pPlayer->Update(*m_pInput, dt);
	m_pPlayer->UpdateCollision(&m_RenderEnemy);
}