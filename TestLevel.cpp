#include "TestLevel.h"



TestLevel::TestLevel(DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height }),
	 m_SpriteSheet(SpriteSheet(L"Image/Level_BackTile4.png"))
{
	m_pPlayer = new Player(100, 100, m_LevelSize.width, m_LevelSize.height);
	Load();
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pPlayer(player),
	 m_pInput(pInput),
	 m_LevelSize(D2D1_SIZE_F{ 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height }),
	 m_SpriteSheet(SpriteSheet(L"Image/Level_BackTile4.png"))
{
	Load();
}

TestLevel::~TestLevel()
{
	Unload();
}

void TestLevel::Load() 
{
}

void TestLevel::Unload() 
{

}

void TestLevel::Render() 
{
	assert(m_bIsInitialized == true);

	m_SpriteSheet.Draw();

	m_pPlayer->Draw();

	m_playerHealthUI.Draw();
}

void TestLevel::Update(float dt)
{
	m_pPlayer->Update(*m_pInput, dt);

	RECT rect; ::GetWindowRect(Graphics::GetInstance()->GetRenderTarget()->GetHwnd(), &rect);

	int blockSize = rect.right / 3;

	if (m_pPlayer->GetPoint().x + blockSize > m_LevelSize.width - blockSize) {
		Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(((m_LevelSize.width - blockSize) * -1) + (blockSize * 2), 0));
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
	m_LevelSize.height = Graphics::GetInstance()->GetRenderTarget()->GetSize().height;
	m_pPlayer->m_levelSize.height = m_LevelSize.height;
}
