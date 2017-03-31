#include "TestLevel.h"



TestLevel::TestLevel(DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pInput(pInput),
	 m_SpriteSheet(SpriteSheet(L"Image/Level_BackTile4.png"))
{
	m_pPlayer = new Player(100, 100, 4400, Graphics::GetInstance()->GetRenderTarget()->GetSize().height);
	Load();
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pPlayer(player),
	 m_pInput(pInput),
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
	D2D1_SIZE_F levelSize = m_SpriteSheet.GetSize();

	int blockSize = rect.right / 3;

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
