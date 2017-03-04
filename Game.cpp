#include "Game.h"


Game::Game(HINSTANCE hInstance)
	//TODO:m_pRenderHandler의 값이 잘 들어갔는가
	:m_pFrame(new Frame(hInstance, "Default Class Name")),
	 m_pGraphics(new Graphics())
{
}

Game::~Game()
{
}

HRESULT Game::Start(int nCmdShow)
{

	//그래픽스 초기화
	if (FAILED(m_pGraphics->initialize(m_pFrame->GetHWND()))) {

		return S_FALSE;
	}

	if (FAILED(m_pFrame->InitializeFrame(nCmdShow, "ASD"))) {

		return S_FALSE;
	}


	//흐름상 여기서 메시지 루프 함수로 점프함
	m_pFrame->LoopMessage();
	//그런데 필요가 있을까?
	//게임 종류 시 결과?
	return S_OK;
}

