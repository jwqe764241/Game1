#include "MainLevel.h"

MainLevel::MainLevel(DX_Input * pInput):
	m_bIsInitialized(true),
	m_pInput(pInput),
	m_SpriteSheet(L"Image/MainMenu.png")
{
}
MainLevel::~MainLevel()
{
	Unload();
}


void MainLevel::Load()
{
	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"게임시작",
		D2D1_POINT_2F{1000.f, 10.f},
		0
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"랭킹보기",
		D2D1_POINT_2F{ 1000.f, 160.f },
		1
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"게임방법",
		D2D1_POINT_2F{ 1000.f, 310.f },
		2
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"게임소개",
		D2D1_POINT_2F{ 1000.f, 460.f },
		3
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"제작자",
		D2D1_POINT_2F{ 1000.f, 610.f },
		4
	));
}

void MainLevel::Unload()
{
	m_pInput = nullptr;
}

void MainLevel::Render()
{
	m_SpriteSheet.Draw();

	for (Button* button : m_RenderEnvir){
		button->Draw();
	}
}

void MainLevel::Update(float dt, HWND hWnd)
{
	POINT clickPoint;  GetCursorPos(&clickPoint);

	for (TestButton* button : m_RenderEnvir) {

		if (clickPoint.x > button->m_offset.x &&
			clickPoint.x < button->m_offset.x + button->GetSize().width &&
			clickPoint.y > button->m_offset.y &&
			clickPoint.y < button->m_offset.y + button->GetSize().height) {
			button->OnFocus();
			if (m_pInput->m_MouseState.rgbButtons[0]) {
				button->OnLeftMouseClick();

				switch (button->m_iButtonId) {
					case GameUtils::Constant::Button::BUTTON_START :
						SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_LEVEL1, NULL, NULL);
						return;
					case GameUtils::Constant::Button::BUTTON_RANK  :
						SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_RANK, NULL, NULL);
						return;
					case GameUtils::Constant::Button::BUTTON_HOW   :
						SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_HOW, NULL, NULL);
						return;
					case GameUtils::Constant::Button::BUTTON_INFO  :
						SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_INFO, NULL, NULL);
						return;
					case GameUtils::Constant::Button::BUTTON_CREDIT:
						SendMessage(hWnd, GameUtils::Constant::Level::LEVEL_CREDIT, NULL, NULL);
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