#include "DX_Input.h"
#pragma comment(lib, "dinput8")
#pragma comment(lib, "dxguid.lib")

#include "GameDefine.h"


DX_Input::DX_Input()
	:m_pDirectInput(NULL),
	 m_pKeyboardDevice(NULL),
	 m_pMouseDevice(NULL),
	 m_bIsInitialized(false)
{
}
DX_Input::~DX_Input()
{
}


bool DX_Input::Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight)
{
	m_ScreenSize.width = screenWidth;
	m_ScreenSize.height = screenHeight;

	m_MousePoint.x = 0;
	m_MousePoint.y = 0;

	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void **>(&m_pDirectInput), NULL);

	//keyboard setting
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, NULL)))	{ return false; }
	if (FAILED(m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))							{ return false; }
	if (FAILED(m_pKeyboardDevice->SetCooperativeLevel(hWnd, 
		DISCL_FOREGROUND | DISCL_EXCLUSIVE)))												{ return false; }
	if (FAILED(m_pKeyboardDevice->Acquire()))												{ return false; }


	//mouse setting
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL)))			{ return false; }
	if (FAILED(m_pMouseDevice->SetDataFormat(&c_dfDIMouse)))								{ return false; }
	if (FAILED(m_pMouseDevice->SetCooperativeLevel(hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))											{ return false; }
	if (FAILED(m_pMouseDevice->Acquire()))													{ return false; }

	return true;
}
void DX_Input::Release()
{
	if (m_pKeyboardDevice) {
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = NULL;
	}

	if (m_pMouseDevice) {
		m_pMouseDevice->Unacquire();
		m_pMouseDevice->Release();
		m_pMouseDevice = NULL;
	}

	if (m_pDirectInput) {
		m_pDirectInput->Release();
		m_pDirectInput = NULL;
	}
}


bool DX_Input::ReadInput()
{
	if (!ReadKeyboard()) { return false; }
	if (!ReadMouse())    { return false; }

	UpdateInput();

	return true;
}
bool DX_Input::ReadKeyboard()
{
	HRESULT hr;
	hr = m_pKeyboardDevice->GetDeviceState(sizeof(m_KeyboardState), static_cast<LPVOID>(m_KeyboardState));

	if (FAILED(hr)) {
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) { m_pKeyboardDevice->Acquire(); }
		else													  { return false; }
	}

	return true;
}
bool DX_Input::ReadMouse()
{
	HRESULT hr;
	hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);

	if (FAILED(hr)) {  
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) { m_pMouseDevice->Acquire(); }
		else													  { return false; }
	}

	return true;
}


void DX_Input::UpdateInput()
{
	m_MousePoint.x = m_MouseState.lX;
	m_MousePoint.y = m_MouseState.lY;

	if (m_MousePoint.x < 0) { m_MousePoint.x = 0; }
	if (m_MousePoint.y < 0) { m_MousePoint.y = 0; }

	if (m_MousePoint.x < m_ScreenSize.width)  { m_MousePoint.x = m_ScreenSize.width; }
	if (m_MousePoint.y < m_ScreenSize.height) { m_MousePoint.y = m_ScreenSize.height; }
}


bool DX_Input::IsKeyPressed(DWORD keyCode)
{
	if (m_KeyboardState[keyCode] & 0x80) { return true; }

	return false;
}