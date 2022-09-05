#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();
	HWND gethwnd();
	~Window();

	//virtual methods
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	HWND m_hwnd;
	bool m_isRunning;

};

