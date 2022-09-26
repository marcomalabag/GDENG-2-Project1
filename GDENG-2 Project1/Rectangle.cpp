#include "Rectangle.h"

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


Rectangle::Rectangle()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,      0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	this->vertexshader = graphEngine->createVertexShader(shader_byte_code, size_shader);

	this->vertexbuffer = graphEngine->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	this->vertexbuffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->pixelshader = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();


	constant cc;
	cc.m_angle = 0;

	this->constantbuffer = graphEngine->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

}

void Rectangle::draw()
{
	unsigned long newtime = 0;
	if (this->oldTime)
	{
		newtime = GetTickCount() - this->oldTime;
	}

	this->deltaTime = newtime / 1000.0f;
	this->oldTime = ::GetTickCount();

	this->angle += 1.57f * this->deltaTime;
	constant cc;
	cc.m_angle = this->angle;

	this->constantbuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->vertexshader, this->constantbuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(this->pixelshader, this->constantbuffer);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->vertexshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->pixelshader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(this->vertexbuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(this->vertexbuffer->getSizeVertexList(), 0);

}

Rectangle::~Rectangle()
{
	this->vertexbuffer->release();
	this->vertexshader->release();
	this->pixelshader->release();
}
