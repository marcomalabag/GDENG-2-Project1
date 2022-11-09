#include "AppWindow.h"



AppWindow* AppWindow::sharedInstance = NULL;
AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	EngineTime::initialize();
	SceneCameraHandler::initialize();
	Shaderlibrary::initialize();
	TextureManager::initialize();
	TextureLibrary::initialize();
	MeshManager::initialize();

	InputSystem::getInstance()->showCursor(true);

	GameObjectManager::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();


	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	
	
	

	

}

void AppWindow::createInterface()
{
	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	this->ticks += EngineTime::getDeltaTime() * 1.0f;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	SceneCameraHandler::getInstance()->update();
	InputSystem::getInstance()->update();
	UIManager::getInstance()->drawAllUI();
	//Cube drawing

	/*
	for (int i = 0; i < Cubes.size(); i++)
	{
		
		Cubes[i]->update(ticks);
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	
	sphere->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	cylinder->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	
	//Cube and plane initialization
	
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	*/
	
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);

	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::destroy();
	m_swap_chain->release();
	GraphicsEngine::getInstance()->release();
	TextureManager::destroy();
	
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{

}

void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& deltaMousePos)
{
	
}

void AppWindow::onLeftMouseDown(const Point& mousePosition)
{
	
}

void AppWindow::onLeftMouseUp(const Point& mousePosition)
{
	
}

void AppWindow::onRightMouseDown(const Point& mousePosition)
{
	
}

void AppWindow::onRightMouseUp(const Point& mousePosition)
{
	
}


AppWindow* AppWindow::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}
