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
	
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	EngineTime::initialize();
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
	/*
	int max = 1.5f;
	int min = -2.5f;
	Math math;

	for(int i = 0; i < 100; i++)
	{
		float x = math.getRandom(min, max);
		float y = math.getRandom(-2.0, 1.0f);
		
		float speed = math.getRandom(1.0f, 25.0f);
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.25, .25, .25);
		this->Cubes.at(i)->setPosition(x, y, 0.0f);
		this->Cubes.at(i)->setAnimSpeed(speed);
	}
	*/

	//Cube and plane initialization
	
	for (int i = 0; i < 1; i++)
	{
		this->Planes.push_back(new Plane("Plane", shader_byte_code, size_shader));
		this->Planes.at(i)->setScale(3.0, 0.01, 1.1);
		this->Planes.at(i)->setPosition(0.0f, -123.0f, 0.0f);
		
		this->Planes.at(i)->setAnimSpeed(0.0f);
	}

	for (int i = 0; i < 1; i++)
	{
		
		this->Cubes.push_back(new Cube("Cube", shader_byte_code, size_shader));
		this->Cubes.at(i)->setScale(.25, .25, .25);
		this->Cubes.at(i)->setPosition(0.0f, 0.0f, 0.0f);
		this->Cubes.at(i)->setAnimSpeed(0.0f);
	}
	

	graphEngine->releaseCompiledShader();


	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = graphEngine->createPixelShader(shader_byte_code, size_shader);
	

	graphEngine->releaseCompiledShader();

	constant cc;
	cc.time = 0;

	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Cube drawing
	/*
	for (int i = 0; i < Cubes.size(); i++)
	{
		Cubes.at(i)->update(EngineTime::getDeltaTime() * 1.0f);
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	*/

	//Cube and plane initialization
	
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}

	for (int i = 0; i < Cubes.size(); i++)
	{
		Cubes.at(i)->draw(rc.right - rc.left, rc.bottom - rc.top, this->vertexshader, this->pixelshader);
	}
	
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//this->vertexbuffer->release();
	//this->indexbuffer->release();
	//this->constantbuffer->release();
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
