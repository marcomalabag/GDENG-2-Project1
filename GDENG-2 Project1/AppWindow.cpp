#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
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

	// triangle coordinates
	/*
	vertex list[] = {
		{-0.5f,-0.5f,0.0f},
		{0.0f,0.5f,0.0f},
		{ 0.5f,-0.5f,0.0f}
	};
	*/

	//Quadrilateral coordinates
	
	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f, 1,0,0},
		{-0.5f,0.5f,0.0f,  0,1,0},
		{ 0.5f,-0.5f,0.0f, 0,0,1},
		{ 0.5f,0.5f,0.0f,  1,1,0}
	};
	


	this->VertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	this->VertexBuffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	this->pixelshader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.5, 0.5);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->vertexshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->pixelshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(this->VertexBuffer);

	//Triangle render
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(this->VertexBuffer->getSizeVertexList(), 0);

	//Quadrilateral render
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(this->VertexBuffer->getSizeVertexList(), 0);
	this->m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->VertexBuffer->release();
	m_swap_chain->release();
	this->vertexshader->release();
	this->pixelshader->release();
	GraphicsEngine::getInstance()->release();
}