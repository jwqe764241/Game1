#pragma once
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include "GameDefine.h"


class DX_Input
{
public:
	DX_Input();
	~DX_Input();
	
	bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight);
	void Release();

	bool ReadInput();
	bool IsKeyPressed(DWORD keyCode);
public:
	unsigned char m_KeyboardState[256];
	DIMOUSESTATE  m_MouseState;
	GameUtils::Type::MOUSEPOINT m_MousePoint;
  
private:
	bool ReadKeyboard();
	bool ReadMouse();

	void UpdateInput();
private:
	IDirectInput8		* m_pDirectInput;
	IDirectInputDevice8 * m_pKeyboardDevice;
	IDirectInputDevice8 * m_pMouseDevice;

	GameUtils::Type::SCREENSIZE m_ScreenSize;

	bool m_bIsInitialized;
};