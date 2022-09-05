#include "AppWindow.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::getInstance()->init();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::getInstance()->release();
}