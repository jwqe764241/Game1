#include <Sources/Levels/HowLevel.h>

HowLevel::HowLevel(DX_Input * pInput):
	m_SpriteSheet(SpriteSheet(L"Image/HowToPlay.png")),
	m_pInput(pInput)
{
}
HowLevel::~HowLevel()
{
}


void HowLevel::Load()
{
	m_pBackButton = new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"�ڷ�",
		D2D1_POINT_2F{ 50, 600 }, 
		NULL
	);
}

void HowLevel::Unload()
{
	delete m_pBackButton;
}

void HowLevel::Render()
{
	m_SpriteSheet.Draw();
	m_pBackButton->Draw();
}

void HowLevel::Update(float dt, HWND hWnd)
{
	POINT clickPoint;  GetCursorPos(&clickPoint);

	if (clickPoint.x > m_pBackButton->m_offset.x &&
		clickPoint.x < m_pBackButton->m_offset.x + m_pBackButton->GetSize().width &&
		clickPoint.y > m_pBackButton->m_offset.y &&
		clickPoint.y < m_pBackButton->m_offset.y + m_pBackButton->GetSize().height) {
		m_pBackButton->OnFocus();
		if (m_pInput->m_MouseState.rgbButtons[0]) {
			m_pBackButton->OnLeftMouseClick();
			SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_MAIN, NULL, NULL);
			return;
		}
		else {
			m_pBackButton->OnLeftMouseRelease();
		}
	}
	else {
		m_pBackButton->OnLeftMouseRelease();
		m_pBackButton->OnFocusOut();
	}
}
