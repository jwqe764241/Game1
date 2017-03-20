#include "Game.h"

Game::Game(Frame * frame)
	:m_pFrame(frame),
	 m_pGraphics(new Graphics())
{
}

Game::~Game()
{

	delete m_pFrame;
	delete m_pGraphics;

}

HRESULT Game::Start(int nCmdShow, char * frameTitle)
{
	if (FAILED(m_pFrame->InitializeFrame(nCmdShow, frameTitle)))	  { return S_FALSE; }
	if (FAILED(m_pGraphics->initialize(m_pFrame->GetHWND())))		  { return S_FALSE; }

	m_RenderList.push_back(new Player(100.0f, 100.0f, m_pGraphics));

	return S_OK;
}

void Game::StartLooping()
{
	MSG msg;

	bool bIsRunning = true;

	while (bIsRunning)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				//TODO:루프를 끝내기 전 빠진것이 없나?
				bIsRunning = false;
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		m_pFrame->input.ReadInput();
		Update();
		Render();
	}

}

void Game::Update()
{
	for (std::vector<IActor *>::iterator itor = m_RenderList.begin(); itor < m_RenderList.end(); itor++) {
		(*itor)->Update(m_pFrame->input);
	}
}


void Game::Render()
{
	m_pGraphics->BeginDraw();

		m_pGraphics->ClearScreen(D2D1::ColorF(0, 0, 1.0f));
  
		for (std::vector<IActor *>::iterator itor = m_RenderList.begin(); itor < m_RenderList.end(); itor++) {
		
			(*itor)->Draw(m_pGraphics);
		}

	m_pGraphics->EndDraw();
}
