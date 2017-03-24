#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include <thread>
#include "Graphics.h"
#include "Player.h"
#include "IActor.h"
#include "TestLevel.h"
#include "TestLevel2.h"
#include "LevelController.h"
#include "GameDefine.h"

class Game 
{
	class Frame{
		private:
			HWND m_hWnd;
			HINSTANCE m_hInstance;
			char * m_lpcWndClassName;
			Graphics * m_pGraphics;

		public:
			DX_Input input;

		public:
			Frame(HINSTANCE hInstance, char * wndClassName);
			~Frame();

			HRESULT InitializeFrame(int nCmdShow, char * frameTitle, Graphics * pGraphics);
			HRESULT Release();

			HWND GetHWND();
			bool IsActive();
			DX_Input * GetInput() { return &input; }

			static LRESULT CALLBACK HandleWndProc(HWND, UINT, WPARAM, LPARAM);
			LRESULT CALLBACK WndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam);

	}m_Frame;

private:
	Graphics  * m_pGraphics;
	LevelController levelController;

public:
	Game(HINSTANCE hInstance, char * wndClassName);
	~Game();

	HRESULT Start(int nCmdShow, char * frameTitle);
	HRESULT ClearScreen(D2D1::ColorF color){ m_pGraphics->ClearScreen(color); }

	void Update();
	void Render();

	void StartLooping();
};

