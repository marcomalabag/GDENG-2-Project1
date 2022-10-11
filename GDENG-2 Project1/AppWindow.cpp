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

	positions[0] = Vector3D(-.5, .25, 0.0);
	positions[1] = Vector3D(.5, .25, 0.0);
	positions[2] = Vector3D(0, -.25, 0.0);

	
	TrianglePositions[0] = Vector3D(-.5, .5, 0.0);
	TrianglePositions[1] = Vector3D(.5, .5, 0.0);
	TrianglePositions[2] = Vector3D(0, .001, 0.0);
	

	//For instantiating triangles
	
	for(int i = 0; i < 3; i++)
	{
		this->triangle.push_back(new Triangle());
		this->triangle.at(i)->setPosition(TrianglePositions[i]);
		this->triangle.at(i)->setWindowSizeHeight((rc.bottom - rc.top) / 400.f);
		this->triangle.at(i)->setWindowSizeLength((rc.right - rc.left) / 400.f);
	}
	
	

	//For instantiating rectangles
	for (int i = 0; i < 3; i++)
	{
		this->rectangle.push_back(new class Rectangle());
		this->rectangle.at(i)->setPosition(positions[i]);
		this->rectangle.at(i)->setWindowSizeHeight(height / 400.f);
		this->rectangle.at(i)->setWindowSizeLength(width / 400.f);
	}
	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//For instantiating triangles
	
	for(int i = 0; i < this->triangle.size(); i++)
	{
		this->triangle.at(i)->draw();
	}
	
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) - 3);
	for (int i = 0; i < this->triangle.size(); i++)
	{
		this->triangle.at(i)->draw();
	}

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
