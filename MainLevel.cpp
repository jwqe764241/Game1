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
	m_RenderEnvir.push_back(new Button(1000.f, 100.f));
	m_RenderEnvir.push_back(new Button(1000.f, 300.f));
	m_RenderEnvir.push_back(new Button(1000.f, 500.f));
}

void MainLevel::Unload()
{
	m_pInput = nullptr;
}

void MainLevel::Render()
{
	m_SpriteSheet.Draw();

	for (Button* button : m_RenderEnvir){
		button->Render();
	}
}

void MainLevel::Update(float dt)
{
	if (m_pInput->m_MouseState.rgbButtons[0]) {
		POINT point;  GetCursorPos(&point);
		for (Button* button : m_RenderEnvir) {
			if (button->IsOnMouse(point.x, point.y)) {
				SendMessage(Graphics::GetInstance()->GetRenderTarget()->GetHwnd(), WM_USER + 1, NULL, NULL);
				return;
			}
		}
	}
}