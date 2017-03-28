#pragma once
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>


//TODO:나중엔 GameDefine에 위치하여 있을것
typedef struct _SCREENSIZE {
	int width;
	int height;
} SCREENSIZE, *LPSCREENSIZE;

typedef struct _MOUSEPOINT {
	int x;
	int y;
} MOUSEPOINT, *LPMOUSEPOINT;


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
	MOUSEPOINT m_MousePoint;
  
private:
	bool ReadKeyboard();
	bool ReadMouse();

	void UpdateInput();
private:
	IDirectInput8		* m_pDirectInput;
	IDirectInputDevice8 * m_pKeyboardDevice;
	IDirectInputDevice8 * m_pMouseDevice;

	SCREENSIZE m_ScreenSize;

	bool m_bIsInitialized;
};