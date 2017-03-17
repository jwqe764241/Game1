#pragma once

#include <Windows.h>
#include <cassert>
#include <thread>
#include "Keyboard.h"
#include "DX_Input.h"

class Frame
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	char * m_lpcWndClassName;

public:
	Keyboard keyboard;
	DX_Input input;
//ÀÛ¾÷
public:
	Frame(HINSTANCE hInstance, char * wndClassName);
	~Frame();

	HRESULT InitializeFrame(int nCmdShow, char * frameTitle);
	HRESULT Release();
	//void LoopMessage();

	HWND GetHWND();
	bool IsActive();

	static LRESULT CALLBACK HandleWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam);
};

