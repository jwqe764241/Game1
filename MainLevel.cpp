#include "MainLevel.h"


MainLevel::MainLevel(DX_Input * pInput)
	:m_bIsInitialized(true),
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
		D2D1_POINT_2F{1000.f, 10.f}
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"랭킹보기",
		D2D1_POINT_2F{ 1000.f, 160.f }
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"게임방법",
		D2D1_POINT_2F{ 1000.f, 310.f }
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"게임서게",
		D2D1_POINT_2F{ 1000.f, 460.f }
	));

	m_RenderEnvir.push_back(new TestButton(
		L"Image/UI/button_yellow_normal.png", L"Image/UI/button_yellow_focused.png", L"Image/UI/button_yellow_pressed.png", L"크레딧",
		D2D1_POINT_2F{ 1000.f, 610.f }
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