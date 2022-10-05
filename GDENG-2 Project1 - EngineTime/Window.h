#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	HWND gethwnd();
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	

	//virtual methods
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_isRunning;

};

