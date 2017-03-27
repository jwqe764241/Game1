#pragma comment(lib, "d2d1")

#include "Game.h"
#include "resource.h"

#include <string>

Game::Frame::Frame(HINSTANCE hInstance, char * wndClassName) 
	:m_hWnd(NULL),
	 m_hInstance(hInstance),
	 m_lpcWndClassName(wndClassName)
{
}
Game::Frame::~Frame()
{
	CloseHandle(m_hWnd);
	CloseHandle(m_hInstance);
	delete m_lpcWndClassName;
	delete m_pGraphics;
}

HRESULT Game::Frame::InitializeFrame(int nCmdShow, char * frameTitle, Graphics * pGraphics)
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
		//wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = m_lpcWndClassName;
		wndClass.hIconSm = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	RegisterClassEx(&wndClass);

	RECT rect = {0, 0, 800, 600};
	
	//::GetWindowRect(GetDesktopWindow(), &rect);

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//WS_EX_TOPMOST | WS_POPUP
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

	m_pGraphics = pGraphics;

	if (!input.Initialize(m_hInstance, m_hWnd, rect.right - rect.left, rect.bottom - rect.top)) { return S_FALSE; }

	return S_OK;
}

HRESULT Game::Frame::Release()
{
	CloseWindow(m_hWnd);
	delete m_lpcWndClassName;

	return S_OK;
}

HWND Game::Frame::GetHWND()
{
	if (m_hWnd != NULL) { return m_hWnd; }
	else { return 0; }
}

bool Game::Frame::IsActive()
{
	if (m_hWnd != NULL) { return m_hWnd == GetActiveWindow(); }
	else { return false; }
}

LRESULT CALLBACK Game::Frame::HandleWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Frame * localFrame = reinterpret_cast<Frame *>(GetWindowLongPtr(hWnd, 0));

	if (localFrame) { return localFrame->WndProc(hWnd, msg, wParam, lParam); }
	else { return DefWindowProc(hWnd, msg, wParam, lParam); }
}

LRESULT CALLBACK Game::Frame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (m_pGraphics != nullptr) {
			RECT rect;	GetWindowRect(m_hWnd, &rect);
			m_pGraphics->OnResize((rect.right - rect.left), (rect.bottom - rect.top));
		}
		break;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//---------------------------------------------------------------------------------------------//


Game::Game(HINSTANCE hInstance, char * wndClassName)
	: m_pGraphics(new Graphics()),
	  m_Frame(hInstance, wndClassName)
{
}

Game::~Game()
{
	delete m_pGraphics;
}

HRESULT Game::Start(int nCmdShow, char * frameTitle)
{
	if (FAILED(m_Frame.InitializeFrame(nCmdShow, frameTitle, m_pGraphics)))	  { return S_FALSE; }
	if (FAILED(m_pGraphics->initialize(m_Frame.GetHWND())))	  { return S_FALSE; }

	levelController.LoadLevel(new TestLevel(m_pGraphics, m_Frame.GetInput()));

	return S_OK;
}

void Game::StartLooping()
{
	MSG msg;

	bool bIsRunning = true;

	while (bIsRunning)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				//TODO:루프를 끝내기 전 빠진것이 없나?
				bIsRunning = false;
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		m_Frame.input.ReadInput();
		Update();
		Render();
	}

}

void Game::Update()
{

	levelController.Update();

}


void Game::Render()
{
	m_pGraphics->BeginDraw();

		m_pGraphics->ClearScreen(D2D1::ColorF(0, 0, 1.0f));
  
		levelController.Render();

	m_pGraphics->EndDraw();
}