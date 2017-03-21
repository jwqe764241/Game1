#include "Frame.h"

//프로젝트에서 제외됨

/*

Frame::Frame(HINSTANCE hInstance, char * wndClassName): 
	m_hWnd(NULL),
	m_hInstance (hInstance),
	m_lpcWndClassName(wndClassName)
{
}
Frame::~Frame()
{
}

HRESULT Frame::InitializeFrame(int nCmdShow, char * frameTitle)
{
	WNDCLASSEX wndClass;	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = &Frame::HandleWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = sizeof(Frame*);
		wndClass.hInstance = m_hInstance;
		wndClass.hIcon = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = m_lpcWndClassName;
		wndClass.hIconSm = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	RegisterClassEx(&wndClass);

	RECT rect = { 0, 0, 800, 600 };

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	
	m_hWnd = CreateWindowEx(
		NULL,
		m_lpcWndClassName,
		frameTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		this);

	SetWindowLongPtr(m_hWnd, 0, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	if (!input.Initialize(m_hInstance, m_hWnd, rect.right - rect.left, rect.bottom - rect.top)) {
	}

	return S_OK;
}

HRESULT Frame::Release() 
{
	CloseWindow(m_hWnd);
	delete m_lpcWndClassName;

	return S_OK;
}

HWND Frame::GetHWND() 
{
	if (m_hWnd != NULL) { return m_hWnd; }
	else				{ return 0; }
}

bool Frame::IsActive() 
{
	if (m_hWnd != NULL) { return m_hWnd == GetActiveWindow(); }
	else				{ return false; }
}

LRESULT CALLBACK Frame::HandleWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	Frame * localFrame = reinterpret_cast<Frame *>(GetWindowLongPtr(hWnd, 0));

	if (localFrame)			{ return localFrame->WndProc(hWnd, msg, wParam, lParam); }
	else                    { return DefWindowProc(hWnd, msg, wParam, lParam); }
}

LRESULT CALLBACK Frame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
*/