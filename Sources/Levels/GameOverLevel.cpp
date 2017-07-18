#include <Sources/Levels/GameOverLevel.h>

GameOverLevel::GameOverLevel(DX_Input* pInput) :
	m_pInput(pInput), m_screenColor(D2D1::ColorF(D2D1::ColorF::PaleVioletRed)),
	m_gameOverTextLayout(
		L"Comic Sans MS",
		100.f, D2D1::ColorF(D2D1::ColorF::WhiteSmoke),
		D2D1::RectF(0, 0,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().width,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().height * 0.7f)
	)
{
}

GameOverLevel::GameOverLevel(DX_Input * pInput, D2D1::ColorF pColor) :
	m_pInput(pInput), m_screenColor(pColor),
	m_gameOverTextLayout(
		L"Comic Sans MS",
		100.f, D2D1::ColorF(D2D1::ColorF::WhiteSmoke),
		D2D1::RectF(0, 0,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().width,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().height * 0.7f)
	)
{
}

GameOverLevel::~GameOverLevel()
{
}

void GameOverLevel::Load()
{
	m_buttonList.push_back(new TestButton(
		L"../Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png",
		L"다시하기",
		D2D1::Point2F(
			Graphics::GetInstance()->GetRenderTarget()->GetSize().width / 8,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().height * 0.7
		),
		GameUtils::Constant::Button::BUTTON_START
	));
	m_buttonList.push_back(new TestButton(
		L"../Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png",
		L"처음으로",
		D2D1::Point2F(
			Graphics::GetInstance()->GetRenderTarget()->GetSize().width / 8 * 5,
			Graphics::GetInstance()->GetRenderTarget()->GetSize().height * 0.7
		),
		GameUtils::Constant::Button::BUTTON_MAIN
	));
}

void GameOverLevel::Unload()
{
	m_pInput = nullptr;
}

void GameOverLevel::Render()
{
	Graphics::GetInstance()->GetRenderTarget()->Clear(m_screenColor);
	
	m_gameOverTextLayout.Draw(L"Game Over");

	for (TestButton* button : m_buttonList) {
		button->Draw();
	}
}

void GameOverLevel::Update(float dt, HWND hWnd)
{
	POINT clickPoint;  GetCursorPos(&clickPoint);

	for (TestButton* button : m_buttonList) {
		if (clickPoint.x > button->m_offset.x &&
			clickPoint.x < button->m_offset.x + button->GetSize().width &&
			clickPoint.y > button->m_offset.y &&
			clickPoint.y < button->m_offset.y + button->GetSize().height) {
			button->OnFocus();
			if (m_pInput->m_MouseState.rgbButtons[0]) {
				button->OnLeftMouseClick();

				switch (button->m_iButtonId)
				{
				case GameUtils::Constant::Button::BUTTON_START:
					SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_LEVEL1, NULL, NULL);
					return;
				case GameUtils::Constant::Button::BUTTON_MAIN:
					SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_MAIN, NULL, NULL);
					return;
				}
			}
			else {
				button->OnLeftMouseRelease();
			}
		}
		else {
			button->OnLeftMouseRelease();
			button->OnFocusOut();
		}
	}
}
