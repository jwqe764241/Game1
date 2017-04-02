#pragma comment(lib, "d2d1")

#include "Game.h"
#include "resource.h"

Game::Game(HINSTANCE hInstance, char * wndClassName) :
	 m_hInstance(hInstance),
	 m_lpcWndClassName(wndClassName)
{
	m_pTimer = GameTimer();
}
Game::~Game()
{
}


HRESULT Game::InitializeFrame(int nCmdShow, char * frameTitle)
{
	WNDCLASSEX wndClass;	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = Game::HandleWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = sizeof(Game*);
		wndClass.hInstance = m_hInstance;
		wndClass.hIcon = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = m_lpcWndClassName;
		wndClass.hIconSm = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	RegisterClassEx(&wndClass);

	RECT rect = {0, 0, 800, 600};
	
	::GetWindowRect(GetDesktopWindow(), &rect);

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

	ShowWindow(m_hWnd, SW_MAXIMIZE);
	UpdateWindow(m_hWnd);

	if (!input.Initialize(m_hInstance, m_hWnd, rect.right - rect.left, rect.bottom - rect.top)) { return S_FALSE; }

	return S_OK;
}

HRESULT Game::Release()
{
	CloseWindow(m_hWnd);
	delete m_lpcWndClassName;

	return S_OK;
}
HWND Game::GetHWND()
{
	if (m_hWnd != NULL) { return m_hWnd; }
	else { return 0; }
}
bool Game::IsActive()
{
	if (m_hWnd != NULL) { return m_hWnd == GetActiveWindow(); }
	else { return false; }
}

LRESULT CALLBACK Game::HandleWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Game * localFrame = reinterpret_cast<Game *>(GetWindowLongPtr(hWnd, 0));

	if (localFrame) { return localFrame->WndProc(hWnd, msg, wParam, lParam); }
	else { return DefWindowProc(hWnd, msg, wParam, lParam); }
}
LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (Graphics::GetInstance() != nullptr) {
			RECT rect;	GetWindowRect(m_hWnd, &rect);
			Graphics::GetInstance()->OnResize((rect.right - rect.left), (rect.bottom - rect.top));
			levelController.OnResize();
		}
		break;
	case WM_USER + 1:
		levelController.ChangeLevel(new TestLevel2(&input));
		break;
	case WM_USER + 2:
		MessageBox(m_hWnd, "End!", "Yeah!", MB_OK);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//---------------------------------------------------------------------------------------------//

HRESULT Game::Start(int nCmdShow, char * frameTitle)
{
	if (FAILED(InitializeFrame(nCmdShow, frameTitle)))				  { return S_FALSE; }
	if (FAILED(Graphics::GetInstance()->initialize(GetHWND())))					  { return S_FALSE; }

	levelController.LoadLevel(new TestLevel(&input));

	m_pTimer.Initialize();

	return S_OK;
}

void Game::Looping()
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
			
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		input.ReadInput();
		Update();
		Render();
	}

}

void Game::Update()
{
	m_pTimer.Frame();
	levelController.Update(m_pTimer.GetTime());
}


void Game::Render()
{
	if (!Graphics::GetInstance()->GetRenderTarget()) {
		Graphics::GetInstance()->CreateDeviceResource(m_hWnd);
		levelController.CreateLevelDeviceResources();
	}

	RECT rect; ::GetClientRect(m_hWnd, &rect);

	Graphics::GetInstance()->BeginDraw();

	//Graphics::GetInstance()->ClearScreen(D2D1::ColorF(0, 0, 1.0f));
	levelController.Render();
  
	if (Graphics::GetInstance()->EndDraw() == D2DERR_RECREATE_TARGET)
	{
		Graphics::GetInstance()->ReleaseDeviceResource();
		levelController.ReleaseLevelDeviceResources();
	}
}