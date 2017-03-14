#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include "Frame.h"
#include "Graphics.h"
#include "Player.h"
#include "IActor.h"
#include "GameDefine.h"

//TODO:일단 렌더러블부터 렌더링 해봐;
//TODO:문제시 LevelController 내용 빼기 

class Game 
{
private:
	Frame * m_pFrame;
	Graphics * m_pGraphics;

	//Level Controller 내용
	//static GameLevel * m_pCurrentLevel;

	//TODO:벡터는 최후의 수단
	//TODO:절대아님
	std::vector<IActor *> m_RenderList;

public:
	Game(Frame * frame);
	~Game();

	HRESULT Start(int nCmdShow, char * frameTitle);
	HRESULT ClearScreen(D2D1::ColorF color){ m_pGraphics->ClearScreen(color); }

	void Update();
	void Render();

	void StartLooping();
	//LevelController 내용
	//static void LoadLevel(GameLevel * level);
	//static void ChangeLevel(GameLevel *level);
};

