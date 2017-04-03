#include "TestLevel.h"



TestLevel::TestLevel(DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pInput(pInput),
	 m_SpriteSheet(SpriteSheet(L"Image/LevelTile.png")),
	 m_testButton(
		 L"Image/UI/button_yellow_normal.png",
		 L"Image/UI/button_yellow_focused.png",
		 L"Image/UI/button_yellow_pressed.png",
		 L"클릭하세요.",
		 D2D1::Point2F(300, 300))
{
	m_pPlayer = new Player(
		100, 100,
		m_SpriteSheet.GetSize().width,
		Graphics::GetInstance()->GetRenderTarget()->GetSize().height);
}
TestLevel::TestLevel(Player * player, DX_Input * pInput):
	 m_bIsInitialized(true),
	 m_pPlayer(player),
	 m_pInput(pInput),
	m_SpriteSheet(SpriteSheet(L"Image/LevelTile.png")),
	m_testButton(
		L"Image/UI/button_yellow_normal.png",
		L"Image/UI/button_yellow_focused.png",
		L"Image/UI/button_yellow_clicked.png",
		L"클릭하세요.",
		D2D1::Point2F(300, 300))
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
	m_RenderEnemy.push_back(Enemy(3000, 200));
}

void TestLevel::Unload() 
{
}

void TestLevel::Render() 
{
	D2D1_SIZE_F windowSize = Graphics::GetInstance()->GetRenderTarget()->GetSize();

	D2D1_SIZE_F levelSize = m_SpriteSheet.GetSize();

	float blockSize = windowSize.width / 3.f;

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

	for (Enemy enemy : m_RenderEnemy)
	{
		enemy.Draw();
	}

	// Draw UI component after 69 line.
	Graphics::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pPlayer->m_playerHealthUI.Draw();

	m_testButton.Draw();
}

void TestLevel::Update(float dt, HWND hwnd)
{
	UpdateUI(hwnd);
	m_pPlayer->Update(*m_pInput, dt);
	
	m_pPlayer->UpdateCollision(m_RenderEnemy);
}

void TestLevel::OnResize()
{
	m_pPlayer->m_levelSize.height = Graphics::GetInstance()->GetRenderTarget()->GetSize().height;
}

void TestLevel::UpdateUI(HWND hwnd)
{
	/*int x = m_pInput->m_MousePoint.x;
	int y = m_pInput->m_MousePoint.y;*/

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);

	/*std::vector<TestButton> buttons;
	buttons.push_back(m_testButton);

	for (TestButton button : buttons) {
		
	}*/

	if (point.x > m_testButton.m_offset.x &&
		point.x < m_testButton.m_offset.x + m_testButton.GetSize().width &&
		point.y > m_testButton.m_offset.y &&
		point.y < m_testButton.m_offset.y + m_testButton.GetSize().height) {
		m_testButton.OnFocus();
		if (m_pInput->m_MouseState.rgbButtons[0]) {
			m_testButton.OnLeftMouseClick();
		}
		else {
			m_testButton.OnLeftMouseRelease();
		}
	}
	else {
		m_testButton.OnLeftMouseRelease();
		m_testButton.OnFocusOut();
	}
}
