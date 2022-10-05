#include "GameWindow.h"


GameWindow* GameWindow::sharedInstance = NULL;
GameWindow::GameWindow()
{
	
}


void GameWindow::initialize()
{
	sharedInstance = new GameWindow();
	
	sharedInstance->initiazeGameWindow();
}

GameWindow* GameWindow::getInstance()
{
	if (sharedInstance != NULL) {
		return sharedInstance;
	}
}

void GameWindow::onCreate()
{
	Window::onCreate();
}

void GameWindow::CreateGameWindow()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	m_swap_chain_game = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	
	m_swap_chain_game->init(this->m_gamewindow, width, height);

	positions[0] = Vector3D(-.5, .25, 0.0);
	positions[1] = Vector3D(.5, .25, 0.0);
	positions[2] = Vector3D(0, -.25, 0.0);

	/*
	TrianglePositions[0] = Vector3D(-.5, .5, 0.0);
	TrianglePositions[1] = Vector3D(.5, .5, 0.0);
	TrianglePositions[2] = Vector3D(0, .001, 0.0);
	*/

	//For instantiating triangles
	
	for(int i = 0; i < 3; i++)
	{
		this->triangle.push_back(new Triangle());
		this->triangle.at(i)->setPosition(TrianglePositions[i]);
		this->triangle.at(i)->setWindowSizeHeight((rc.bottom - rc.top) / 400.f);
		this->triangle.at(i)->setWindowSizeLength((rc.right - rc.left) / 400.f);
	}
	


	//For instantiating rectangles
	for (int i = 0; i < 1; i++)
	{
		this->rectangle.push_back(new class Rectangle());
		this->rectangle.at(i)->setPosition(positions[i]);
		this->rectangle.at(i)->setWindowSizeHeight(height / 400.f);
		this->rectangle.at(i)->setWindowSizeLength(width / 400.f);
	}
}

void GameWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain_game,
		0, 0, 0.5, 0.5);
	RECT rc = this->getGameWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top , 1);

	for (int i = 0; i < this->triangle.size(); i++)
	{
		this->triangle.at(i)->draw();
	}

	for (int i = 0; i < this->rectangle.size(); i++)
	{
		this->rectangle.at(i)->draw();
	}

	this->m_swap_chain_game->present(false);
}


void GameWindow::onDestroy()
{
	Window::onDestroy();
	this->m_swap_chain_game->release();
	if (GraphicsEngine::getInstance() != NULL) {
		GraphicsEngine::getInstance()->release();
	}
}


GameWindow::~GameWindow()
{
}
