#include "Window.h"
#include <iostream>
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"
#include <exception>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Window* window = nullptr;
Window::Window()
{
}



LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
		case WM_CREATE:
		{
				Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
				window->setHWND(hwnd);

				window->onCreate();
				break;
		}
		case WM_DESTROY:
		{
			Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		default:
		{
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

	}

	return NULL;
}

bool Window::initializeWC()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"GDENG - 2 Project";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &wndProc;

	if (!::RegisterClassEx(&wc))
	{

		return false;
	}
}

bool Window::initializeAppWindow()
{

	this->m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"GDENG - 2 Project", L"DirectX Application", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1440, 900, NULL, NULL, NULL, this);

	if (!this->m_hwnd)
	{
		std::cout << "Not working";
		return false;
	}

	::ShowWindow(this->m_hwnd, SW_SHOW);
	::UpdateWindow(this->m_hwnd);


	m_isRunning = true;

	return true;
}

bool Window::initiazeGameWindow()
{
	
	/*
	this->m_gamewindow = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"GDENG - 2 Project", L"Game Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 540, 960, NULL, NULL, NULL, this);

	if (!this->m_gamewindow)
	{
		std::cout << "Game window not working";
		return false;
	}

	::ShowWindow(this->m_gamewindow, SW_SHOW);
	::UpdateWindow(this->m_gamewindow);

	GameWindowRunning = true;
	*/
	return true;
	
}



bool Window::broadcast()
{

	MSG msg;

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	

	Sleep(1);

	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(this->m_hwnd))
	{
		return false;
	}

	/*
	if (!::DestroyWindow(this->m_gamewindow)) {
		return false;
	}
	*/
	return true;
	
}

bool Window::isRun()
{
	return m_isRunning;
}

bool Window::isGameRun()
{
	//return GameWindowRunning;
	return false;
}

HWND Window::gethwnd()
{
	return m_hwnd;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}


void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

Window::~Window()
{
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
	
}

void Window::onDestroy()
{
	m_isRunning = false;
	//GameWindowRunning = false;
}