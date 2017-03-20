#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include "Frame.h"
#include "Graphics.h"
#include "Player.h"
#include "IActor.h"
#include "GameDefine.h"

//TODO:�ϴ� ����������� ������ �غ�;
//TODO:������ LevelController ���� ���� 

class Game 
{
private:
	Frame * m_pFrame;
	Graphics * m_pGraphics;

	//Level Controller ����
	//static GameLevel * m_pCurrentLevel;

	//TODO:���ʹ� ������ ����
	//TODO:����ƴ�
	std::vector<IActor *> m_RenderList;

public:
	Game(Frame * frame);
	~Game();

	HRESULT Start(int nCmdShow, char * frameTitle);
	HRESULT ClearScreen(D2D1::ColorF color){ m_pGraphics->ClearScreen(color); }

	void Update();
	void Render();

	void StartLooping();
	//LevelController ����
	//static void LoadLevel(GameLevel * level);
	//static void ChangeLevel(GameLevel *level);
};

