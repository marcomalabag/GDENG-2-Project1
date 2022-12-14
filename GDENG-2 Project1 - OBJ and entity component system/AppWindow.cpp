#include "AppWindow.h"
#include "Debug.h"


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
	BaseSystem::initialize();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	EngineTime::initialize();
	EngineBackEnd::initialize();
	SceneCameraHandler::initialize();
	Shaderlibrary::initialize();
	TextureManager::initialize();
	MeshManager::initialize();
	ActionHistory::initialize();

	InputSystem::getInstance()->showCursor(true);

	GameObjectManager::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();


	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	Debug::Log("Initialize");
}

void AppWindow::createInterface()
{
	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	this->ticks += EngineTime::getDeltaTime() * 1.0f;
	InputSystem::getInstance()->update();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	EngineBackEnd* backend = EngineBackEnd::getInstance();
	if (backend->getMode() == EngineBackEnd::EditorMode::PLAY) {
		BaseSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
		GameObjectManager::getInstance()->updateAll();
	}
	else if (backend->getMode() == EngineBackEnd::EditorMode::EDITOR) {
		GameObjectManager::getInstance()->updateAll();

	}
	else if (backend->getMode() == EngineBackEnd::EditorMode::PAUSED) {
		if (backend->insideFrameStep()) {
			BaseSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
			GameObjectManager::getInstance()->updateAll();
			backend->endFrameStep();
		}
	}


	SceneCameraHandler::getInstance()->update();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);
	UIManager::getInstance()->drawAllUI();
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::destroy();
	m_swap_chain->release();
	GraphicsEngine::getInstance()->release();
	TextureManager::destroy();
	BaseSystem::destroy();
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
