#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};


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
	
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();


	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	

	this->rectangle = new class Rectangle();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	
	this->rectangle->draw();

	

	this->m_swap_chain->present(false);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//this->vertexbuffer->release();

	
	m_swap_chain->release();
	
	
	//this->vertexshader->release();
	//this->pixelshader->release();
	GraphicsEngine::getInstance()->release();
	
	
}


AppWindow* AppWindow::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}
