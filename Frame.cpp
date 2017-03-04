#pragma comment(lib, "d2d1")

#include "resource.h"
#include "Frame.h"

#include <cassert>
#include <thread>


/////////////////////////////
#define DEBUG

#ifdef DEBUG
	#include <iostream>
#endif



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

	//::AllocConsole();

	//-----------------------
	assert(m_hInstance != NULL);
	//-----------------------

	WNDCLASSEX wndClass;	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = Frame::WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
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

	m_hWnd = CreateWindow(m_lpcWndClassName,
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

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT Frame::ReleaseFrame() {

	// TODO: 핸들 유효와 클래스이름 유효 검사

	CloseWindow(m_hWnd);
	delete m_lpcWndClassName;

	return S_OK;

}

void Frame::LoopMessage() {

	bool bIsRunning = true;
	
	/*
	std::thread thLoopBody([&bIsRunning](){

		MSG msg;

		while (bIsRunning)
		{
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT) {
				bIsRunning = false;
			}
		}

	});
	*/

	MSG msg;

	while (bIsRunning)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT) {
				bIsRunning = false;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}

	}

	

}

HWND Frame::GetHWND() {

	if (m_hWnd != NULL) {

		return m_hWnd;
	}
	else {

		return 0;
	}

}
bool Frame::IsActive() {

	if (m_hWnd != NULL) {

		return m_hWnd == GetActiveWindow();
	}
	else {

		return 0;
	}

}


LRESULT CALLBACK Frame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{

	switch (msg) {
		case WM_CREATE:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			break;

		case WM_KEYDOWN:
			MessageBox(hWnd, "dsfsd", "DSfsd", MB_OK);
			break;

		case WM_LBUTTONDOWN:
			break;

		case WM_RBUTTONDOWN:
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}