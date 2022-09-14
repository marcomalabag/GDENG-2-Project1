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
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	this->triangle = new Triangle(shader_byte_code, size_shader, this->vertexshader);

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	this->rectangle = new class Rectangle(shader_byte_code, size_shader, this->vertexshader);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	this->triangle->draw();
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