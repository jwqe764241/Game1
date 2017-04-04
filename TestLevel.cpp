#include "TestLevel.h"

TestLevel::TestLevel(DX_Input * pInput):
	m_bIsInitialized(true),
	m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile.png"))
{
	m_pPlayer = new Player(
		100, 100,
		m_SpriteSheet.GetSize().width,
		Graphics::GetInstance()->GetRenderTarget()->GetSize().height);
}
TestLevel::TestLevel(DX_Input * pInput, Player * pPlayer):
	m_bIsInitialized(true),
	m_pPlayer(pPlayer),
	m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile.png"))
{
}
TestLevel::~TestLevel()
{
	Unload();
}


void TestLevel::Load() 
{
	m_RenderEnemy.push_back(Enemy(400, 100));
	m_RenderEnemy.push_back(Enemy(1000, 200));
	m_RenderEnemy.push_back(Enemy(3000, 600));

	m_RenderEnemy.push_back(Enemy(1000, 500));
	m_RenderEnemy.push_back(Enemy(2000, 300));
	m_RenderEnemy.push_back(Enemy(3500, 600));
}

void TestLevel::Unload() 
{
	m_pInput = nullptr;
	delete m_pPlayer;
}

void TestLevel::Render() 
{
	D2D1_SIZE_F windowSize = Graphics::GetInstance()->GetRenderTarget()->GetSize();
	D2D1_SIZE_F levelSize  = m_SpriteSheet.GetSize();

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

	for (Enemy enemy : m_RenderEnemy){
		enemy.Draw();
	}
	// Draw UI component after 69 line.
	Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pPlayer->m_playerHealthUI.Draw();
}

void TestLevel::Update(float dt, HWND hwnd)
{
	if (m_RenderEnemy.size() == 0) {
		SendMessage(hwnd, GameUtils::Constant::Level::LEVEL_LEVEL2, NULL, NULL);
		return;
	}

	if (!m_pPlayer->IsAlive()) {
		MessageBoxA(NULL, "You've Died!!", "Message", MB_OK);
		SendMessage(hwnd, GameUtils::Constant::Level::LEVEL_GAMEOVER, NULL, NULL);
		return;
	}

	m_pPlayer->Update(*m_pInput, dt);
	m_pPlayer->UpdateCollision(&m_RenderEnemy);
	m_pPlayer->UpdateDamage(&m_RenderEnemy);
}
