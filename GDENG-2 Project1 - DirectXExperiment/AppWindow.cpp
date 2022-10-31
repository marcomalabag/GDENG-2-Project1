#include "AppWindow.h"
#include "IMGUI/imgui.h"


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
	sharedInstance->initializeWC();
	sharedInstance->initializeAppWindow();
	
}

void AppWindow::onCreate()
{
	Window::onCreate();
	
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	Viewport::initialize();

	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	Viewport::getInstance()->add((FLOAT)width / 2.0f, (FLOAT)height / 2.0f, 0.0f,
		1.0f, 0.0f, 0.0f);

	Viewport::getInstance()->add((FLOAT)width / 2.0f, (FLOAT)height / 3.0f, 0.0f,
		1.0f, (FLOAT)width / 2.0f, (FLOAT)width / 2.0f);

	positions[0] = Vector3D(-.5, .25, 0.0);
	positions[1] = Vector3D(.5, .25, 0.0);
	positions[2] = Vector3D(0, -.25, 0.0);

	/*
	TrianglePositions[0] = Vector3D(-.5, .5, 0.0);
	TrianglePositions[1] = Vector3D(.5, .5, 0.0);
	TrianglePositions[2] = Vector3D(0, .001, 0.0);
	*/

	//For instantiating triangles
	/*
	for(int i = 0; i < 3; i++)
	{
		this->triangle.push_back(new Triangle());
		this->triangle.at(i)->setPosition(TrianglePositions[i]);
		this->triangle.at(i)->setWindowSizeHeight((rc.bottom - rc.top) / 400.f);
		this->triangle.at(i)->setWindowSizeLength((rc.right - rc.left) / 400.f);
	}
	*/
	

	//For instantiating rectangles
	for (int i = 0; i < 1; i++)
	{
		this->rectangle.push_back(new class Rectangle());
		this->rectangle.at(i)->setPosition(positions[i]);
		this->rectangle.at(i)->setWindowSizeHeight(height / 400.f);
		this->rectangle.at(i)->setWindowSizeLength(width / 400.f);
	}
	
}

void AppWindow::createInterface()
{
	UIManager::initialize(this->m_hwnd);
}


void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(Viewport::getInstance()->getViewport(0));

	//For instantiating triangles
	/*
	for(int i = 0; i < this->triangle.size(); i++)
	{
		this->triangle.at(i)->draw();
	}
	*/

	for (int i = 0; i < this->rectangle.size(); i++)
	{
		this->rectangle.at(i)->draw();
	}
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(Viewport::getInstance()->getViewport(1));
	for (int i = 0; i < this->rectangle.size(); i++)
	{
		this->rectangle.at(i)->draw();
	}

	UIManager::getInstance()->drawAllUI();

	this->m_swap_chain->present(false);

	//this->m_swap_chain_game->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//this->vertexbuffer->release();

	
	m_swap_chain->release();
	
	
	//this->vertexshader->release();
	//this->pixelshader->release();
	if (GraphicsEngine::getInstance() != NULL) {
		GraphicsEngine::getInstance()->release();
	}
	
	UIManager::getInstance()->destroy();
	
}


AppWindow* AppWindow::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}
