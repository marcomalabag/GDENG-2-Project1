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

	InputSystem::getInstance()->showCursor(false);

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();


	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	

	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = graphEngine->createVertexShader(shader_byte_code, size_shader);

	
	
	//Cube Initialization
	
	int max = 1.5f;
	int min = -2.5f;
	Math math;

	for(int i = 0; i < 10; i++)
	{
		float x = math.getRandom(min, max);
		float y = math.getRandom(-2.0, 1.0f);
		
		float speed = math.getRandom(1.0f, 25.0f);
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.25, .25, .25);
		this->Cubes.at(i)->setPosition(x, y, 1.0f);
		this->Cubes.at(i)->setAnimSpeed(speed);
		
	}
	//Sphere initialization
	//sphere = new Sphere("Sphere", shader_byte_code, size_shader);
	//sphere->setPosition(0, 0, 0);
	//sphere->setScale(.25, .25, .25);

	//Cylinder initialization
	//this->cylinder = new Cylinder("Cylinder", shader_byte_code, size_shader);
	//this->cylinder->setPosition(1.25, .25, 0);
	//this->cylinder->setScale(.25, .25, .25);
	//this->cylinder->setRotation(45, 90, 45);


	//Cube and plane initialization
	/*
	for (int i = 0; i < 1; i++)
	{
		this->Planes.push_back(new Plane("Plane", shader_byte_code, size_shader));
		this->Planes.at(i)->setScale(3.0, 0.01, 1.1);
		this->Planes.at(i)->setPosition(0.0f, 0.0f, 0.0f);
		
		this->Planes.at(i)->setAnimSpeed(0.0f);
	}

	for (int i = 0; i < 1; i++)
	{
		
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.25, .25, .25);
		this->Cubes.at(i)->setPosition(0.0f, 0.0f, 0.0f);
		this->Cubes.at(i)->setAnimSpeed(0.0f);
	}
	*/

	graphEngine->releaseCompiledShader();


	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = graphEngine->createPixelShader(shader_byte_code, size_shader);
	

	graphEngine->releaseCompiledShader();

	

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	this->ticks += EngineTime::getDeltaTime() * 1.0f;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::getInstance()->update();
	
	//Cube drawing


	for (int i = 0; i < Cubes.size(); i++)
	{
		
		//Cubes[i]->update(ticks);
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	//sphere->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	//cylinder->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	
	//Cube and plane initialization
	/*
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}

	for (int i = 0; i < Cubes.size(); i++)
	{
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	*/

	SceneCameraHandler::getInstance()->update();
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//this->vertexbuffer->release();
	//this->indexbuffer->release();
	//this->constantbuffer->release();
	InputSystem::destroy();
	m_swap_chain->release();
	//this->vertexshader->release();
	//this->pixelshader->release();
	GraphicsEngine::getInstance()->release();
	
	
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
