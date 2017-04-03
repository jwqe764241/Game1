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
		L"sadsd", L"sad", L"asdas", L"vbx",
		D2D1_POINT_2F{1000.f, 100.f}
	));

	m_RenderEnvir.push_back(new TestButton(
		L"sadsd", L"sad", L"asdas", L"vbx",
		D2D1_POINT_2F{ 1000.f, 300.f }
	));

	m_RenderEnvir.push_back(new TestButton(
		L"sadsd", L"sad", L"asdas", L"vbx",
		D2D1_POINT_2F{ 1000.f, 500.f }
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
	if (m_pInput->m_MouseState.rgbButtons[0]) {
		POINT point;  GetCursorPos(&point);
		for (Button* button : m_RenderEnvir) {

		}
	}
}