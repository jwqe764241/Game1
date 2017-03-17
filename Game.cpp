#include "Game.h"

//THISBLOCK:�׽��ÿ�
//#define GAME_TEST_OTHERLOOP_1
//#define GAME_TEST_OTHERLOOP_2
//#define GAME_TEST_CNGCOR 
Game::Game(Frame * frame)
	//TODO:m_pRenderHandler�� ���� �� ���°�
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
	//�׷��Ƚ� �ʱ�ȭ

	if (FAILED(m_pFrame->InitializeFrame(nCmdShow, frameTitle)))	  { return S_FALSE; }
	if (FAILED(m_pGraphics->initialize(m_pFrame->GetHWND())))		  { return S_FALSE; }

#ifdef GAME_TEST_CNGCOR
	
	D2D1::ColorF RedColor(1.0f, 0.0f, 0.0f, 0.0f);
	D2D1::ColorF BlueColor(0.0f, 0.0f, 1.0f, 0.0f);

	m_pGraphics->BeginDraw();

	for (int i = 0; i < 1000; ++i) {
		if (i / 2 == 00)
			m_pGraphics->ClearScreen(RedColor);
		else
			m_pGraphics->ClearScreen(BlueColor);
	}

	m_pGraphics->EndDraw();

#endif

	m_RenderList.push_back(new Player(400.0f, 400.0f));

	return S_OK;
}

void Game::StartLooping()
{

#if defined(GAME_TEST_OTHERLOOP_1)

	MSG msg; PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

	while (msg.message != WM_QUIT) 
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

#elif defined(GAME_TEST_OTHERLOOP_2)

	//�ش� ���� : PeekMessage�� ť�� �˻��ϴٰ� �޽����� ������ 0�� �ǹǷ� �����

	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{

		if (msg.message == WM_QUIT) {

			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#else
	MSG msg;

	bool bIsRunning = true;

	while (bIsRunning)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				//TODO:������ ������ �� �������� ����?
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
#endif

}

void Game::Update()
{
	for (std::vector<IActor *>::iterator itor = m_RenderList.begin(); itor < m_RenderList.end(); itor++) {
		//(*itor)->Update(m_pFrame->keyboard);
		(*itor)->Update(m_pFrame->input);
	}
}


void Game::Render()
{
	m_pGraphics->BeginDraw();

		m_pGraphics->ClearScreen(D2D1::ColorF(0, 0, 1.0f));
		//TODO : ���޸� ��ȿ�� ����
		for (std::vector<IActor *>::iterator itor = m_RenderList.begin(); itor < m_RenderList.end(); itor++) {
		
			(*itor)->Draw(m_pGraphics);
		}

	m_pGraphics->EndDraw();
}
