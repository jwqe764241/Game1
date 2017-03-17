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
private:
	bool ReadKeyboard();
	bool ReadMouse();

	void UpdateInput();
private:
	IDirectInput8		* m_pDirectInput;
	IDirectInputDevice8 * m_pKeyboardDevice;
	IDirectInputDevice8 * m_pMouseDevice;

	//DIMOUSESTATE2?는 rgbButton의 요소 갯수가 4개 더 많음;?
	DIMOUSESTATE  m_MouseState;

	SCREENSIZE m_ScreenSize;
	MOUSEPOINT m_MousePoint;

	bool m_bIsInitialized;
};