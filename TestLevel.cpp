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
	Load();
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pPlayer(player),
	 m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile.png"))
{
	Load();
}

TestLevel::~TestLevel()
{
	Unload();
}

void TestLevel::Load() 
{
	m_RenderEnemy.push_back(Enemy(400, 100));
	m_RenderEnemy.push_back(Enemy(1000, 200));
	m_RenderEnemy.push_back(Enemy(3000, 200));
}

void TestLevel::Unload() 
{
}

void TestLevel::Render() 
{
	m_SpriteSheet.Draw();

	m_pPlayer->Draw();

	m_playerHealthUI.Draw();

	for (Enemy enemy : m_RenderEnemy)
	{
		enemy.Draw();
	}
}

void TestLevel::Update(float dt)
{
	m_pPlayer->Update(*m_pInput, dt);
	
	m_pPlayer->UpdateCollision(m_RenderEnemy);
  
	RECT rect; ::GetWindowRect(Graphics::GetInstance()->GetRenderTarget()->GetHwnd(), &rect);
  
	D2D1_SIZE_F levelSize = m_SpriteSheet.GetSize();

	float blockSize = (rect.right - rect.left) / 3.f;

	if (m_pPlayer->GetPoint().x + blockSize > levelSize.width - blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((levelSize.width - blockSize) * -1) + (blockSize * 2), 0));
	}
	else if (m_pPlayer->GetPoint().x > blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_pPlayer->GetPoint().x) * -1) + blockSize, 0));
	}
	else if (m_pPlayer->GetPoint().x < blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	}
}

void TestLevel::OnResize()
{
	m_pPlayer->m_levelSize.height = Graphics::GetInstance()->GetRenderTarget()->GetSize().height;
}