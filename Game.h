#pragma once

#include <Windows.h>
#include "Frame.h"
#include "Graphics.h"

class Game
{
private:
	Frame * m_pFrame;
	Graphics * m_pGraphics;

public:
	Game(HINSTANCE hInstance);
	~Game();

	HRESULT Start(int nCmdShow);
	//TODO:레벨 클래스 추가 후 시그니쳐에 등록할까
	HRESULT LoadLevel();

};

