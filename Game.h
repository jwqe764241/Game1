#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include <thread>
#include "Graphics.h"
#include "Player.h"
#include "IActor.h"
#include "GameTimer.h"
#include "TestLevel.h"
#include "TestLevel2.h"
#include "MainLevel.h"
#include "LevelController.h"
#include "GameDefine.h"

class Game 
{
	//Frame 내용
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	char * m_lpcWndClassName;

public:
	DX_Input input;

public:
	HRESULT InitializeFrame(int nCmdShow, char * frameTitle);
	HRESULT Release();

	HWND GetHWND();
	bool IsActive();
	DX_Input * GetInput() { return &input; }

	static LRESULT CALLBACK HandleWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam);
	//Frame 내용 끝

public:
	GameTimer m_pTimer;
	LevelController levelController;

public:
	Game() = delete;
	Game(HINSTANCE hInstance, char * wndClassName);
	~Game();

	HRESULT Start(int nCmdShow, char * frameTitle);
	HRESULT ClearScreen(D2D1::ColorF color){ Graphics::GetInstance()->ClearScreen(color); }

	void Update();
	void Render();

	void Looping();
};

